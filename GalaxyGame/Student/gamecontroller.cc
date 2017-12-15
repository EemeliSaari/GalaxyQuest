#include "gamecontroller.hh"
#include "playerrepairdialog.hh"
#include "playerbuydialog.hh"
#include "point.hh"
#include "rescuemission.hh"
#include "utility"

namespace Student
{

GameController::GameController(std::shared_ptr<Galaxy> galaxy,
                   std::shared_ptr<EventHandler> events,
                   std::shared_ptr<Common::IGameRunner> gameRunner)
    : galaxy_(galaxy), events_(events), gameRunner_(gameRunner), turnCounter_(0)
{
    standardRange_ = 12.0;
    standardTime_ = 7;

    auto start = galaxy->getStarSystemByName("Sol");

    std::shared_ptr<QuantumMap> playersMap = std::make_shared<QuantumMap>(galaxy_);
    std::shared_ptr<QuantumEngine> playersEngine = std::make_shared<QuantumEngine>(playersMap);

    // initialize playership.
    playerShip_ = std::make_shared<PlayerShip>(playersEngine, start, "Havier");

    // Connect playership to handler.
    connect(playerShip_.get(), SIGNAL(actionsUsed()),
            events_.get(), SLOT(actionsUsed()));
    connect(playerShip_.get(), SIGNAL(movesUsed()),
            events_.get(), SLOT(movesUsed()));
    connect(playerShip_.get(), SIGNAL(iMoved(std::shared_ptr<Common::StarSystem>, std::vector<std::shared_ptr<Common::StarSystem>>)),
            events_.get(), SLOT(playerMoved(std::shared_ptr<Common::StarSystem>, std::vector<std::shared_ptr<Common::StarSystem>>)));
    connect(playerShip_.get(), SIGNAL(updateHp(int)),
            events_.get(), SLOT(playerHp(int)));
    connect(playerShip_.get(), SIGNAL(uncertaintyUpdated(int)),
            events_.get(), SLOT(playerUncertainty(int)));
    connect(playerShip_.get(), SIGNAL(engineBroke()),
            events_.get(), SLOT(playerBroke()));
}

GameController::~GameController()
{
}

void GameController::spawnShips(unsigned value)
{
    gameRunner_->spawnShips(value);
}

std::shared_ptr<Common::StarSystem::StarSystemVector> GameController::getStarSystems()
{
    return galaxy_->getStarSystems();
}

std::map<std::string, std::vector<std::string> > GameController::getMap()
{
    return playerShip_->getEngine()->getStringMap();
}

void GameController::initialize()
{
    playerShip_->setinitialized();
}

void GameController::setPlayerName(std::string name)
{
    playerShip_->setName(name);
}

void GameController::turnEnded()
{
    if(missionsMap_.size() < 1) //So far keep just one mission
    {
        spawnMission();
    }
    playTurn();
}

void GameController::completeSaveShip(std::shared_ptr<Common::Ship> target)
{
    target->getEngine()->repair(target->getEngine()->getMaxHealth());
}

void GameController::playTurn()
{
    //Do all the things needed here
    for(auto it = missionsMap_.begin(); it != missionsMap_.end(); ++it)
    {
        if(!((*it).second->getStatus()))
        {
            missionsMap_.erase(it);
        }
    }
    ++turnCounter_;

    if(turnCounter_ % 20 == 0)
        gameRunner_->spawnShips(1);

    gameRunner_->createActions();
    gameRunner_->doActions();

    //at the end emit the turnEnded
    events_->turnPlayed();
}

void GameController::movePlayer(std::string newLocation)
{
    auto newSystem = galaxy_->getStarSystemByName(newLocation);
    playerShip_->setLocation(newSystem);
}

void GameController::completeMission(std::string locationName)
{
    auto mission = missionsMap_[locationName];
    mission->tryComplete();
    playerShip_->doAction();
}

void GameController::missionSuccess(std::shared_ptr<Common::StarSystem> location, int reward)
{
    events_->rescueCompleted(location, reward);
}

void GameController::missionAttemptFail()
{
    //Player takes dmg
    unsigned randomAmount = static_cast<unsigned>(Common::randomMinMax(1, 10));
    playerShip_->takeDmg(randomAmount);
}

void GameController::missionFail(std::shared_ptr<Common::StarSystem> location)
{
    events_->rescueFailed(location);
}

void GameController::salvageShip(std::shared_ptr<Common::Ship> ship)
{
    galaxy_->removeShip(ship);
    events_->shipRemoved(ship);
}

void GameController::openRepair(std::string location)
{
    auto system = galaxy_->getStarSystemByName(location);
    auto type = system->getEconomy();

    int playerCredits = events_->getCredits();
    int price;
    if(type == Common::StarSystem::Industrial)
        price = 12;
    else if(type == Common::StarSystem::HiTech)
        price = 10;
    else if(type == Common::StarSystem::Service)
        price = 8;
    else
        price = 15;

    auto maxRepair = static_cast<int>(std::floor(playerCredits / price));

    int max;
    if(playerShip_->getEngine()->getMaxHealth() - playerShip_->getEngine()->getHealth() == 0)
        max = 0;
    else if(maxRepair > playerShip_->getEngine()->getHealth())
        max = playerShip_->getEngine()->getMaxHealth() - playerShip_->getEngine()->getHealth();
    else if(maxRepair == 0)
        max = -1;
    else
        max = maxRepair;

    auto *dialog = new StudentUI::PlayerRepairDialog(location, price, max);

    connect(dialog, SIGNAL(acceptedRepair(int, int)), this, SLOT(repair(int, int)));
    connect(dialog, SIGNAL(rejected()), events_.get(), SLOT(unPause()));

    dialog->exec();

    delete dialog;
}

void GameController::repair(int amount, int price)
{
    playerShip_->repair(static_cast<unsigned>(amount));
    int creditAmount = amount * price;

    events_->removeCredits(static_cast<unsigned>(creditAmount));
    playerShip_->doAction();

    events_->unPause();
}

void GameController::openBuy(std::string location)
{
    auto *dialog = new StudentUI::PlayerBuyDialog(location, events_->getCredits());

    connect(dialog, SIGNAL(completePurchase(int,int)), this, SLOT(buy(int,int)));
    connect(dialog, SIGNAL(rejected()), events_.get(), SLOT(unPause()));

    dialog->exec();

    delete dialog;
}

void GameController::buy(int amount, int price)
{
    gameRunner_->spawnShips(static_cast<unsigned>(amount));

    events_->removeCredits(price);
    playerShip_->doAction();

    events_->unPause();
}

void GameController::collectInfo(std::string location)
{
    auto system = galaxy_->getStarSystemByName(location);
    auto ships = galaxy_->getShipsInStarSystem(location);

    events_->receiveInfo(system, ships);
}

void GameController::spawnMission()
{
    auto currentLocation = playerShip_->getLocation();
    auto newLocation = galaxy_->getRandomSystemOutsideRange(currentLocation, standardRange_);
    auto newCoordinates = newLocation->getCoordinates();
    auto rangeToMission = currentLocation->getCoordinates().distanceTo(newCoordinates);

    // time scales up the further away the mission is
    auto time = static_cast<double>(standardTime_) * rangeToMission/standardRange_;

    QString name = QString::fromStdString(playerShip_->getName());

    auto newMission = std::make_shared<RescueMission>(newLocation,
                                                      unsigned(std::abs(time)),
                                                      name);
    //Connect Mission to EventHanler slots.
    connect(newMission.get(), SIGNAL(missionFailed(std::shared_ptr<Common::StarSystem>)),
            this, SLOT(missionFail(std::shared_ptr<Common::StarSystem>)));
    connect(newMission.get(), SIGNAL(attemptFailed()),
            this, SLOT(missionAttemptFail()));
    connect(newMission.get(), SIGNAL(missionSuccess(std::shared_ptr<Common::StarSystem>,int)),
            this, SLOT(missionSuccess(std::shared_ptr<Common::StarSystem>,int)));
    connect(events_.get(), SIGNAL(continueGame()), newMission.get(), SLOT(reduceTurn()));

    missionsMap_[newLocation->getName()] = newMission;
    events_->missionSpawned(newLocation);
}

}

