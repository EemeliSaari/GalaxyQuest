#include <eventhandler.hh>
#include <iostream>

#include "ship.hh"

namespace Student {

EventHandler::EventHandler(std::shared_ptr<Statistics> stats, QObject *parent)
    : stats_(stats)
{
    state_ = std::make_shared<GameState>();
}

EventHandler::~EventHandler()
{
}

void EventHandler::shipSpawned(std::shared_ptr<Common::Ship> ship)
{
    state_->addActive(ship);
    emit spawnedShip(ship);
}

void EventHandler::shipRemoved(std::shared_ptr<Common::Ship> ship)
{
    try
    {
        stats_->addCredits(150);
    }
    catch(...)
    {
        emit gameOver(stats_->getPoints());
    }
}

void EventHandler::shipRelocated(std::shared_ptr<Common::Ship> ship,
                   std::shared_ptr<Common::StarSystem> starSystem)
{
    if(ship->getLocation() == nullptr)
        emit shipIsLeaving(ship, starSystem);
    else
    {
        emit shipIsEntering(ship);
    }
}

void EventHandler::shipMoved(std::shared_ptr<Common::Ship> ship,
                             Common::Point origin,
                             Common::Point target)
{
    emit moveShip(ship, origin, target);
}

void EventHandler::exceptionInExecution(std::shared_ptr<Common::Ship> ship,
                                        std::string const& msg)
{
    std::cout << msg << std::endl;
}

void EventHandler::distressOn(std::shared_ptr<Common::Ship> ship)
{
    state_->addHelp(ship);
    state_->removeActive(ship);

    emit shipNeedsSaving(ship);
}

void EventHandler::distressOff(std::shared_ptr<Common::Ship> ship)
{
    state_->addActive(ship);
    state_->removeHelp(ship);
    try
    {
        stats_->addSavedShip();
        stats_->addPoints(50);
    }
    catch(...)
    {
        emit gameOver(stats_->getPoints());
    }
}

void EventHandler::shipAbandoned(std::shared_ptr<Common::Ship> ship)
{
    stats_->addLostShip();
    state_->removeHelp(ship);

    emit shipSaveFailedAt(ship);
    emit salvageShip(ship);
}

void EventHandler::rescueCompleted(std::shared_ptr<Common::StarSystem> location, int reward)
{
    try
    {
        stats_->addCredits(reward);
        stats_->addPoints(10);
        emit deleteMission(location->getName());
    }
    catch(...)
    {
        emit gameOver(stats_->getPoints());
    }

}

void EventHandler::rescueFailed(std::shared_ptr<Common::StarSystem> location)
{
    emit deleteMission(location->getName());
}

void EventHandler::removeCredits(unsigned amount)
{
    try
    {
        stats_->reduceCredits(amount);
    }
    catch(...)
    {
        emit gameOver(0);
    }
}

int EventHandler::getCredits()
{
    return stats_->getCreditBalance();
}

void EventHandler::receiveInfo(std::shared_ptr<Common::StarSystem> system,
                                std::vector<std::shared_ptr<Common::Ship> > ships)
{
    emit sendInfo(system, ships);
}

void EventHandler::addScore(unsigned amount)
{
    try
    {
        stats_->addPoints(amount);
    }
    catch(std::overflow_error)
    {
        emit gameOver(stats_->getPoints());
    }
}

void EventHandler::unPause()
{
    emit unPauseGame();
}

void EventHandler::playerHp(int newValue)
{
    emit updateDmg(newValue);
}

void EventHandler::playerUncertainty(int newValue)
{
    emit updateUncertainty(newValue);
}

void EventHandler::actionsUsed()
{
    emit playerTurnsUsed();
}

void EventHandler::movesUsed()
{
    emit playerMovesUsed();
}

void EventHandler::turnPlayed()
{
    emit getActive(state_->getActive());

    if(state_->getState())
    {
        emit continueGame();
    }
    else
    {
        unsigned points;
        try
        {
            points = stats_->getPoints();
        }
        catch(...)
        {
            points = 0;
        }

        emit gameOver(points);
    }
}

void EventHandler::playerMoved(std::shared_ptr<Common::StarSystem> system, std::vector<std::shared_ptr<Common::StarSystem> > systemsInRange)
{
    auto systemString = system->getName();

    std::vector<std::string> inRange(0);

    for(auto it = systemsInRange.begin(); it != systemsInRange.end(); ++it)
    {
        inRange.push_back((*it)->getName());
    }

    emit newPlayerLoc(systemString, inRange);
}

void EventHandler::playerBroke()
{
    emit gameOver(stats_->getPoints());
}

void EventHandler::missionSpawned(std::shared_ptr<Common::StarSystem> location)
{
    emit spawnMission(location->getName());
}

}
