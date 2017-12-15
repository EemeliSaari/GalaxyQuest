#include <cmath>
#include <QGridLayout>

#include "playerbuydialog.hh"

namespace StudentUI
{

const int PlayerBuyDialog::SHIP_PRICE = 1000;

PlayerBuyDialog::PlayerBuyDialog(std::string location,
                                 int playerCredits,
                                 QWidget *parent)
{
    setFixedSize(250,250);

    QGridLayout *layout = new QGridLayout(this);
    QFrame *textFrame = makeLabel(QString::fromStdString(location));

    value_ = static_cast<int>(std::floor(playerCredits / SHIP_PRICE));

    if(value_ >= 1)
    {
        cancelButton_ = new QPushButton("Cancel");

        acceptButton_ = new QPushButton("Buy");
        acceptButton_->setFixedWidth(100);
        connect(acceptButton_, SIGNAL(clicked(bool)),
                this, SLOT(accept()));

        spinBox_ = new QSpinBox(this);
        spinBox_->setMaximum(value_);
        spinBox_->setAlignment(Qt::AlignCenter);

        layout->addWidget(textFrame,0,0,1,0, Qt::AlignCenter);
        layout->addWidget(spinBox_,1,0,1,0, Qt::AlignCenter);
        layout->addWidget(acceptButton_, 2, 0);
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

void PlayerBuyDialog::accept()
{
    int amount = spinBox_->value();
    int val = SHIP_PRICE * amount;

    emit completePurchase(amount, val);
    done(1);
}

QFrame *PlayerBuyDialog::makeLabel(QString name)
{
    QString text;
    if(value_ >= 1)
        text = QString("Welcome to legendary<br/>"
                       "ship bazaar of %1.<br/>"
                       "We offer the greatest<br/>"
                       "ships in the whole galaxy!<br/><br/>"
                       "Price for you is only 1000<br/>"
                       "credits each.").arg(name);
    else
        text = QString("I'm afraid %1 can't<br/>"
                       "offer any ships with<br/>"
                       "your budget.").arg(name);

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

} //StudentUI
