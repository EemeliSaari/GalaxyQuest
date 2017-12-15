#include <algorithm>
#include <cmath>

#include "gamestate.hh"
#include "gameexception.hh"
#include "objectnotfoundexception.hh"

namespace Student
{

const unsigned GameState::NEEDED_ACTIVE = 15; //Galaxy can't survive without 15 active ships.

GameState::GameState()
    : activeShips_(0), helpShips_(0), state_(true)
{
}

GameState::~GameState()
{
}

bool GameState::getState()
{
    return state_;
}

unsigned GameState::getActive()
{
    return static_cast<unsigned>(activeShips_.size());
}

void GameState::addActive(std::shared_ptr<Common::Ship> ship)
{
    auto it = std::find(activeShips_.begin(), activeShips_.end(), ship);

    if(activeShips_.empty())
        activeShips_.push_back(ship);
    else if(it == activeShips_.end())
        activeShips_.push_back(ship);
    else
        throw Common::GameException("Ship already in active");

    calculateState();
}

void GameState::removeActive(std::shared_ptr<Common::Ship> ship)
{
    auto it = std::find(activeShips_.begin(), activeShips_.end(), ship);

    if(!(activeShips_.empty()) && it != activeShips_.end())
        activeShips_.erase(it);
    else
        throw Common::ObjectNotFoundException("Ship not found in active");

    calculateState();
}

void GameState::addHelp(std::shared_ptr<Common::Ship> ship)
{
    auto it = std::find(helpShips_.begin(), helpShips_.end(), ship);

    if(helpShips_.empty())
        helpShips_.push_back(ship);
    else if(it == helpShips_.end())
        helpShips_.push_back(ship);
    else
        throw Common::GameException("Ship already in help");

    calculateState();
}

void GameState::removeHelp(std::shared_ptr<Common::Ship> ship)
{
    auto it = std::find(helpShips_.begin(), helpShips_.end(), ship);

    if(!(helpShips_.empty()) && it != helpShips_.end())
        helpShips_.erase(it);
    else
        throw Common::ObjectNotFoundException("Ship not found in help");

    calculateState();
}

void GameState::calculateState()
{
    int activeNumber = activeShips_.size();

    if(NEEDED_ACTIVE > activeNumber)
        state_ = false;
    else
        state_ = true;
}

}
