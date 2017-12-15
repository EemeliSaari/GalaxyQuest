#ifndef GALAXYMAP_HH
#define GALAXYMAP_HH

#include <memory>
#include <map>
#include <string>

#include <QFrame>
#include <QGraphicsScene>

#include "galaxy.hh"
#include "galaxyview.hh"
#include "shipitem.hh"
#include "solarsystemitem.hh"
#include "starsystem.hh"


namespace StudentUI
{

/*!
 * \brief GalaxyFrame class to display the QGraphicsScene and manage
 *        the information flow between QGraphicsItems in the scene and
 *        the game logic.
 */
class GalaxyFrame : public QFrame
{
    Q_OBJECT
public:

    /*!
     * \brief Class constructor
     * \param parent widget
     * \param starSystems vector pointer
     */
    GalaxyFrame(QWidget *parent);
    /*!
     * \brief deconstructor
     */
    ~GalaxyFrame();

    /*!
     * \brief creates the view, scene and places the objects.
     */
    void initialize(std::shared_ptr<Common::StarSystem::StarSystemVector> starSystems,
                    std::map<std::string, std::vector<std::string> > connections);

    /*!
     * \brief set initialized status on, Frame is ready to be used.
     */
    void setInitialized();

    /*!
     * \brief Move the Scene Rect to player location.
     * \post Player location == Scene rect center.
     */
    void focusOnPlayer();

    /*!
     * \brief Enables actions and movements in player location.
     */
    void newTurn();

    /*!
     * \brief Deletes the scene and objects in it.
     */
    void resetScene();

public slots:

    /*!
     * \brief Player initialized repair action.
     * \param location name.
     */
    void playerInitRepair(std::string location);

    /*!
     * \brief player initialized buy action.
     * \param location name.
     */
    void playerInitBuy(std::string location);

    /*!
     * \brief Inform the correct GraphicsItems where player moved.
     * \param newLoc new player location.
     * \param inRange systems in player range.
     */
    void playerMoved(std::string newLoc, std::vector<std::string> inRange);

    /*!
     * \brief Selected GraphicsItem
     * \param name of the system.
     */
    void systemSelected(std::string name);

    /*!
     * \brief Ship that is not in any system is drawn here.
     * \param ship pointer
     * \param origin point (x,y)
     * \param target point (x,y)
     */
    void shipMoving(std::shared_ptr<Common::Ship> ship,
                    Common::Point origin,
                    Common::Point target);

    /*!
     * \brief Add ship to system.
     * \param ship pointer.
     */
    void addShips(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief Ship leaving from system.
     * \param ship pointer
     * \param starSystem pointer
     */
    void shipLeaving(std::shared_ptr<Common::Ship> ship,
                     std::shared_ptr<Common::StarSystem> starSystem);

    /*!
     * \brief Add new ship mission indicator to GraphicsItem.
     * \param ship in need of saving.
     */
    void shipMission(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief Remove ship mission indicator from GraphicsItem.
     * \param ship that needed saving.
     */
    void shipMissionFail(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief Catch signal if player saved a ship from GraphicsItem.
     *        Sends a signal shipSaved(ship)
     * \param ship that was saved.
     */
    void shipMissionSuccess(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief Player salvaged ship.
     * \param ship pointer.
     */
    void completeSalvage(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief Ship is marked as salvageable
     * \param ship pointer.
     */
    void salvageMission(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief Disables items from taking any player actions.
     */
    void playerActionsUp();

    /*!
     * \brief Disables items from allowing player to move.
     */
    void playerMovesUp();

    /*!
     * \brief Player initializing move operation.
     * \param from location name.
     */
    void playerInitMove(std::string from);

    /*!
     * \brief Sets new mission system to display in the scene.
     * \param location name.
     */
    void newMission(std::string to);

    /*!
     * \brief Player completing mission
     * \param from location name
     */
    void completingMission(std::string from);

    /*!
     * \brief Sets mission system to not display mission.
     * \param from location name
     */
    void missionExpired(std::string from);

signals:

    /*!
     * \brief Signal to update starsystem
     * \param system name
     */
    void updateThis(std::string systemName);

    /*!
     * \brief Signal to move player to location.
     * \param systemName location to move.
     */
    void movePlayerHere(std::string systemName);

    /*!
     * \brief Signal which ship was saved.
     * \param ship pointer
     */
    void shipSaved(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief Attempt to complete mission signal
     * \param system name
     */
    void tryMission(std::string systemName);

    /*!
     * \brief Salvage ship signal
     * \param ship pointer
     */
    void salvageShip(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief Send signal about buy action.
     * \param system name
     */
    void buyInit(std::string systemName);

    /*!
     * \brief Send signal about repair action.
     * \param system name
     */
    void repairInit(std::string systemName);

    /*!
     * \brief Sends error signal about failed execution.
     */
    void errorInExecution();
private:

    /*!
     * \brief populates the scene
     * \pre number of items in scene == 0
     * \post number of items in scene == len StarSystemVector.
     */
    void populateScene(std::shared_ptr<Common::StarSystem::StarSystemVector> starSystems);

    /*!
     * \brief makeConnections
     * \param connections
     */
    void makeConnections(std::map<std::string, std::vector<std::string> > connections);

    /*!
     * \brief status if frame can be used or not.
     */
    bool initialized_;

    /*!
     * \brief playerLocation_ star system name.
     */
    std::string playerLocation_;

    /*!
     * \brief systems in player range.
     */
    std::vector<std::string> inPlayerRange_;

    /*!
     * \brief map of ships displayed in the scene.
     */
    std::map<std::shared_ptr<Common::Ship>, std::shared_ptr<ShipItem> > shipsInSky_;

    /*!
     * \brief map between system names and GraphicsItems.
     */
    std::map<std::string, std::shared_ptr<SolarSystemItem>> starMap_;

    /*!
     * \brief View of the scene
     */
    std::shared_ptr<GalaxyView> view_;

    /*!
     * \brief Scene containing the GraphicsItems.
     */
    QGraphicsScene *scene_;

    /*!
     * \brief Parent widget.
     */
    QWidget parent_;

};

}//StudentUI

#endif // GALAXYMAP_HH
