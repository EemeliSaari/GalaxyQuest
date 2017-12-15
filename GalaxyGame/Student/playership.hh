#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include <QObject>
#include <memory>

#include "quantumengine.hh"
#include "ship.hh"
#include "starsystem.hh"

namespace Student
{

/*!
 * \brief The PlayerShip class
 */
class PlayerShip : public QObject
{
    Q_OBJECT
public:

    /*!
     * \brief Mac actions per turn
     */
    static const int MAX_ACTIONS;

    /*!
     * \brief Constructor
     * \param engine pointer
     * \param initial location pointer
     * \param name
     */
    PlayerShip(std::shared_ptr<QuantumEngine> engine,
               std::shared_ptr<Common::StarSystem> location,
               std::string name);

    /*!
     * \brief deconstructor
     */
    ~PlayerShip() = default;

    /*!
     * \brief get the ship engine
     * \return pointer to ship engine
     */
    std::shared_ptr<QuantumEngine> getEngine();

    /*!
     * \brief get current location
     * \return starsystem pointer
     */
    std::shared_ptr<Common::StarSystem> getLocation();

    /*!
     * \brief get playername
     * \return player name
     */
    std::string getName() const;

    /*!
     * \brief sets the player name
     * \param new name
     */
    void setName(std::string newName);

    /*!
     * \brief get current actions of player.
     * \return actions counter
     */
    int getActions();

    /*!
     * \brief Set player to new location.
     * \param new location
     */
    void setLocation(std::shared_ptr<Common::StarSystem> newLocation);

    /*!
     * \brief substract player actions counter
     */
    void doAction();

    /*!
     * \brief reset actions and movement.
     */
    void setTurn();

    /*!
     * \brief set playership ready to be used.
     */
    void setinitialized();

    /*!
     * \brief Take engine damage.
     * \param amount of dmg taken.
     */
    void takeDmg(unsigned amount);

    /*!
     * \brief Repair engine.
     * \param amount to be repaired.
     */
    void repair(unsigned amount);

signals:

    /*!
     * \brief Send signal if actions are used.
     */
    void actionsUsed();

    /*!
     * \brief Send signal if moves are used.
     */
    void movesUsed();

    /*!
     * \brief Send signal about new player location.
     * \param new system
     * \param new systems in range.
     */
    void iMoved(std::shared_ptr<Common::StarSystem> newSystem,
                std::vector<std::shared_ptr<Common::StarSystem>> inRange);

    /*!
     * \brief Sends signal about updated engine hitpoints.
     * \param new value
     */
    void updateHp(int newValue);

    /*!
     * \brief Sends signal about updated uncertainty.
     * \param new value.
     */
    void uncertaintyUpdated(int newValue);

    /*!
     * \brief engineBroke
     */
    void engineBroke();

private:

    /*!
     * \brief Pointer to engine
     */
    std::shared_ptr<QuantumEngine> engine_;

    /*!
     * \brief Pointer to current location
     */
    std::shared_ptr<Common::StarSystem> location_;

    /*!
     * \brief Player name
     */
    std::string name_;

    /*!
     * \brief Actions counter.
     */
    int actionCounter_;

    /*!
     * \brief Status if initialized.
     */
    bool initialized_;
};    

}//Student

#endif // PLAYERSHIP_H
