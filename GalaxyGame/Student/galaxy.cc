#include "utility.hh"
#include "galaxy.hh"
#include "objectnotfoundexception.hh"
#include "stateexception.hh"

namespace {

    /*!
     * \brief Helper function to check if two systems are the same.
     * \param target StarSystem pointer
     * \param search StartSystem pointer
     * \return true if name or id or coordinates are the same, false otherwise
     */
    static bool isEqualSystem(std::shared_ptr<Common::StarSystem> target, std::shared_ptr<Common::StarSystem> search)
    {
        if(target->getName() == search->getName() || target->getId() == search->getId() || target->getCoordinates() == search->getCoordinates())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

namespace Student {

Galaxy::Galaxy()
{
    ships_ = std::make_shared<Common::IGalaxy::ShipVector>();
    starSystems_ = std::make_shared<Common::StarSystem::StarSystemVector>();
}

Galaxy::~Galaxy()
{
}

void Galaxy::addShip(std::shared_ptr<Common::Ship> ship)
{
    auto it = std::find(ships_->begin(), ships_->end(), ship);

    if (it != ships_->end())
    {
        throw Common::StateException();
    }
    else
    {
        ships_->push_back(ship);
    }
}

void Galaxy::removeShip(std::shared_ptr<Common::Ship> ship)
{
    auto it = std::find(ships_->begin(), ships_->end(), ship);

    if (it != ships_->end())
    {
        it = ships_->erase(it);
    }
    else
    {
        throw Common::ObjectNotFoundException();
    }
}

void Galaxy::addStarSystem(std::shared_ptr<Common::StarSystem> starSystem)
{
    auto it = std::find_if(starSystems_.get()->begin(), starSystems_.get()->end(), [starSystem](std::shared_ptr<Common::StarSystem> target){return isEqualSystem(target, starSystem);});
    if (it == starSystems_.get()->end() || starSystems_.get()->empty())
    {
        starSystems_->push_back(starSystem);
    }
    else
    {
        throw Common::StateException(starSystem->getName());
    }
}

std::shared_ptr<Common::IGalaxy::ShipVector> Galaxy::getShips()
{
    return ships_;
}

std::shared_ptr<Common::StarSystem::StarSystemVector> Galaxy::getStarSystems()
{
    return starSystems_;
}

Common::StarSystem::StarSystemVector Galaxy::getSystemsInRange
        (std::shared_ptr<Common::StarSystem> system, int range)
{
    std::vector<std::shared_ptr<Common::StarSystem>> systemsInRange;
    auto i = std::find_if(starSystems_.get()->begin(), starSystems_.get()->end(), [system](std::shared_ptr<Common::StarSystem> target){return isEqualSystem(target, system);});
    if (i != starSystems_.get()->end())
    {
        for (auto it = starSystems_.get()->begin(); it != starSystems_.get()->end(); ++it)
        {
            if (system.get()->getCoordinates().distanceTo((*it)->getCoordinates()) < range && !isEqualSystem(*it, system))
            {
                systemsInRange.insert(systemsInRange.begin(),*it);
            }
        }
    }
    else
    {
        throw(Common::ObjectNotFoundException());
    }
    return systemsInRange;
}

std::shared_ptr<Common::StarSystem> Galaxy::getRandomSystemOutsideRange(
        std::shared_ptr<Common::StarSystem> currentSystem, int range)
{
    if (!starSystems_->empty())
    {
        auto systemsInRange = getSystemsInRange(currentSystem,range);
        std::vector<std::shared_ptr<Common::StarSystem>> systemsOutOfRange;

        for(auto starit = starSystems_.get()->begin(); starit != starSystems_.get()->end(); ++starit)
        {
            auto it = std::find_if(starSystems_.get()->begin(), starSystems_.get()->end(), [starit](std::shared_ptr<Common::StarSystem> target){return isEqualSystem(target, (*starit));});
            if(it != systemsInRange.end())
            {
                systemsOutOfRange.push_back(*starit);
            }
        }

        auto randomIndex = Common::randomMinMax(0, systemsOutOfRange.size() - 1);
        return systemsOutOfRange.at(randomIndex);
    }
    else
    {
        throw Common::ObjectNotFoundException();
    }
}


std::shared_ptr<Common::StarSystem> Galaxy::getRandomSystem()
{
    if (!starSystems_->empty())
    {
        auto randomIndex = Common::randomMinMax(0, starSystems_->size() - 1);
        return starSystems_->at(randomIndex);
    }
    else
    {
        throw Common::ObjectNotFoundException();
    }
}

Common::IGalaxy::ShipVector Galaxy::getShipsInStarSystem(std::string name)
{
    std::vector<std::shared_ptr<Common::Ship>> shipsInSystem;
    for(auto it = ships_.get()->begin(); it != ships_.get()->end(); ++it)
    {
        if((*it)->getLocation() != nullptr)
            if ((*it)->getLocation()->getName() == name)
            {
                shipsInSystem.push_back(*it);
            }
    }
    return shipsInSystem;
}

std::vector<std::string> Galaxy::getSystemNames()
{
    std::vector<std::string> systemNames;
    for (auto it = starSystems_->begin(); it != starSystems_->end(); ++it)
    {
        systemNames.push_back((*it)->getName());
    }
    return systemNames;
}

std::vector<unsigned> Galaxy::getSystemIds()
{
    std::vector<unsigned> systemIds;
    for (auto it = starSystems_->begin(); it != starSystems_->end(); ++it)
    {
        systemIds.push_back((*it)->getId());
    }
    return systemIds;
}

std::shared_ptr<Common::StarSystem> Galaxy::getStarSystemByName(std::string name)
{
    auto it = std::find_if(starSystems_.get()->begin(), starSystems_.get()->end(), [name](std::shared_ptr<Common::StarSystem> target){return name == target->getName();});

    if (it != starSystems_.get()->end() && !starSystems_.get()->empty())
    {
        return *it;
    }
    else
    {
        throw Common::ObjectNotFoundException();
    }
}


std::shared_ptr<Common::StarSystem> Galaxy::getStarSystemById(unsigned id)
{
    auto it = std::find_if(starSystems_.get()->begin(),starSystems_.get()->end(),[id](std::shared_ptr<Common::StarSystem> target){return id == target->getId();});

    if (it != starSystems_.get()->end() && !starSystems_.get()->empty())
    {
        return *it;
    }
    else
    {
        throw(Common::ObjectNotFoundException());
    }
}

}//Student
