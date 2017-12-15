#include <algorithm>

#include "quantummap.hh"

using namespace Student;
using namespace Common;

QuantumMap::QuantumMap(std::shared_ptr<Galaxy> galaxy)
    : galaxy_(galaxy)
{
    initializeConnections();
    allSystems_ = std::vector<std::shared_ptr<StarSystem> >(0);
}

std::vector<std::shared_ptr<StarSystem> > QuantumMap::systemsInRange(std::shared_ptr<StarSystem> system)
{
    auto systems = network_[system];
    return systems;
}

bool QuantumMap::validJump(std::shared_ptr<StarSystem> from,
                           std::shared_ptr<StarSystem> to)
{
    auto target = network_[from];

    auto it = std::find(target.begin(), target.end(), to);

    if(it == target.end())
        return false;
    else
        return true;
}

std::shared_ptr<StarSystem> QuantumMap::getRandom(std::shared_ptr<StarSystem> current)
{
    return galaxy_->getRandomSystemOutsideRange(current, 8);
}

std::map<std::string, std::vector<std::string> > QuantumMap::getStrings()
{
    std::map<std::string, std::vector<std::string> > stringNetwork;

    for(auto itMap = network_.begin(); itMap != network_.end(); ++itMap)
    {
        std::vector<std::string> systemNames(0);

        auto systemVector = (*itMap).second;

        for(auto it = systemVector.begin(); it != systemVector.end(); ++it)
        {
            systemNames.push_back((*it)->getName());
        }

        stringNetwork[(*itMap).first->getName()] = systemNames;
    }
    return stringNetwork;
}

void QuantumMap::initializeConnections()
{
    auto systems = galaxy_->getStarSystems();

    // Copy the starsystems vector.
    for(auto it = systems->begin(); it != systems->end(); ++it)
    {
        allSystems_.push_back((*it));
    }

    cheat();

    auto point = findNext();

    while(!(allSystems_.empty()))
    {
        auto nn = nearestNeighbours(point);

        if(network_.find(point) == network_.end())
        {
            network_[point] = nn;
        }
        else
        {
            for(auto it = nn.begin(); it != nn.end(); ++it)
            {
                if(network_[point].size() < 4)
                    network_[point].push_back((*it));
                else
                    break;
            }
        }

        connectBack(point);

        auto it = std::find(allSystems_.begin(), allSystems_.end(), point);
        allSystems_.erase(it);

        if(!(allSystems_.empty()))
        {
            point = findNext();
        }

    }
}

void QuantumMap::cheat()
{
    std::vector<std::shared_ptr<StarSystem>>vector1(0);
    std::vector<std::shared_ptr<StarSystem>>vector2(0);
    std::vector<std::shared_ptr<StarSystem>>vector3(0);

    auto system1 = galaxy_->getStarSystemByName("Ross 248");
    auto system2 = galaxy_->getStarSystemByName("EZ Aquarii");
    vector1.push_back(system2);
    vector3.push_back(system1);
    network_[system1] = vector1;
    network_[system2] = vector3;

    auto system3 = galaxy_->getStarSystemByName("LHS 2");
    auto system4 = galaxy_->getStarSystemByName("BR Piscium");
    vector2.push_back(system4);
    network_[system3] = vector2;
    connectBack(system3);
}

std::vector<std::shared_ptr<StarSystem> > QuantumMap::nearestNeighbours(std::shared_ptr<StarSystem> system)
{
    std::vector<std::shared_ptr<StarSystem> > neighbours(0);

    int r = randomMinMax(2, 3);
    unsigned range = 1;

    while(neighbours.size() < r)
    {
        auto inRange = galaxy_->getSystemsInRange(system, range);

        if(!(inRange.empty()))
        {
            for(auto it = inRange.begin(); it != inRange.end(); ++it)
            {
                auto check = std::find(neighbours.begin(), neighbours.end(), (*it));

                if(check == neighbours.end() && neighbours.size() < r && validNeighbour(system, (*it)))
                {
                   neighbours.push_back((*it));
                }
            }
        }
        ++range;
        if(range > 12)
            break;
    }
    return neighbours;
}

bool QuantumMap::validNeighbour(std::shared_ptr<StarSystem> system, std::shared_ptr<StarSystem> targetSys)
{
    if (network_.empty())
        return true;
    else if(network_.find(targetSys) == network_.end())
        return true;
    else
    {
        auto target = network_[targetSys];

        auto it = std::find(target.begin(), target.end(), system);

        if(target.size() < 3)
            return true;

        else if(it == target.end())
            return true;

        else
            return false;
    }
}

void QuantumMap::connectBack(std::shared_ptr<StarSystem> system)
{

    auto vec = network_[system];

    for(auto it = vec.begin(); it != vec.end(); ++it)
    {
        if(network_.find((*it)) == network_.end())
        {
            std::vector<std::shared_ptr<StarSystem> > newNeighbour(0);
            newNeighbour.push_back(system);
            network_[(*it)] = newNeighbour;
        }
        else
        {
            network_[(*it)].push_back(system);
        }
    }

}

std::shared_ptr<StarSystem> QuantumMap::findNext()
{
    std::shared_ptr<StarSystem> next;

    for(int x = -25; x < 25; ++x)
    {
        bool loop = true;
        for(int y = -25; y < 25; ++y)
        {
            auto start = allSystems_.begin();
            auto end = allSystems_.end();

            auto it = std::find_if(start, end,
                                   [x, y](std::shared_ptr<Common::StarSystem> target)
                                   {return target->getCoordinates().x == x && target->getCoordinates().y == y;});
            if(it != end)
            {
                next = *it;
                loop = false;
                break;
            }
        }
        if(!loop)
        {
            break;
        }
    }
    return next;
}
