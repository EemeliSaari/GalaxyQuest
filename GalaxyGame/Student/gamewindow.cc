#include <QMessageBox>

#include "eventhandler.hh"
#include "galaxy.hh"
#include "gameoverdialog.hh"
#include "gamewindow.hh"
#include "initialize.hh"
#include "highscoresystem.hh"
#include "hpbar.hh"
#include "statistics.hh"
#include "statsframe.hh"
#include "utility.hh"

namespace StudentUI
{

GameWindow::GameWindow(QObject *parent)
    : parent_(parent), state_(false)
{
    statsFrame_ = std::make_shared<StatsFrame>(this);

    gameFrame_ = std::make_shared<GalaxyFrame>(this);

    hpBar_ = std::make_shared<HpBar>(this, 150,100);

    infoFrame_ = std::make_shared<StarInfoFrame>(this);

    createMenu();
    createButtonFrame();

    gameLayout_ = std::make_shared<GameWindowLayout>(this);

    gameLayout_->addWidget(gameFrame_.get() , GameWindowLayout::Center);
    gameLayout_->addWidget(menu_.get(), GameWindowLayout::North);
    gameLayout_->addWidget(statsFrame_.get(), GameWindowLayout::East);
    gameLayout_->addWidget(infoFrame_.get(), GameWindowLayout::East);
    gameLayout_->addWidget(endTurnFrame_.get(), GameWindowLayout::East);
    gameLayout_->addWidget(hpBar_.get(), GameWindowLayout::South);

    setLayout(gameLayout_.get());
}

void GameWindow::startGame(QString playerName)
{
    state_ = true;
    playerName_ = playerName;

    auto stats_ = std::make_shared<Student::Statistics>(this); //Difficulty will setup the starting credits

    auto handler = std::make_shared<Student::EventHandler>(stats_);

    auto galaxy = std::make_shared<Student::Galaxy>();

    //Only calling Common::getGameRunner once.
    auto gameRunner = Common::getGameRunner(galaxy, handler);

    controller_ = std::make_shared<Student::GameController>(galaxy, handler, gameRunner);

    connect(stats_.get(), SIGNAL(updateSavedShips(unsigned)), statsFrame_.get(), SLOT(updateSaved(unsigned)));
    connect(stats_.get(), SIGNAL(updateLostShips(unsigned)), statsFrame_.get(), SLOT(updateLost(unsigned)));
    connect(stats_.get(), SIGNAL(updatePoints(unsigned)), statsFrame_.get(), SLOT(updateScore(unsigned)));
    connect(stats_.get(), SIGNAL(updateCredits(unsigned)), statsFrame_.get(), SLOT(updateCredits(unsigned)));

    connect(handler.get(),SIGNAL(updateDmg(int)), hpBar_.get(), SLOT(updateHp(int)));
    connect(handler.get(), SIGNAL(updateUncertainty(int)), hpBar_.get(), SLOT(updateUncertainty(int)));
    connect(handler.get(), SIGNAL(continueGame()), this, SLOT(newTurn()));
    connect(handler.get(), SIGNAL(gameOver(unsigned)), this, SLOT(gameOver(unsigned)));
    connect(handler.get(), SIGNAL(unPauseGame()), this, SLOT(continueGame()));
    connect(handler.get(), SIGNAL(getActive(unsigned)), statsFrame_.get(), SLOT(updateActive(unsigned)));

    connect(gameFrame_.get(), SIGNAL(movePlayerHere(std::string)),
            controller_.get(), SLOT(movePlayer(std::string)));
    connect(gameFrame_.get(), SIGNAL(shipSaved(std::shared_ptr<Common::Ship>)),
            controller_.get(), SLOT(completeSaveShip(std::shared_ptr<Common::Ship>)));
    connect(gameFrame_.get(), SIGNAL(tryMission(std::string)),
            controller_.get(), SLOT(completeMission(std::string)));
    connect(gameFrame_.get(), SIGNAL(salvageShip(std::shared_ptr<Common::Ship>)),
            controller_.get(), SLOT(salvageShip(std::shared_ptr<Common::Ship>)));
    connect(gameFrame_.get(), SIGNAL(buyInit(std::string)),
            controller_.get(), SLOT(openBuy(std::string)));
    connect(gameFrame_.get(), SIGNAL(repairInit(std::string)),
            controller_.get(), SLOT(openRepair(std::string)));
    connect(gameFrame_.get(), SIGNAL(updateThis(std::string)),
            controller_.get(), SLOT(collectInfo(std::string)));

    connect(handler.get(), SIGNAL(playerTurnsUsed()),
            gameFrame_.get(), SLOT(playerActionsUp()));
    connect(handler.get(), SIGNAL(playerMovesUsed()),
            gameFrame_.get(), SLOT(playerMovesUp()));
    connect(handler.get(), SIGNAL(salvageShip(std::shared_ptr<Common::Ship>)),
            gameFrame_.get(), SLOT(salvageMission(std::shared_ptr<Common::Ship>)));
    connect(handler.get(),SIGNAL(newPlayerLoc(std::string,std::vector<std::string>)),
            gameFrame_.get(), SLOT(playerMoved(std::string,std::vector<std::string>)));
    connect(handler.get(), SIGNAL(spawnedShip(std::shared_ptr<Common::Ship>)),
            gameFrame_.get(), SLOT(addShips(std::shared_ptr<Common::Ship>)));
    connect(handler.get(), SIGNAL(shipIsEntering(std::shared_ptr<Common::Ship>)),
            gameFrame_.get(), SLOT(addShips(std::shared_ptr<Common::Ship>)));
    connect(handler.get(), SIGNAL(shipIsLeaving(std::shared_ptr<Common::Ship>,std::shared_ptr<Common::StarSystem>)),
            gameFrame_.get(), SLOT(shipLeaving(std::shared_ptr<Common::Ship>,std::shared_ptr<Common::StarSystem>)));
    connect(handler.get(), SIGNAL(shipNeedsSaving(std::shared_ptr<Common::Ship>)),
            gameFrame_.get(), SLOT(shipMission(std::shared_ptr<Common::Ship>)));
    connect(handler.get(), SIGNAL(shipSaveFailedAt(std::shared_ptr<Common::Ship>)),
            gameFrame_.get(), SLOT(shipMissionFail(std::shared_ptr<Common::Ship>)));
    connect(handler.get(), SIGNAL(spawnMission(std::string)),
            gameFrame_.get(), SLOT(newMission(std::string)));
    connect(handler.get(), SIGNAL(deleteMission(std::string)),
            gameFrame_.get(), SLOT(missionExpired(std::string)));
    connect(handler.get(), SIGNAL(moveShip(std::shared_ptr<Common::Ship>,Common::Point,Common::Point)),
            gameFrame_.get(), SLOT(shipMoving(std::shared_ptr<Common::Ship>,Common::Point,Common::Point)));

    connect(handler.get(), SIGNAL(sendInfo(std::shared_ptr<Common::StarSystem>,std::vector<std::shared_ptr<Common::Ship> >)),
            infoFrame_.get(), SLOT(updateInfo(std::shared_ptr<Common::StarSystem>,std::vector<std::shared_ptr<Common::Ship> >)));

    stats_->addCredits(150);

    auto systems = controller_->getStarSystems();
    auto map = controller_->getMap();

    gameFrame_->initialize(systems, map);

    controller_->spawnShips(20);
    controller_->setPlayerName(playerName.toStdString());
    controller_->movePlayer();
    controller_->initialize();

    gameFrame_->setInitialized();
    gameFrame_->focusOnPlayer();
}

void GameWindow::resetHard()
{
    controller_.reset();
    gameFrame_->resetScene();

    hpBar_->reset();
    statsFrame_->reset();
    infoFrame_->reset();

    startGame(playerName_);
}

bool GameWindow::getGame()
{
    return state_;
}

QString GameWindow::getPlayerName()
{
    return playerName_;
}

void GameWindow::newTurn()
{
    endTurnFrame_->setEnabled(true);
    gameFrame_->newTurn();
}

void GameWindow::gameOver(unsigned finalScore)
{

    // gets final score and player name
    auto highScoreSystem = std::make_shared<Student::HighScoreSystem>();
    if(highScoreSystem->goesToHighScoreList(finalScore))
    {
        highScoreSystem->reArrangeList(playerName_, finalScore);
    }

    bool enoughForHighScore = highScoreSystem->goesToHighScoreList(finalScore);
    auto *gameOverDialog = new StudentUI::GameOverDialog(enoughForHighScore,
                                                         playerName_,
                                                         finalScore);
    gameOverDialog->exec();
    delete gameOverDialog;

    endTurnFrame_->setEnabled(true);

    emit mainMenu(false);
}

void GameWindow::exitGame()
{
    emit exit();
}

void GameWindow::exitMainMenu()
{
    QMessageBox dialog;
    dialog.setText("Do you want to quit the game?");
    dialog.setInformativeText("Game will remain on the background otherwise.");
    dialog.addButton(QMessageBox::Cancel);
    dialog.addButton(QMessageBox::Ok);

    auto ret = dialog.exec();

    if(ret == 0x00000400)
        emit mainMenu(false);
    else
        emit mainMenu(true);
}

void GameWindow::pause(std::string location)
{
    this->setDisabled(true);
}

void GameWindow::continueGame()
{
    this->setDisabled(false);
}

void GameWindow::endTurnPressed()
{
    endTurnFrame_->setDisabled(true);
    controller_->turnEnded();
}

void GameWindow::newGame()
{
    resetHard();
}

void GameWindow::createButtonFrame()
{
    endTurnFrame_ = std::make_shared<QFrame>(this);
    endTurnFrame_->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);

    // Make the endTurn button
    QPushButton *endTurnButton = new QPushButton(endTurnFrame_.get());
    endTurnButton->setText(QString("End Turn"));
    endTurnButton->setFixedWidth(100);

    QHBoxLayout *layout = new QHBoxLayout(endTurnFrame_.get());
    layout->addWidget(endTurnButton);

    // Connect it to GameController to inform about the ended turn.
    connect(endTurnButton, SIGNAL(clicked(bool)), this, SLOT(endTurnPressed()));

    endTurnFrame_->setLayout(layout);
}

void GameWindow::createMenu()
{
    menu_ = std::make_shared<QMenuBar>();
    menu_->setFixedWidth(100);
    auto menu = menu_->addMenu(tr("&Menu"));

    QAction *exitGameAction = menu->addAction("Exit Game");
    connect(exitGameAction, SIGNAL(triggered(bool)),
            this, SLOT(exitGame()));

    QAction *newAction = menu->addAction("New Game");
    connect(newAction, SIGNAL(triggered(bool)),
            this, SLOT(newGame()));

    QAction *exitMainAction = menu->addAction("Main Menu");
    connect(exitMainAction, SIGNAL(triggered(bool)),
            this, SLOT(exitMainMenu()));

    menu->addAction(newAction);
    menu->addAction(exitMainAction);
    menu->addAction(exitGameAction);
}

}//Student
