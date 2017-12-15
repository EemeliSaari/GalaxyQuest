#ifndef GAMESTATE_HH
#define GAMESTATE_HH

#include <memory>
#include <vector>

#include "ship.hh"

namespace Student
{

/*!
 * \brief The GameState class keeping track of economic
 *        stability of the galaxy.
 * \invariant activeShips.size >= NEEDED_ACTIVE
 */
class GameState
{
public:

    /*!
     * \brief number of needed NPC ships at any given turn.
     */
    static const unsigned NEEDED_ACTIVE;

    /*!
     * \brief constructor
     * \post activeShips = 0 && helpShips = 0, state = true
     */
    GameState();

    /*!
     * \brief deconstructor
     */
    ~GameState();

    /*!
     * \brief Get the current state of the game.
     * \return bool false wheter or not game is lost
     */
    bool getState();

    /*!
     * \brief Get amount of ships that are active
     * \return amount of ships that are active
     */
    unsigned getActive();

    /*!
     * \brief Add ship to activeShips vector
     * \param pointer to ship
     * \post active ship is added to activeShips_
     * \throw GameException if ship already in vector
     */
    void addActive(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief Remove ship from activeShips vector
     * \param pointer to ship
     * \post ship is removed from the activeShips_
     * \throw ObjectNotFoundException if object not found in vector
     */
    void removeActive(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief Add ship in need of help to helpShips vector.
     * \param pointer to ship
     * \post ship in need of help is added to helpShips_ vector
     * \throw GameException if ship already in vector
     */
    void addHelp(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief Remove ship in need from helpShips vector.
     * \param pointer to ship
     * \post ship is removed from the helpShip_ vector
     * \throw ObjectNotFoundException if object not found in vector
     */
    void removeHelp(std::shared_ptr<Common::Ship> ship);

private:

    /*!
     * \brief Checks the class invariance and sets the state
     * \post game state is set accordingly.
     */
    void calculateState();

    /*!
     * \brief vector storeing active ships.
     */
    std::vector<std::shared_ptr<Common::Ship> > activeShips_;

    /*!
     * \brief vector storeing ships need of help.
     */
    std::vector<std::shared_ptr<Common::Ship> > helpShips_;

    /*!
     * \brief state of the game.
     */
    bool state_;
};

} //Student

#endif // GAMESTATE_HH
