#include "playership.hh"

#include <cassert>

const int Student::PlayerShip::MAX_ACTIONS = 3;

Student::PlayerShip::PlayerShip(std::shared_ptr<QuantumEngine> engine,
                                std::shared_ptr<Common::StarSystem> location,
                                std::string name)
    : engine_(engine), location_(location), name_(name), actionCounter_(MAX_ACTIONS), initialized_(false)
{
}

std::shared_ptr<Student::QuantumEngine> Student::PlayerShip::getEngine()
{
    return engine_;
}

std::shared_ptr<Common::StarSystem> Student::PlayerShip::getLocation()
{
    return location_;
}

std::string Student::PlayerShip::getName() const
{
    return name_;
}

void Student::PlayerShip::setName(std::string newName)
{
    name_ = newName;
}

int Student::PlayerShip::getActions()
{
    return actionCounter_;
}

void Student::PlayerShip::setLocation(std::shared_ptr<Common::StarSystem> newLocation)
{
    location_ = engine_->executeMove(newLocation);

    emit iMoved(location_, engine_->getMap()->systemsInRange(location_));

    if(initialized_)
    {
        engine_->increaseUncertainty();

        --actionCounter_;
        emit uncertaintyUpdated(engine_->getUncertainty());
        emit movesUsed();
    }


    if(actionCounter_ == 0)
        emit actionsUsed();
}

void Student::PlayerShip::doAction()
{
    --actionCounter_;
    if(actionCounter_ == 0)
    {
        emit actionsUsed();
        emit movesUsed();
    }
}

void Student::PlayerShip::setTurn()
{
    actionCounter_ = MAX_ACTIONS;
}

void Student::PlayerShip::setinitialized()
{
    initialized_ = true;
}

void Student::PlayerShip::takeDmg(unsigned amount)
{
    if(engine_->getHealth() - amount >= 0)
    {
        engine_->decreaseHealth(amount);
        emit updateHp(engine_->getHealth());
    }
    else
    {
        engine_->decreaseHealth(engine_->getHealth());
        emit engineBroke();
    }
}

void Student::PlayerShip::repair(unsigned amount)
{
    engine_->repair(static_cast<Common::ShipEngine::Health>(amount));
    emit updateHp(engine_->getHealth());
}
