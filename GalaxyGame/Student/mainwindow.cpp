#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utility"
#include "startdialog.hh"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), launch_(false)
{
    ui->setupUi(this);

    startWindow_ = new StudentUI::StartWindow(this);
    highScoreWindow_ = new StudentUI::HighScoreWindow(this);

    connect(startWindow_, SIGNAL(startGame(QString)), this, SLOT(gameView(QString)));
    connect(startWindow_, SIGNAL(checkHighScore()), this, SLOT(highscoreView()));
    connect(startWindow_, SIGNAL(exitGame()), this, SLOT(close()));
    connect(startWindow_, SIGNAL(continueGame()), this, SLOT(continueGame()));
    connect(startWindow_, SIGNAL(exitSignal()), this, SLOT(close()));

    Common::utilityInit(time(NULL));

    connect(highScoreWindow_, SIGNAL(goBack()), this, SLOT(startView()));

    gameWindow_ = new StudentUI::GameWindow(this);

    connect(gameWindow_, SIGNAL(exit()), this, SLOT(close()));
    connect(gameWindow_, SIGNAL(mainMenu(bool)), this, SLOT(exitGame(bool)));

    mainLayout_ = new QStackedWidget(ui->centralwidget);

    mainLayout_->insertWidget(0, startWindow_);
    mainLayout_->insertWidget(1, gameWindow_);
    mainLayout_->insertWidget(2, highScoreWindow_);
    mainLayout_->setCurrentIndex(0);

    this->setCentralWidget(mainLayout_);
    setWindowTitle(QString("GalaxyQuest"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startView()
{
    mainLayout_->setCurrentIndex(0);
}

void MainWindow::exitGame(bool val)
{
    mainLayout_->setCurrentIndex(0);
    startWindow_->setGame(val);
}

void MainWindow::continueGame()
{
    mainLayout_->setCurrentIndex(1);
    if(!launch_)
    {
        auto *dialog = new StudentUI::StartDialog(gameWindow_->getPlayerName());
        dialog->exec();

        launch_ = true;

        delete dialog;
    }
}

void MainWindow::gameView(QString playerName)
{
    if(gameWindow_->getGame())
        gameWindow_->resetHard();

    else if(!gameWindow_->getGame())
        gameWindow_->startGame(playerName);

    continueGame();
}

void MainWindow::highscoreView()
{
    highScoreWindow_->updateScore();
    mainLayout_->setCurrentIndex(2);
}



