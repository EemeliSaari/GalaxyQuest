#ifndef SOLARSYSTEMITEM_HH
#define SOLARSYSTEMITEM_HH

#include <vector>

#include <QColor>
#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QRectF>
#include <QSignalMapper>
#include <QString>

#include "ship.hh"

namespace StudentUI
{

/*!
 * \brief The QGraphics item for StarSystem
 */
class SolarSystemItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:

    /*!
     * \brief Constructor
     * \param x coordinate
     * \param y coordinate
     * \param name of the system
     */
    SolarSystemItem(int x,
                    int y,
                    std::string name);

    /*!
     * \brief Bounding box for the object
     * \return the QRectF of the bounding box.
     */
    QRectF boundingRect() const override;

    /*!
     * \brief Shape of the object
     * \return QPainterPath
     */
    QPainterPath shape() const override;

    /*!
     * \brief Paints the object in the scene.
     * \param QPainter painter
     * \param Scene specific options.
     * \param QWidget widget
     */
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    /*!
     * \brief Remove ship from this system.
     * \param ship pointer
     * \post pointer has been removed from the ships vector
     * \throw ObjectNotFoundException if object not in ship
     */
    void shipLeft(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief Add ship to this system
     * \param ship pointer
     * \post ship is added to the ships vector
     * \throw GameException if ship already in vector
     */
    void shipEntered(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief Add ship in trouble to this system.
     * \param ship pointer
     * \post ship has been added to the trouble vector
     * \throw GameException if ship already in vector
     */
    void shipInTrouble(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief Remove ship in trouble from this system.
     * \param ship pointer
     * \post ship has been removed from the vector
     * \throw ObjectNotFoundException if object not in ship
     */
    void shipNotInTrouble(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief Add salvageable ship to this system.
     * \param ship pointer
     * \post ship has been added to the salvage vector
     * \throw GameException if ship already in vector
     */
    void addSalvage(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief Remove salvageable ship from this sytem.
     * \param ship pointer
     * \post ship has been removed from the vector
     * \throw ObjectNotFoundException if object not in ship
     */
    void removeSalvage(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief Set system to ether host or unhost player.
     * \param True if hosting, false if not.
     */
    void setHostingPlayer(bool val);

    /*!
     * \brief Set system to be in range for player
     * \param True if in range, false otherwise.
     */
    void setRange(bool val);

    /*!
     * \brief Set system to host a mission.
     * \param True if hosting mission, false otherwise.
     */
    void setMission(bool val);

    /*!
     * \brief Set system to take player interactions
     * \param True if player can interact, false otherwise
     */
    void setActions(bool val);

    /*!
     * \brief Set system to take player movement interaction.
     * \param True if player can move, false otherwise.
     */
    void setMoveable(bool val);

    /*!
     * \brief Set system to take repair interaction.
     * \param True if on, false otherwise.
     */
    void setRepair(bool val);

private:

    /*!
     * \brief local x coordinate
     */
    int x_;

    /*!
     * \brief local y coordinate
     */
    int y_;

    /*!
     * \brief Ships that are salvageable
     */
    std::vector<std::shared_ptr<Common::Ship>> salvageable_;

    /*!
     * \brief Ships in system.
     */
    std::vector<std::shared_ptr<Common::Ship> > ships_;

    /*!
     * \brief Ships in trouble
     */
    std::vector<std::shared_ptr<Common::Ship> > troubleShips_;

    /*!
     * \brief bool if System hosts player or not.
     */
    bool hostingPlayer_;

    /*!
     * \brief Bool if in player range
     */
    bool inPlayerRange_;

    /*!
     * \brief Bool if mission system.
     */
    bool missionSystem_;

    /*!
     * \brief Bool if valid interactions
     */
    bool validActions_;

    /*!
     * \brief Bool if valid repair system
     */
    bool canRepair_;

    /*!
     * \brief Bool if player can move to this system.
     */
    bool validMove_;

    /*!
     * \brief Name of the system.
     */
    std::string name_;

    /*!
     * \brief Opens interaction menu according to game state.
     * \param Location of the cliced global frame position.
     */
    void openMenu(QPoint loc);

private slots:

    /*!
     * \brief Slot if player is entering to this system.
     */
    void playerEntering();

    /*!
     * \brief Slot if player chose to save ship.
     * \param index of the clicked menu action.
     */
    void savingShip(int index);

    /*!
     * \brief Slot if player chose to try completing mission
     */
    void doMission();

    /*!
     * \brief Slot if player chose to try to salvage a ship.
     * \param index of the clicked menu action
     */
    void salvage(int index);

    /*!
     * \brief Slot if player chose to initialize repair event.
     */
    void playerRepair();

    /*!
     * \brief Slot if player chose to initialize buying event.
     */
    void playerBuying();

signals:

    /*!
     * \brief Signal if player selected this item.
     * \param item name
     */
    void imSelected(std::string myName);

    /*!
     * \brief Signal if player is moving here
     * \param item name
     */
    void playerMovingHere(std::string myName);

    /*!
     * \brief Signal which ship player is saving.
     * \param target ship pointer
     */
    void savedShip(std::shared_ptr<Common::Ship> target);

    /*!
     * \brief Signal the attempted mission completion.
     * \param item name
     */
    void tryCompleteMission(std::string myName);

    /*!
     * \brief Signal the ship that player is salvageing.
     * \param target ship pointer
     */
    void salvagedShip(std::shared_ptr<Common::Ship> target);

    /*!
     * \brief Init buy event.
     * \param buy event location name.
     */
    void initBuying(std::string myName);

    /*!
     * \brief Init repair event.
     * \param repair event location.
     */
    void initRepairing(std::string myName);

protected:

    /*!
     * \brief Mouse events are handled here.
     * \param QGraphicsScene specific mouse event.
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

}//StudentUI

#endif // SolarSystemItem_HH
