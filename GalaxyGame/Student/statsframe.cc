#include <QGridLayout>
#include <QtWidgets>
#include <QString>
#include <QLayout>

#include "statsframe.hh"

namespace StudentUI
{

StatsFrame::StatsFrame(QWidget *parent)
    :parent_(parent)
{
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);

    auto layout = new QGridLayout(this);

    score_ = new QLabel(this);
    score_->text();

    credits_ = new QLabel(this);
    credits_->text();

    saved_ = new QLabel(this);
    saved_->text();

    lost_ = new QLabel(this);
    saved_->text();

    active_ = new QLabel(this);
    active_->text();

    //Init the texts.
    updateScore(0);
    updateCredits(0);
    updateSaved(0);
    updateLost(0);
    updateActive(0);

    //Put the Labels into a grid.
    layout->addWidget(createLabel(QString("Score: ")), 0, 0);
    layout->addWidget(score_, 0, 2);
    layout->addWidget(createLabel(QString("Credits: ")), 1, 0);
    layout->addWidget(credits_, 1, 2);
    layout->addWidget(createLabel(QString("Saved Ships: ")), 2, 0);
    layout->addWidget(saved_, 2, 2);
    layout->addWidget(createLabel(QString("Lost Ships: ")), 3, 0);
    layout->addWidget(lost_, 3, 2);
    layout->addWidget(createLabel(QString("Active Ships: ")), 4, 0);
    layout->addWidget(active_, 4, 2);

    setLayout(layout);
}

StatsFrame::~StatsFrame()
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

    delete this->layout();
}

QSize StatsFrame::sizeHint() const
{
    return QSize(10 + BoardWidth * frameWidth(), 5 + BoardHeight * frameWidth());
}

QSize StatsFrame::minimumSizeHint() const
{
    return QSize(BoardWidth, BoardHeight);
}

void StatsFrame::reset()
{
    updateCredits(0);
    updateScore(0);
    updateSaved(0);
    updateLost(0);
    updateActive(0);
}

void StatsFrame::updateScore(unsigned newValue)
{
    QString value;
    if(newValue == 0)
    {
        value = "-";
    }

    else
    {
        value = QString::number(newValue);
    }

    score_->setText(value);
    update();
}

void StatsFrame::updateCredits(unsigned newValue)
{
    QString value;
    if(newValue == 0)
    {
        value = "-";
    }
    else
    {
        value = QString::number(newValue);
    }

    credits_->setText(value);
}

void StatsFrame::updateSaved(unsigned newValue)
{
    QString value;
    if(newValue == 0)
    {
        value = "-";
    }
    else
    {
        value = QString::number(newValue);
    }

    saved_->setText(value);
}

void StatsFrame::updateLost(unsigned newValue)
{
    QString value;
    if(newValue == 0)
    {
        value = "-";
    }
    else
    {
        value = QString::number(newValue);
    }

    lost_->setText(value);
}

void StatsFrame::updateActive(unsigned newValue)
{
    QString value;
    if(newValue == 0)
    {
        value = "-";
    }

    else
    {
        value = QString::number(newValue);
    }

    active_->setText(value);
    update();
}

QLabel* StatsFrame::createLabel(const QString &text)
{
    auto label = new QLabel(text);
    return label;
}

}
