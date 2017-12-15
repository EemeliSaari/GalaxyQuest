#include "hpbar.hh"

namespace StudentUI
{

HpBar::HpBar(QWidget *parent, int maxHp, int maxUncertainty)
    : defaultHp_(maxHp), defaultUncertainty_(0)
{
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);

    hp_ = new QProgressBar(this);
    hp_->setMaximum(defaultHp_);
    hp_->setMinimum(0);
    hp_->setValue(defaultHp_);
    hp_->setFixedWidth(150);

    hpText_ = new QLabel("HP:");
    hpText_->setAlignment(Qt::AlignCenter);

    uncertainty_ = new QProgressBar(this);
    uncertainty_->setMaximum(maxUncertainty);
    uncertainty_->setMinimum(0);
    uncertainty_->setValue(0);
    uncertainty_->setFixedWidth(150);

    uncertaintyText_ = new QLabel("Uncertainty:");
    uncertaintyText_->setAlignment(Qt::AlignCenter);

    layout_ = new QGridLayout(this);

    layout_->addWidget(hpText_,0, 0);
    layout_->addWidget(hp_,1, 0);
    layout_->addWidget(uncertaintyText_, 0, 3);
    layout_->addWidget(uncertainty_, 1, 3);

    setLayout(layout_);
}

HpBar::~HpBar()
{
    delete layout_;
}

void HpBar::reset()
{
    hp_->setValue(defaultHp_);
    uncertainty_->setValue(defaultUncertainty_);
}

void HpBar::updateHp(int newValue)
{
    hp_->setValue(newValue);
}

void HpBar::updateUncertainty(int newValue)
{
    uncertainty_->setValue(newValue);
}

}
