#include <QHBoxLayout>

#include "starinfoframe.hh"

namespace StudentUI
{

StarInfoFrame::StarInfoFrame(QWidget *parent)
{
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    tab_ = new QTabWidget(this);

    general_ = new QLabel(tab_);
    general_->setTextFormat(Qt::RichText);
    general_->setAlignment(Qt::AlignTop);

    ships_ = new QLabel(tab_);
    ships_->setTextFormat(Qt::RichText);
    ships_->setAlignment(Qt::AlignHCenter);

    tab_->addTab(general_, "Info");
    tab_->addTab(ships_, "Ships");

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(1);
    mainLayout->addWidget(tab_);
    setLayout(mainLayout);
}

StarInfoFrame::~StarInfoFrame()
{
    delete tab_;
}

QSize StarInfoFrame::sizeHint() const
{
    return QSize(10 + BoardWidth * frameWidth(), 5 + BoardHeight * frameWidth());
}

QSize StarInfoFrame::minimumSizeHint() const
{
    return QSize(BoardWidth, BoardHeight);
}

void StarInfoFrame::reset()
{
    ships_->setText("");
    general_->setText("");
}

void StarInfoFrame::updateInfo(std::shared_ptr<Common::StarSystem> system,
                               std::vector<std::shared_ptr<Common::Ship>> ships)
{
    QString generalText;
    QString shipText;

    QString sysName = QString::fromStdString(system->getName());
    QString sysPop = QString::number(system->getPopulation());
    QString sysEco = getEconomy(system->getEconomy());
    QString sysId = QString::number(system->getId());
    QString sysCoord = QString::fromStdString(system->getCoordinates().toString());

    QString sysRep;
    if(system->canRepair())
        sysRep = QString("Yes");
    else
        sysRep = QString("No");

    generalText = QString("Name: %1<br/>"
                          "Pop: %2<br/>"
                          "Eco: %3<br/>"
                          "ID: %4<br/>"
                          "Coord: %5<br/>"
                          "Rep: %6<br/>").arg(sysName,sysPop,sysEco,sysId,sysCoord, sysRep);
    general_->setText(generalText);

    if(ships.size() > 7)
        shipText = QString("Ships: %1").arg(QString::number(ships.size()));
    else
        for(auto it = ships.begin(); it < ships.end(); ++it)
        {
            shipText.append(QString("%1<br/>").arg(QString::fromStdString((*it)->getName())));
        }
    ships_->setText(shipText);



    update();
}

QString StarInfoFrame::getEconomy(Common::StarSystem::ECONOMY_TYPE type)
{
    QString eco;
    switch(type)
    {
        case Common::StarSystem::Refinery : eco = QString("Refinery");
            break;
        case Common::StarSystem::Extraction : eco = QString("Extraction");
            break;
        case Common::StarSystem::HiTech : eco = QString("HiTech");
            break;
        case Common::StarSystem::Industrial : eco = QString("Industrial");
            break;
        case Common::StarSystem::Tourism : eco = QString("Tourism");
            break;
        case Common::StarSystem::Agriculture : eco = QString("Agriculture");
            break;
        case Common::StarSystem::Service : eco = QString("Service");
            break;
        case Common::StarSystem::Military : eco = QString("Military");
            break;
        case Common::StarSystem::Terraforming : eco = QString("Terraforming");
            break;
        case Common::StarSystem::Colony : eco = QString("Colony");
            break;
        case Common::StarSystem::None : eco = QString("-");
            break;
    }

    return eco;
}




}
