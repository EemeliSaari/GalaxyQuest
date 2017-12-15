#include "highscorewindow.hh"
#include "highscoresystem.hh"
#include <iostream>

#include <memory>

namespace StudentUI
{

HighScoreWindow::HighScoreWindow(QObject *parent)
    : parent_(parent)
{
    layout_ = new QVBoxLayout(this);
    layout_->setAlignment(Qt::AlignCenter);
    setLayout(layout());
}

void HighScoreWindow::updateScore()
{
    if(!(this->layout()->isEmpty()))
    {
        QLayoutItem *item;
        QWidget *widget;

        while (item = this->layout()->takeAt(0))
        {
            if ((widget = item->widget()) != 0)
            {
                widget->hide();
                delete widget;
            }
            else
            {
                delete item;
            }
        }
    }
    initialize();
}

void HighScoreWindow::initialize()
{
    title_ = new QLabel("TOP 10 SCORES:");

    QFont font("Arial", 20, QFont::Bold);
    title_->setFont(font);

    backBtn_ = new QPushButton("Go back");
    backBtn_->setFixedWidth(100);
    auto hs = std::make_shared<Student::HighScoreSystem>();
    auto rankings = hs->getList();

    layout_->addWidget(title_);

    for(int i = 0; i < rankings.size(); ++i)
    {
        QString playerName = QString::fromStdString(rankings.at(i).player);
        QString playerScore = QString::number(rankings.at(i).score);
        QString index = QString::number(i+1);
        QString labelText = index + ". " + playerName + "  -  " + playerScore + " points";
        labels[i] = new QLabel("");
        labels[i]->setText(labelText);
        layout_->addWidget(labels[i]);
    }

    layout_->addWidget(backBtn_);
    connect(backBtn_, SIGNAL(clicked(bool)), this, SLOT(pressedBack()));
}

void HighScoreWindow::pressedBack()
{
    emit goBack();
}

}


