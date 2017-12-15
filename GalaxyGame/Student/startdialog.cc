#include "startdialog.hh"

namespace StudentUI
{

StartDialog::StartDialog(QString playerName, QWidget *parent)
    :playerName_(playerName)
{
    auto general = createGeneral();

    auto mission = createMissions();
    mission->setAlignment(Qt::AlignTop);

    auto score = createScore();
    score->setAlignment(Qt::AlignTop);

    acceptButton_ = new QPushButton(this);
    acceptButton_->setText("OK");
    connect(acceptButton_, SIGNAL(clicked(bool)), this, SLOT(accept()));

    tab_ = new QTabWidget(this);
    tab_->addTab(general, "General");
    tab_->addTab(mission, "Missions");
    tab_->addTab(score, "Scores");

    layout_ = new QVBoxLayout(this);
    layout_->addWidget(tab_);
    layout()->addWidget(acceptButton_);

    setLayout(layout_);

    setFixedSize(this->layout()->sizeHint());
}

QLabel *StartDialog::createGeneral()
{
    QString text = QString("<b>Welcome to GalaxyQuest,<br/>"
                           "super teekkari %1!</b><br/><br/>"
                           "Your goal is to maintain economical<br/>"
                           "balance in the galaxy by maintaining<br/>"
                           "at least 15 cargo ships in the sky<br/>"
                           "at all times. Also help citizens of<br/>"
                           "Star systems who might ask you for help.<br/><br/>"
                           "Here's some introductions:<br/>"
                           "1. Cyan system is where you are.<br/>"
                           "2. Cyan circles are systems in your range.<br/>"
                           "3. Purple circles are the ships in the system.<br/>"
                           "4. Yellow circle is salvageable ship<br/>"
                           "5. Red circle is ship in trouble<br/>"
                           "6. Red cross is repair and buy station<br/><br/>"
                           "Good luck!").arg(playerName_);
    QLabel *label = new QLabel(text);
    label->setWordWrap(true);
    label->setTextFormat(Qt::RichText);
    return label;
}

QLabel *StartDialog::createMissions()
{
    QString text = QString("Info about missions:<br/><br/>"
                           "Missions spawn to random locations<br/>"
                           "and they give you dialog to info their<br/>"
                           "location and how many turns until they<br/>"
                           "expire.<br/>"
                           "<b>On attempt failure:</b> Player 1 to 10 damage<br/>"
                           "<b>On expire:</b> repair and buy ability disables in<br/>"
                           "the system in question<br/>"
                           "<b>On success:</b> Player is rewarded credits based<br/>"
                           "on the difficulty of the mission (rng*1000)");

    QLabel *label = new QLabel(text);
    label->setWordWrap(true);
    label->setTextFormat(Qt::RichText);
    return label;
}

QLabel *StartDialog::createScore()
{
    QString text = QString("Info about scoring:<br/><br/>"
                           "<b>Successful mission:</b> credits, 10 points<br/>"
                           "<b>Successful ship save:</b> 50 points<br/>"
                           "<b>Ship salvage:</b> 150 credits<br/><br/>"
                           "When game ends the end score will be<br/>"
                           "added to the highscore list.");

    QLabel *label = new QLabel(text);
    label->setWordWrap(true);
    label->setTextFormat(Qt::RichText);
    return label;
}

}
