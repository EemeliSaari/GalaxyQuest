#include <QGridLayout>
#include <QBoxLayout>

#include "playerrepairdialog.hh"

namespace StudentUI
{

PlayerRepairDialog::PlayerRepairDialog(std::string serviceLocation,
                                       int price,
                                       int maximum,
                                       QWidget *parent)
    : value_(maximum), price_(price)
{
    setFixedSize(250,250);

    QGridLayout *layout = new QGridLayout(this);

    QString priceText = QString::number(price);
    QFrame *textFrame = makeLabel(QString::fromStdString(serviceLocation), priceText);

    if(value_ >= 1)
    {
        cancelButton_ = new QPushButton("Cancel");

        acceptButton_ = new QPushButton("Repair");
        acceptButton_->setFixedWidth(100);
        connect(acceptButton_, SIGNAL(clicked(bool)),
                this, SLOT(accept()));

        spinBox_ = new QSpinBox();
        spinBox_->setMaximum(maximum);
        spinBox_->setAlignment(Qt::AlignCenter);


        layout->addWidget(textFrame,0,0,1,0, Qt::AlignCenter);
        layout->addWidget(spinBox_,1,0,1,0, Qt::AlignCenter);
        layout->addWidget(acceptButton_, 2,0);
        layout->addWidget(cancelButton_,2,3);
    }
    else
    {
        cancelButton_ = new QPushButton("OK");
        layout->addWidget(textFrame,0,0,1,0, Qt::AlignCenter);
        layout->addWidget(cancelButton_,1,0,1,0,Qt::AlignCenter);
    }

    cancelButton_->setFixedWidth(100);
    connect(cancelButton_, SIGNAL(clicked(bool)),
            this, SLOT(reject()));
    setLayout(layout);
}

void PlayerRepairDialog::accept()
{
    emit acceptedRepair(spinBox_->value(), price_);
    done(1);
}

QFrame* PlayerRepairDialog::makeLabel(QString name, QString price)
{
    QString text;
    if(value_ >= 1)
        text = QString("Greetings from %1!<br/>"
                       "We offer to repair<br/>"
                       "your ship for decent<br/>"
                       "price of %2 for each<br/>"
                       "hitpoint.<br/><br/>"
                       "Do you accept?").arg(name,price);
    else if(value_ == 0)
        text = QString("Greetings, your ship<br/>"
                       "seems to be all fixed.<br/><br/>"
                       "Your're good to go!");
    else
        text = QString("I'm afraid you don't<br/>"
                       "have the credits to fix <br/>"
                       "your ship.");

    QLabel *label = new QLabel(text);
    label->setWordWrap(true);
    label->setTextFormat(Qt::RichText);

    QFrame *newFrame = new QFrame(this);
    newFrame->setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);

    QGridLayout *layout = new QGridLayout(newFrame);
    layout->addWidget(label,0,0);

    newFrame->setLayout(layout);

    return newFrame;
}

}
