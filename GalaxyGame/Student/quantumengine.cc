#include "quantumengine.hh"
#include "utility"

using namespace Student;

const int QuantumEngine::MAX_HEALTH = 150;
const int QuantumEngine::MAX_UNCERTAINTY = 100;

QuantumEngine::QuantumEngine(std::shared_ptr<QuantumMap> map)
    : Common::ShipEngine(MAX_HEALTH), map_(map)
{
    uncertaintyFactor_ = 0;
}

bool QuantumEngine::canStart() const
{
    return Common::ShipEngine::canStart();
}

std::shared_ptr<Common::StarSystem> QuantumEngine::executeMove(std::shared_ptr<Common::StarSystem> destination)
{
    if(uncertaintyFactor_ > 0)
    {
        auto rng = Common::randomMinMax(1,uncertaintyFactor_);
        double factor = static_cast<double>(rng) / static_cast<double>(MAX_UNCERTAINTY);

        if(factor > 0.65)
        {
            resetUncertainty();
            return map_->getRandom(destination);
        }
        else
        {
            return destination;
        }
    }
    else
    {
        return destination;
    }

}

void QuantumEngine::onStart()
{
    increaseUncertainty();
}

Common::StarSystem::StarSystemVector QuantumEngine::getValidDestinations(std::shared_ptr<Common::StarSystem> source) const
{
    auto inRange = map_->systemsInRange(source);

    auto systems = Common::StarSystem::StarSystemVector();

    for(auto it = inRange.begin(); it != inRange.end(); ++it)
    {
        systems.push_back((*it));
    }
    return systems;
}

bool QuantumEngine::isValidTrip(std::shared_ptr<Common::StarSystem> source,
                                std::shared_ptr<Common::StarSystem> destination) const
{
    return map_->validJump(source, destination);
}

int QuantumEngine::requiredTurns(std::shared_ptr<Common::StarSystem> source,
                                 std::shared_ptr<Common::StarSystem> destination) const
{
    return 1;
}

void QuantumEngine::increaseUncertainty()
{
    uncertaintyFactor_ += Common::randomMinMax(1,10);
}

void QuantumEngine::resetUncertainty()
{
    uncertaintyFactor_ = 0;
}

int QuantumEngine::getUncertainty()
{
    return uncertaintyFactor_;
}

std::map<std::string, std::vector<std::string>> QuantumEngine::getStringMap()
{
    return map_->getStrings();
}

std::shared_ptr<QuantumMap> QuantumEngine::getMap()
{
    return map_;
}

