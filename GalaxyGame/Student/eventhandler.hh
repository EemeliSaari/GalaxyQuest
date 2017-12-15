#ifndef EVENTHANDLER_HH
#define EVENTHANDLER_HH

#include <QObject>

#include "gamestate.hh"
#include "ieventhandler.hh"
#include "point.hh"
#include "statistics.hh"

namespace Student
{

/*!
 * \brief EventHandler class to receive information from course and
 *        forward the information to UI components.
 */
class EventHandler: public QObject, public Common::IEventHandler
{
    Q_OBJECT
public:

    /*!
     * \brief Constructor
     * \param stats, pointer to Statistics class.
     * \param QObject parent, default = nullptr
     */
    EventHandler(std::shared_ptr<Statistics> stats,
                 QObject *parent = nullptr);

    /*!
     * \brief Deconstructor
     */
    ~EventHandler();

    /*!
     * \brief Take the information about the spawned ship.
     *        Emits the spawnedShip and update GameState.
     * \param ship pointer.
     */
    void shipSpawned(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief Take the information about the removed ship.
     *        Updates the score.
     * \param ship pointer
     */
    void shipRemoved(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief Takes the information if ship left or entered system.
     *        Emits the correct signal according to the case.
     * \param ship pointer
     * \param starSystem pointer
     */
    void shipRelocated(std::shared_ptr<Common::Ship> ship,
                       std::shared_ptr<Common::StarSystem> starSystem);

    /*!
     * \brief Takes information about moved ship. Emits signal
     *        and information forward.
     * \param ship pointer
     * \param origin where ship left
     * \param target where ship is going
     */
    void shipMoved(std::shared_ptr<Common::Ship> ship,
                   Common::Point origin,
                   Common::Point target);

    /*!
     * \brief If any exceptions occur this function is called.
     * \param ship pointer that caused exception.
     * \param msg message
     */
    void exceptionInExecution(std::shared_ptr<Common::Ship> ship,
                              std::string const& msg);

    /*!
     * \brief Ship calls this if it's in trouble
     *        Update the GameState and emit shipNeedsSaving signal.
     * \param ship pointer
     */
    void distressOn(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief Ship informs this if it's no longer in trouble.
     *        Update the GameState and Statistics.
     * \param ship pointer
     */
    void distressOff(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief Ship informs this if it's abandoned.
     *        Update GameState and Statistics. Emit
     *        shipSaveFailedAt and salvageShip.
     * \param ship pointer
     */
    void shipAbandoned(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief When turn is played this is called. Emit the
     *        continueGame signal if GameState passes otherwise
     *        emits gameOver.
     */
    void turnPlayed();

    /*!
     * \brief Inform location of the new mission. Emit spawnMission
     * \param location
     */
    void missionSpawned(std::shared_ptr<Common::StarSystem> location);

    /*!
     * \brief Inform this if mission was completed.
     * \param location of the completed mission.
     * \param reward to be added to player wallet.
     */
    void rescueCompleted(std::shared_ptr<Common::StarSystem> location, int reward);

    /*!
     * \brief inform this if mission was failed.
     * \param laction of the failed mission.
     */
    void rescueFailed(std::shared_ptr<Common::StarSystem> location);

    /*!
     * \brief Remove credits from player. Emit gameOver if exception is caught.
     * \param unsigned amount.
     */
    void removeCredits(unsigned amount);

    /*!
     * \brief Get the current credit balance.
     * \return credits balance int.
     */
    int getCredits();

    /*!
     * \brief Pass the starsystem info towards UI.
     * \param system pointer
     * \param ships pointer
     */
    void receiveInfo(std::shared_ptr<Common::StarSystem> system,
                      std::vector<std::shared_ptr<Common::Ship>> ships);
    /*!
     * \brief Add score to the player Statistics
     * \param amount to be added
     */
    void addScore(unsigned amount);

public slots:

    /*!
     * \brief This slot receives information about unpausing of the game.
     */
    void unPause();

    /*!
     * \brief This slot receives information about changed player hp.
     * \param new Hp value.
     */
    void playerHp(int newValue);

    /*!
     * \brief This slot receives information about changed uncertainty.
     * \param new uncertainty value.
     */
    void playerUncertainty(int newValue);

    /*!
     * \brief This slot receives information about player movement.
     * \param new system
     * \param new systems in range
     */
    void playerMoved(std::shared_ptr<Common::StarSystem> system,
                     std::vector<std::shared_ptr<Common::StarSystem> > systemsInRange);
    /*!
     * \brief playerBroke
     */
    void playerBroke();

    /*!
     * \brief This slot receives information about used actions.
     */
    void actionsUsed();

    /*!
     * \brief This slot receives information about used move actions.
     */
    void movesUsed();

signals:

    /*!
     * \brief this signal send information about unpausing the game
     */
    void unPauseGame();

    /*!
     * \brief this signal send information about updated dmg/hp
     * \param new hp value.
     */
    void updateDmg(int newValue);

    /*!
     * \brief this signal send information about uncertainty
     * \param new uncertainty value
     */
    void updateUncertainty(int newValue);

    /*!
     * \brief this signal send information about used turn.
     */
    void playerTurnsUsed();

    /*!
     * \brief this signal send information about used moves.
     */
    void playerMovesUsed();

    /*!
     * \brief this signal send information about ship in need of saving.
     * \param ship pointer
     */
    void shipNeedsSaving(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief this signal send information about failed ship save.
     * \param ship pointer
     */
    void shipSaveFailedAt(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief this signal send information about spawned ship.
     * \param ship pointer
     */
    void spawnedShip(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief this signal send information about new mission location.
     * \param location name
     */
    void spawnMission(std::string location);

    /*!
     * \brief this signal send information about new salvageable ship.
     * \param ship pointer
     */
    void salvageShip(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief this signal send information about mission that needs to be deleted
     * \param location
     */
    void deleteMission(std::string location);

    /*!
     * \brief this signal send information about lost game.
     */
    void gameOver(unsigned finalScore);

    /*!
     * \brief this signal send information about continueable game.
     */
    void continueGame();

    /*!
     * \brief this signal send information about ship movement.
     * \param ship pointer
     * \param origin location (from)
     * \param target location (to)
     */
    void moveShip(std::shared_ptr<Common::Ship> ship,
                  Common::Point origin,
                  Common::Point target);

    /*!
     * \brief this signal send information about ship leaving from system.
     * \param ship pointer
     * \param starSystem that ship is leaving from.
     */
    void shipIsLeaving(std::shared_ptr<Common::Ship> ship,
                       std::shared_ptr<Common::StarSystem> starSystem);

    /*!
     * \brief this signal send information about ship entering to system orbit.
     * \param ship pointer.
     */
    void shipIsEntering(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief this signal sends information about players new location and systems in range
     * \param system
     * \param systemsInRange
     */
    void newPlayerLoc(std::string system, std::vector<std::string> systemsInRange);

    /*!
     * \brief this signal send information about selected system toward UI.
     * \param system that was clicked.
     * \param ships in system.
     */
    void sendInfo(std::shared_ptr<Common::StarSystem> system,
                  std::vector<std::shared_ptr<Common::Ship>> ships);

    /*!
     * \brief this signal sends information about current active ships count
     * \param amount of active ships
     */
    void getActive(unsigned amount);

private:

    /*!
     * \brief Pointer to Statistics that EventHandler will update.
     */
    std::shared_ptr<Statistics> stats_;

    /*!
     * \brief Pointer to GameState that keeps track of game state.
     */
    std::shared_ptr<GameState> state_;
};

} //Student

#endif // EVENTHANDLER_HH
