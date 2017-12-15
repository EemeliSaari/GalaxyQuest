#include "missioncompleteddialog.hh"

namespace StudentUI
{

MissionCompletedDialog::MissionCompletedDialog(bool completed, QWidget *parent)
{
    QString text;

    if(completed)
    {
        text = QString("Mission completed!<br>"
                       "You got some reward.");
    }
    else
    {
        text = QString("Mission failed!<br>"
                       "You need to focus son!");
    }

    continueBtn_ = new QPushButton("Continue");
    continueBtn_->setFixedWidth(100);
    connect(continueBtn_, SIGNAL(clicked(bool)), this, SLOT(accept()));

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
    layout->addWidget(continueBtn_,1,0,1,0,Qt::AlignCenter);

    setLayout(layout);

    this->layout()->setSizeConstraint( QLayout::SetFixedSize );

}

}
