#include <cmath>
#include <QString>
#include <QGridLayout>
#include <QLabel>

#include "missiondialog.hh"

namespace StudentUI
{

MissionDialog::MissionDialog(double rng,
                             Student::RescueMission::MISSION_TYPE type,
                             std::string location,
                             QString playerName,
                             unsigned time,
                             QWidget *parent)
{
    QString text;

    int percentage = static_cast<int>(std::floor(rng * 100));

    if(type == Student::RescueMission::Meteorite)
        text = QString("*ALERT*<br/>"
                       "Urgent message from <b>%1</b><br/>*ALERT*<br/><br/>"
                       "'Hello commander %2, our system<br/>"
                       "is in great danger and we need the<br/>"
                       "amazing space pilot to save us from this<br/>"
                       "great meteorite.<br/>"
                       "I marked our location red in the map'<br/><br/>"
                       "Mission has %3 percentage chance to fail<br/>"
                       "Mission fails in %4 turns.").arg(QString::fromStdString(location),
                                                         playerName,
                                                         QString::number(percentage),
                                                         QString::number(time));
    else if(Student::RescueMission::Decease)
        text = QString("*ALERT*<br/> "
                       "Urgent message from <b>%1</b><br/>*ALERT*<br/><br/>"
                       "'Hello commander %2, our system<br/>"
                       "is in great danger and we need the<br/>"
                       "amazing space pilot to save us from this<br/>"
                       "horrible decease that might kill us all.'<br/><br/>"
                       "Mission has %3 percentage chance to fail<br/>"
                       "Mission fails in %4 turns.").arg(QString::fromStdString(location),
                                                         playerName,
                                                         QString::number(percentage),
                                                         QString::number(time));
    else if(Student::RescueMission::SkyNet)
        text = QString("*ALERT*<br/>"
                       "Urgent message from <b>%1</b><br/>*ALERT*<br/><br/>"
                       "'Hello commander %2, our system<br/>"
                       "is in great danger and we need the<br/>"
                       "amazing space pilot to save us from this<br/>"
                       "ravageing skynet terminator that one Teekkari<br/>"
                       "deployed to our planet.'<br/><br/>"
                       "Mission has %3 percentage chance to fail<br/>"
                       "Mission fails in %4 turns.").arg(QString::fromStdString(location),
                                                         playerName,
                                                         QString::number(percentage),
                                                         QString::number(time));
    else
        text = QString("*ALERT*<br/>"
                       "Urgent message from <b>%1</b><br/>*ALERT*<br/><br/>"
                       "'Hello commander %2, our system<br/>"
                       "is in great danger and we need the<br/>"
                       "amazing Teekkari to save us from this<br/>"
                       "bewerage shortage - will you bring us<br/>"
                       "the brews?'<br/><br/>"
                       "Mission has %3 percentage chance to fail<br/>"
                       "Mission fails in %4 turns.").arg(QString::fromStdString(location),
                                                         playerName,
                                                         QString::number(percentage),
                                                         QString::number(time));

    okButton_ = new QPushButton("OK");
    okButton_->setFixedWidth(100);
    connect(okButton_, SIGNAL(clicked(bool)),
            this, SLOT(accept()));

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
    layout->addWidget(okButton_,1,0,1,0,Qt::AlignCenter);

    setLayout(layout);

    this->layout()->setSizeConstraint( QLayout::SetFixedSize );
}

}
