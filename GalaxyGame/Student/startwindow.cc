#include <QVBoxLayout>
#include <QPixmap>

#include <iostream>
#include "startwindow.hh"

namespace StudentUI
{

StartWindow::StartWindow(QObject *parent)
    : parent_(parent), gameOn_(false), defaultName_("unnamed")
{
    playerNameLabel_ = new QLabel("Enter your name: ");

    auto picLabel = new QLabel(this);
    picLabel->setPixmap(QPixmap(QString("galaxyquest.png")));
    picLabel->setAlignment(Qt::AlignCenter);

    playerNameField_ = new QLineEdit("");
    playerNameField_->setFixedWidth(300);
    playerNameField_->setMaxLength(12);
    playerNameField_->setPlaceholderText(defaultName_);

    startGameBtn_ = new QPushButton("Start Game");
    startGameBtn_->setFixedWidth(300);

    highScoresBtn_ = new QPushButton("HighScores");
    highScoresBtn_->setFixedWidth(300);

    quit_ = new QPushButton("Exit game");
    quit_->setFixedWidth(300);

    continueButton_ = new QPushButton("Continue");
    continueButton_->setFixedWidth(300);
    continueButton_->hide();

    connect(continueButton_, SIGNAL(clicked(bool)), this, SLOT(pressedContinue()));
    connect(startGameBtn_, SIGNAL(clicked(bool)), this, SLOT(pressedStart()));
    connect(highScoresBtn_, SIGNAL(clicked(bool)), this, SLOT(pressedHighScore()));
    connect(quit_, SIGNAL(clicked(bool)), this, SLOT(quitGame()));

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(picLabel);
    layout->addWidget(playerNameLabel_);
    layout->addWidget(playerNameField_);
    layout->addWidget(startGameBtn_);
    layout->addWidget(continueButton_);
    layout->addWidget(highScoresBtn_);
    layout->addWidget(quit_);

    setLayout(layout);
}

void StartWindow::quitGame()
{
    emit exitSignal();
}

void StartWindow::setGame(bool val)
{
    gameOn_ = val;
    if(gameOn_)
    {
        continueButton_->show();
    }
    else
        continueButton_->hide();
}

bool StartWindow::getGame()
{
    return gameOn_;
}

void StartWindow::pressedStart()
{
    auto field = playerNameField_->text();
    auto check = field.split(' ', QString::SkipEmptyParts);

    if(check.size() > 0)
        emit startGame(playerNameField_->text());
    else
        emit startGame(defaultName_);
}

void StartWindow::pressedHighScore()
{
    emit checkHighScore();
}


void StartWindow::pressedExit()
{
    emit exitGame();
}

void StartWindow::pressedContinue()
{
    emit continueGame();
}

}//Student

