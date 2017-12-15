#ifndef GALAXY_HH
#define GALAXY_HH

#include <string>
#include <vector>

#include <QObject>

#include "igalaxy.hh"
#include "point.hh"
#include "ship.hh"
#include "starsystem.hh"

namespace Student
{

/*!
 * \brief The Galaxy class
 */
class Galaxy : private QObject, public Common::IGalaxy
{
    Q_OBJECT
public:

    /*!
     * \brief Galaxy constructor
     */
    Galaxy();

    /*!
     * \brief Galaxy destructor
     */
    ~Galaxy();

    /*!
     * \brief adds ship to the galaxy
     * \param ship pointer
     * \post ship is added in the ships_ vector
     * \throw StateException if ship already in the vector
     */
    void addShip(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief removes ship from the galaxy
     * \param ship pointer
     * \post ship has been removed from the ship_ vector
     * \throw ObjectNotFoundException if ship not in ship_ vector
     */
    void removeShip(std::shared_ptr<Common::Ship> ship);

    /*!
     * \brief adds starsystem to the galaxy
     * \param starSystem pointer
     * \post starsystem has been added to starsystem vector
     * \throw StateException if starsystem with same id/name/coordinate is
     *        already in the vector.
     */
    void addStarSystem(std::shared_ptr<Common::StarSystem> starSystem);

    /*!
     * \brief method returns all the ships in the galaxy in a vector pointer
     * \return pointer to ShipVector
     */
    std::shared_ptr<ShipVector> getShips();

    /*!
     * \brief method return all the startsystems in the galaxy in a vector pointer
     * \return pointer to StarSystemVector
     */
    std::shared_ptr<Common::StarSystem::StarSystemVector> getStarSystems();

    /*!
     * \brief method returns starsystems close to given location
     * \param System reference location
     * \param range given range
     * \throw ObjectNotFoundException if system not in vector
     * \return starSystemVector of all the systems in range.
     */
    Common::StarSystem::StarSystemVector getSystemsInRange
            (std::shared_ptr<Common::StarSystem> system, int range);

    /*!
     * \brief method returns randomly chosen system outside given range
     * \param currentSystem reference location
     * \param range given integer range
     * \throw ObjectNotFoundException if system not found
     * \return pointer to StarSystem vector
     */
    std::shared_ptr<Common::StarSystem> getRandomSystemOutsideRange(std::shared_ptr<Common::StarSystem> currentSystem, int range);

    /*!
     * \brief method return randomly chosen system
     * \throw ObjectNotFoundException if starSystems_ vector is empty
     * \return pointer to random system
     */
    std::shared_ptr<Common::StarSystem> getRandomSystem();

    /*!
     * \brief method returns ships in given starsystem
     * \param starsystem name
     * \return ShipVector containing pointers to all the ships
     */
    ShipVector getShipsInStarSystem(std::string name);

    /*!
     * \brief method returns starsystem object pointer by given name
     * \param starsystem name
     * \throw ObjectNotFoundException if system not in starSystem_ vector
     * \return pointer to system
     */
    std::shared_ptr<Common::StarSystem> getStarSystemByName(std::string name);

    /*!
     * \brief method returns starsystem object pointer by given id
     * \param id of the system
     * \throw ObjectNotFoundException if system not in starSystem_ vector
     * \return pointer to system
     */
    std::shared_ptr<Common::StarSystem> getStarSystemById(unsigned id);

    /*!
     * \brief method returns vector of all starsystem names
     * \return vector containing all the names
     */
    std::vector<std::string> getSystemNames();

    /*!
     * \brief method returns vector of all starsystem id's
     * \return vector containing all the id's
     */
    std::vector<unsigned> getSystemIds();

private:
    /*!
     * \brief Galaxy initialization method
     */
    void init();

    /*!
     * \brief ships_ pointer to vector that contains pointers to ships in the galaxy
     */
    std::shared_ptr<ShipVector> ships_;

    /*!
     * \brief starSystems_ vector that contains pointers to starsystems in the galaxy
     */
    std::shared_ptr<Common::StarSystem::StarSystemVector> starSystems_;

};

}//Student

#endif // GALAXY_HH
