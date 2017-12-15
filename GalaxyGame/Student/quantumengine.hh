#ifndef QUANTUMENGINE_HH
#define QUANTUMENGINE_HH

#include <memory>

#include "quantummap.hh"
#include "shipengine.hh"
#include "starsystem.hh"

namespace Student
{

/*!
 * \brief Custom engine for playership to use.
 */
class QuantumEngine : public Common::ShipEngine
{
public:

    /*!
     * \brief Max health for engine.
     */
    static const Health MAX_HEALTH;

    /*!
     * \brief Max Uncertainty
     */
    static const int MAX_UNCERTAINTY;

    /*!
     * \brief Constructor for engine
     * \param map pointer used to navigate in the galaxy
     */
    QuantumEngine(std::shared_ptr<QuantumMap> map);

    /*!
     * \brief deconstructor
     */
    ~QuantumEngine() = default;

    /*!
     * \brief If player can move.
     * \return true if player can move, false otherwise
     */
    bool canStart() const override;

    /*!
     * \brief Execute move action.
     * \param destination target system
     * \return system that ship ended up in.
     */
    std::shared_ptr<Common::StarSystem> executeMove(std::shared_ptr<Common::StarSystem> destination);

    /*!
     * \brief Checks if system is valid location
     * \param source - system that player is in.
     * \param destination - system that player is going to
     * \return true if valid, false otherwise.
     */
    bool isValidTrip(std::shared_ptr<Common::StarSystem> source,
                     std::shared_ptr<Common::StarSystem> destination) const override;

    /*!
     * \brief get valid destinations from source
     * \param source current system.
     * \return vector containing StarSystem pointers.
     */
    Common::StarSystem::StarSystemVector getValidDestinations(std::shared_ptr<Common::StarSystem> source) const override;

    /*!
     * \brief On start increase uncertainty
     */
    void onStart() override;

    /*!
     * \brief Required turns for destination.
     * \param source position
     * \param destination position
     * \return 1
     */
    int requiredTurns(std::shared_ptr<Common::StarSystem> source,
                      std::shared_ptr<Common::StarSystem> destination) const override;

    /*!
     * \brief increase uncertainty a random amount between 1 to 10
     */
    void increaseUncertainty();

    /*!
     * \brief reset uncertainty to 0.
     */
    void resetUncertainty();

    /*!
     * \brief get current uncertainty value.
     * \return uncertainty
     */
    int getUncertainty();

    /*!
     * \brief Get StarMap for connection building.
     * \return map
     */
    std::map<std::string, std::vector<std::string> > getStringMap();

    /*!
     * \brief Get pointer to map
     * \return pointer to map
     */
    std::shared_ptr<QuantumMap> getMap();

private:

    /*!
     * \brief Uncertainty amount.
     */
    int uncertaintyFactor_;

    /*!
     * \brief Pointer to map
     */
    std::shared_ptr<QuantumMap> map_;
};
}//Student
#endif // QUANTUMENGINE_HH
