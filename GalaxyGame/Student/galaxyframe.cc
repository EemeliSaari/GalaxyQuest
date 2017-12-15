#include <algorithm>
#include <cmath>

#include <QHBoxLayout>
#include <QGraphicsRectItem>
#include <QtMath>
#include <QString>

#include "galaxyframe.hh"

namespace StudentUI
{

GalaxyFrame::GalaxyFrame(QWidget *parent)
    : QFrame(parent)
{
    initialized_ = false;
}

GalaxyFrame::~GalaxyFrame()
{
    delete this->layout();
}

void GalaxyFrame::populateScene(std::shared_ptr<Common::StarSystem::StarSystemVector> starSystems)
{
    // Creating the scene
    scene_ = new QGraphicsScene(this);

    // Adding systems to the scene coordinates.
    int xx = 0;
    for (int i = -25; i < 25; ++i)
    {
        ++xx;
        int yy = 0;
        for (int j = -25; j < 25; ++j)
        {
            ++yy;
            auto start = starSystems.get()->begin();
            auto end = starSystems.get()->end();

            auto it = std::find_if(start, end,
                                   [i, j](std::shared_ptr<Common::StarSystem> target)
                                   {return target->getCoordinates().x == i && target->getCoordinates().y == j;});

            if (it != end)
            {
                qreal x = i * 25 + 250;
                qreal y = j * 25 + 250;


                auto systemName = (*it)->getName();

                std::shared_ptr<SolarSystemItem> item = std::make_shared<SolarSystemItem>(xx,
                                                                                          yy,
                                                                                          systemName);
                connect(item.get(), SIGNAL(imSelected(std::string)),
                        this, SLOT(systemSelected(std::string)));
                connect(item.get(), SIGNAL(playerMovingHere(std::string)),
                        this, SLOT(playerInitMove(std::string)));
                connect(item.get(), SIGNAL(savedShip(std::shared_ptr<Common::Ship>)),
                        this, SLOT(shipMissionSuccess(std::shared_ptr<Common::Ship>)));
                connect(item.get(), SIGNAL(tryCompleteMission(std::string)), this,
                        SLOT(completingMission(std::string)));
                connect(item.get(), SIGNAL(salvagedShip(std::shared_ptr<Common::Ship>)),
                        this, SLOT(completeSalvage(std::shared_ptr<Common::Ship>)));
                connect(item.get(), SIGNAL(initBuying(std::string)),
                        this, SLOT(playerInitBuy(std::string)));
                connect(item.get(), SIGNAL(initRepairing(std::string)),
                        this, SLOT(playerInitRepair(std::string)));

                item->setRepair((*it)->canRepair());

                item->setPos(QPointF(x,y));
                item->setZValue(1);
                scene_->addItem(item.get());

                //Store the items to easily accessable map.
                starMap_[(*it)->getName()] = item;
            }
        }
    }

    // The way Qt calculates the scene is that it calculates the bounding rectangle of
    // items in it. So we'll need to add two corner blocks to set the scene to display
    // all the objects properly.
    int height = 350;
    for(int i = 0; i < 2; ++i)
    {
        int width = 350;
        height += 500 * ((-1) * i%2);
        for(int j = 0; j < 2; ++j)
        {
            width += 500 * ((-1)*j%2);

            qreal x = width *3;
            qreal y = height *3;

            QGraphicsRectItem *r = new QGraphicsRectItem(i,j,5,5);
            r->setBrush(QBrush(Qt::black));
            r->setPos(x,y);
            scene_->addItem(r);
        }
    }
}

void GalaxyFrame::makeConnections(std::map<std::string, std::vector<std::string> > connections)
{
    for(auto itMap = connections.begin(); itMap != connections.end(); ++itMap)
    {
        auto middleItem = starMap_[(*itMap).first];
        QPointF centerPoint = middleItem->pos();

        auto x = middleItem->boundingRect().width() / 2;

        auto vec = (*itMap).second;

        if(!(vec.empty()))
        {
            for(auto it = vec.begin(); it != vec.end(); ++it)
            {
                auto endItem = starMap_[(*it)];
                QPointF endPoint = endItem->pos();

                scene_->addLine(centerPoint.rx() + x,
                                centerPoint.ry() + x,
                                endPoint.rx() + x,
                                endPoint.ry() + x,
                                QPen(Qt::darkGray, 1));
            }
        }
    }
}

void GalaxyFrame::focusOnPlayer()
{
    if(initialized_)
    {
        auto item = starMap_[playerLocation_];
        view_->view()->centerOn(item->pos());
        update();
    }
}

void GalaxyFrame::playerMoved(std::string newLoc, std::vector<std::string> inRange)
{
    auto playerLocItem = starMap_[newLoc];
    playerLocItem->setHostingPlayer(true);

    if(initialized_) // Set previous systems out of range.
    {
        auto oldLocItem = starMap_[playerLocation_];
        oldLocItem->setHostingPlayer(false);

        for(auto it = inPlayerRange_.begin(); it != inPlayerRange_.end(); ++it)
        {
            auto inRangeItem = starMap_[*it];
            inRangeItem->setRange(false);
        }
    }

    for(auto it = inRange.begin(); it != inRange.end(); ++it)
    {
        auto inRangeItem = starMap_[*it];
        inRangeItem->setRange(true);
    }

    playerLocation_ = newLoc;
    inPlayerRange_ = inRange;
}

void GalaxyFrame::systemSelected(std::string name)
{
    emit updateThis(name);
}

void GalaxyFrame::shipMoving(std::shared_ptr<Common::Ship> ship,
                             Common::Point origin,
                             Common::Point target)
{
    auto it = shipsInSky_.find(ship);

    auto a = origin.distanceTo(target);
    auto b = static_cast<double>(origin.y - target.y);
    auto r = std::asin(b/a);
    auto angle = qRadiansToDegrees(r);

    qreal x = target.x * 25 + 250;
    qreal y = target.y * 25 + 250;

    if(it != shipsInSky_.end() && !(shipsInSky_.empty()))
    {
        auto item = (*it).second;
        item->setPos(x, y);
        item->setRotation(angle);
    }
    else
    {
        std::shared_ptr<ShipItem> item = std::make_shared<ShipItem>(target.x, target.y);

        item->setPos(x,y);
        item->setRotation(angle);
        item->setZValue(2);
        scene_->addItem(item.get());

        shipsInSky_[ship] = item;
    }
}

void GalaxyFrame::addShips(std::shared_ptr<Common::Ship> ship)
{
    auto item = starMap_[ship->getLocation()->getName()];
    item->shipEntered(ship);

    auto it = shipsInSky_.find(ship);

    if(it != shipsInSky_.end() && !(shipsInSky_.empty()))
    {
        shipsInSky_.erase(it);
    }
}

void GalaxyFrame::shipLeaving(std::shared_ptr<Common::Ship> ship, std::shared_ptr<Common::StarSystem> starSystem)
{
    try
    {
        auto from = starMap_[starSystem->getName()];
        from->shipLeft(ship);
    }
    catch(...)
    {
        emit errorInExecution();
    }
}

void GalaxyFrame::shipMission(std::shared_ptr<Common::Ship> ship)
{
    try
    {
        auto location = ship->getLocation()->getName();
        auto item = starMap_[location];

        item->shipInTrouble(ship);
        item->shipLeft(ship);
    }
    catch(...)
    {
        emit errorInExecution();
    }
}

void GalaxyFrame::shipMissionFail(std::shared_ptr<Common::Ship> ship)
{
    try
    {
        auto item = starMap_[ship->getLocation()->getName()];
        item->shipNotInTrouble(ship);
    }
    catch(...)
    {
        emit errorInExecution();
    }
}

void GalaxyFrame::shipMissionSuccess(std::shared_ptr<Common::Ship> ship)
{
    try
    {
        auto item = starMap_[ship->getLocation()->getName()];
        item->shipNotInTrouble(ship);
        item->shipEntered(ship);

        emit shipSaved(ship);
    }
    catch(...)
    {
        emit errorInExecution();
    }
}

void GalaxyFrame::completeSalvage(std::shared_ptr<Common::Ship> ship)
{
    try
    {
        auto item = starMap_[ship->getLocation()->getName()];
        item->removeSalvage(ship);

        emit salvageShip(ship);
    }
    catch(...)
    {
        emit errorInExecution();
    }
}

void GalaxyFrame::salvageMission(std::shared_ptr<Common::Ship> ship)
{
    try
    {
        auto item = starMap_[ship->getLocation()->getName()];
        item->addSalvage(ship);
    }
    catch(...)
    {
        emit errorInExecution();
    }
}

void GalaxyFrame::playerActionsUp()
{
    auto playerItem = starMap_[playerLocation_];
    playerItem->setActions(false);

    for(auto it = inPlayerRange_.begin(); it != inPlayerRange_.end(); ++it)
    {
        auto rangeItem = starMap_[(*it)];
        rangeItem->setActions(false);
    }
}

void GalaxyFrame::playerMovesUp()
{
    for(auto it = inPlayerRange_.begin(); it != inPlayerRange_.end(); ++it)
    {
        auto rangeItem = starMap_[(*it)];
        rangeItem->setMoveable(false);
    }
}

void GalaxyFrame::newTurn()
{
    auto playerItem = starMap_[playerLocation_];
    playerItem->setActions(true);

    for(auto it = inPlayerRange_.begin(); it != inPlayerRange_.end(); ++it)
    {
        auto rangeItem = starMap_[(*it)];
        rangeItem->setActions(true);
        rangeItem->setMoveable(true);
    }
}

void GalaxyFrame::resetScene()
{
    delete this->layout();
    starMap_.clear();
    shipsInSky_.clear();
    delete scene_;
    view_.reset();
}

void GalaxyFrame::playerInitRepair(std::string location)
{
    emit repairInit(location);
}

void GalaxyFrame::playerInitBuy(std::string location)
{
    emit buyInit(location);
}

void GalaxyFrame::playerInitMove(std::string from)
{
    emit movePlayerHere(from);
}

void GalaxyFrame::newMission(std::string to)
{
    auto item = starMap_[to];
    item->setMission(true);
}

void GalaxyFrame::completingMission(std::string from)
{
    emit tryMission(from);
}

void GalaxyFrame::missionExpired(std::string from)
{
    auto item = starMap_[from];
    item->setMission(false);
    item->setRepair(false);
}

void GalaxyFrame::initialize(std::shared_ptr<Common::StarSystem::StarSystemVector> starSystems,
                             std::map<std::string, std::vector<std::string> > connections)
{
    populateScene(starSystems);
    makeConnections(connections);

    view_ = std::make_shared<GalaxyView>(this);

    view_->view()->setScene(scene_);

    // Paint the background.
    view_->view()->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(view_.get());
    setLayout(layout);
}

void GalaxyFrame::setInitialized()
{
    initialized_ = true;
}

}//StudentUI
