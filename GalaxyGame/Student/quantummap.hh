#ifndef QUANTUMMAP_HH
#define QUANTUMMAP_HH

#include <memory>
#include <map>
#include <vector>
#include <string>

#include "galaxy.hh"
#include "starsystem.hh"

namespace Student
{

/*!
 * \brief The Quantum connections generated semi-randomly for player ship
 *        and for the galaxy scene to use.
 */
class QuantumMap
{
public:

    /*!
     * \brief Constructor
     * \param galaxy pointer
     */
    QuantumMap(std::shared_ptr<Galaxy> galaxy);

    /*!
     * \brief deconstructor
     */
    ~QuantumMap() = default;

    /*!
     * \brief Get the systems in range.
     * \param system pointer
     * \return vector of starsystem pointers
     */
    std::vector<std::shared_ptr<Common::StarSystem> > systemsInRange(std::shared_ptr<Common::StarSystem> system);

    /*!
     * \brief Get info if specific jump is valid or not
     * \param from Starsystem pointer
     * \param to Starsystem pointer
     * \return true if valid, false otherwise
     */
    bool validJump(std::shared_ptr<Common::StarSystem> from, std::shared_ptr<Common::StarSystem> to);

    /*!
     * \brief Get random system from all of the systems.
     * \param Current system.
     * \return pointer to random system.
     */
    std::shared_ptr<Common::StarSystem> getRandom(std::shared_ptr<Common::StarSystem> current);

    /*!
     * \brief Transform the network map to string map containing names of starsystems.
     * \return map
     */
    std::map<std::string, std::vector<std::string>> getStrings();

private:

    /*!
     * \brief Start point for the algorith.
     */
    void initializeConnections();

    /*!
     * \brief Initialize the must have connections in able for connections to
     *        cover every system without fractions.
     */
    void cheat();

    /*!
     * \brief Finds the nearest neighbours for system
     * \param system in place
     * \return nearest systems in vector
     */
    std::vector<std::shared_ptr<Common::StarSystem> > nearestNeighbours(std::shared_ptr<Common::StarSystem> system);

    /*!
     * \brief Check if the particular system is valid system.
     * \param system
     * \param target system that is being valuated
     * \return true if valid, false otherwise
     */
    bool validNeighbour(std::shared_ptr<Common::StarSystem> system, std::shared_ptr<Common::StarSystem> targetSys);

    /*!
     * \brief Connect system back to points that it was attached to.
     * \param system
     */
    void connectBack(std::shared_ptr<Common::StarSystem> system);

    /*!
     * \brief Find next system to be connected
     * \return system pointer
     */
    std::shared_ptr<Common::StarSystem> findNext();

    /*!
     * \brief All systems storage that algorith uses.
     */
    std::vector<std::shared_ptr<Common::StarSystem> > allSystems_;

    /*!
     * \brief Pointer to galaxy.
     */
    std::shared_ptr<Galaxy> galaxy_;

    /*!
     * \brief Network of starsystem connections.
     */
    std::map<std::shared_ptr<Common::StarSystem>, std::vector<std::shared_ptr<Common::StarSystem> > > network_;
};

}//Student
#endif // QUANTUMMAP_HH
