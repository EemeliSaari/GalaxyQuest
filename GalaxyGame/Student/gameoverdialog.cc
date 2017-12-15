#include <QLabel>
#include <QGridLayout>

#include "gameoverdialog.hh"

namespace StudentUI
{

GameOverDialog::GameOverDialog(bool enoughForHighScore,
                               QString playerName,
                               unsigned score,
                               QWidget *parent)
{
    QString text;
    QString scoreNumber = QString::number(score);

    if(enoughForHighScore)
    {
        text = QString("<b>Game Over.</b><br>"
                       "<br>"
                       "You did well, Commander <b>%1</b> !<br>"
                       "Your score was <b> %2 </b> and you got to the top-10 ranking list!!<br>"
                       "You truly are an Amazing Space Pilot!").arg(playerName, scoreNumber);
    }
    else
    {
        text = QString("<b>Game Over.</b><br>"
                       "<br>"
                       "Better luck next time, Commander <b>%1</b> !<br>"
                       "Your score was <b>%2</b>.<br>").arg(playerName, scoreNumber);


    }

    mainMenuBtn_ = new QPushButton("Back to main menu");
    mainMenuBtn_->setFixedWidth(200);
    connect(mainMenuBtn_, SIGNAL(clicked(bool)), this, SLOT(accept()));

    QLabel *label = new QLabel(text);
    label->setWordWrap(true);
    label->setTextFormat(Qt::RichText);

    labelFrame_ = new QFrame(this);
    labelFrame_->setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);

    QGridLayout *frameLayout = new QGridLayout(labelFrame_);
    frameLayout->addWidget(label);

    labelFrame_->setLayout(frameLayout);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(labelFrame_,0,0,1,0,Qt::AlignCenter);
    layout->addWidget(mainMenuBtn_,1,0,1,0,Qt::AlignCenter);

    setLayout(layout);

    this->layout()->setSizeConstraint( QLayout::SetFixedSize );
}

}
