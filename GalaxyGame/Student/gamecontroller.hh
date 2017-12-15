#ifndef GAMELOOP_HH
#define GAMELOOP_HH

#include <memory>
#include <map>
#include <string>

#include <QObject>

#include "eventhandler.hh"
#include "galaxy.hh"
#include "igamerunner.hh"
#include "igalaxy.hh"
#include "imission.hh"
#include "playership.hh"
#include "quantummap.hh"
#include "quantumengine.hh"
#include "starsystem.hh"

namespace Student
{

/*!
 * \brief Game controller that manages the NPC side of the game.
 *        Receives the information from UI.
 */
class GameController : public QObject
{
    Q_OBJECT
public:

    /*!
     * \brief Class constructor
     * \param galaxy pointer
     * \param events pointer
     * \param gameRunner pointer
     */
    GameController(std::shared_ptr<Galaxy> galaxy,
             std::shared_ptr<EventHandler> events,
             std::shared_ptr<Common::IGameRunner> gameRunner);

    /*!
     * \brief Deconstructor
     */
    ~GameController();

    /*!
     * \brief spawnShips
     * \param value
     */
    void spawnShips(unsigned value);

    /*!
     * \brief getStarMap
     * \return
     */
    std::shared_ptr<Common::StarSystem::StarSystemVector> getStarSystems();

    /*!
     * \brief getMap
     * \return
     */
    std::map<std::string, std::vector<std::string> > getMap();

    /*!
     * \brief initialize
     */
    void initialize();

    /*!
     * \brief Sets playership name.
     * \param name
     */
    void setPlayerName(std::string name);

public slots:

    /*!
     * \brief turnEnded
     */
    void turnEnded();

    /*!
     * \brief Slot to inform about saving ship.
     * \param target ship that is saved.
     */
    void completeSaveShip(std::shared_ptr<Common::Ship> target);

    /*!
     * \brief Slot to inform about player movement.
     * \param new location name, default Sol
     */
    void movePlayer(std::string newLocation = "Sol");

    /*!
     * \brief Slot to inform about attempt to completed mission
     * \param location name
     */
    void completeMission(std::string locationName);

    /*!
     * \brief Slot to inform if mission was success.
     * \param location name
     */
    void missionSuccess(std::shared_ptr<Common::StarSystem> location, int reward);

    /*!
     * \brief Slot to inform about if mission completion attempt was failure.
     * \param location pointer
     * \param reward amount of credits rewarded.
     */
    void missionAttemptFail();

    /*!
     * \brief Slot to inform about failed mission.
     * \param location pointer
     */
    void missionFail(std::shared_ptr<Common::StarSystem> location);

    /*!
     * \brief Slot to inform about ship that player wants to salvage.
     * \param ship pointer
     */
    void salvageShip(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief Open repair dialog.
     * \param location name.
     */
    void openRepair(std::string location);

    /*!
     * \brief Repair the player the given amount.
     * \param amount to be repaired.
     * \param price for each hitpoint.
     */
    void repair(int amount, int price);

    /*!
     * \brief Open the buy dialog.
     * \param location name.
     */
    void openBuy(std::string location);

    /*!
     * \brief buy amount of ships.
     * \param amount of ships to be purchased.
     */
    void buy(int amount, int price);

    /*!
     * \brief Slot to collect information about location
     * \param location name
     */
    void collectInfo(std::string location);

private:

    /*!
     * \brief counts how many turns have been played.
     */
    unsigned turnCounter_;

    /*!
     * \brief Does all the actions in turn. Emit turnPlayed when done.
     */
    void playTurn();

    /*!
     * \brief Spawns a mission to random location
     */
    void spawnMission();

    /*!
     * \brief initialized_
     */
    bool initialized_;

    /*!
     * \brief pointer to Galaxy
     */
    std::shared_ptr<Galaxy> galaxy_;

    /*!
     * \brief pointer to EventHandler
     */
    std::shared_ptr<EventHandler> events_;

    /*!
     * \brief pointer to PlayerShip
     */
    std::shared_ptr<PlayerShip> playerShip_;

    /*!
     * \brief Course's GamRunner to handle NPC ships
     */
    std::shared_ptr<Common::IGameRunner> gameRunner_;

    /*!
     * \brief map of all the missions [location, mission pointer]
     */
    std::map<std::string, std::shared_ptr<IMission>> missionsMap_;

    /*!
     * \brief Standard mission turn time.
     */
    unsigned standardTime_;

    /*!
     * \brief Standard mission range.
     */
    double standardRange_;
};

}
#endif // GAMELOOP_HH
