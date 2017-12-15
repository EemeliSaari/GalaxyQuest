#ifndef RESCUEMISSION_H
#define RESCUEMISSION_H

#include <QObject>

#include "imission.hh"
#include "starsystem.hh"

namespace Student
{

/*!
 * \brief RescueMission class
 */
class RescueMission : public IMission
{
    Q_OBJECT
public:

    /*!
     * \brief Default reward value.
     */
    static const int REWARD;

    /*!
     * \brief The different mission types.
     */
    enum MISSION_TYPE
    {
        Meteorite,
        Decease,
        SkyNet,
        BeerShortage
    };

    /*!
     * \brief Constructor for class.
     * \param location where the mission is spawned.
     * \param time for the mission unsigned.
     * \param QObject parent.
     */
    RescueMission(std::shared_ptr<Common::StarSystem> location,
                  unsigned time,
                  QString playerName,
                  QObject *parent = nullptr);

    /*!
     * \brief deconstructor for class
     */
    ~RescueMission();

    /*!
     * \brief Get the amount of time left for mission.
     * \return return the time left
     */
    unsigned getTimeLeft() override;

    /*!
     * \brief Get the location for the mission.
     * \return return pointer to starsystem.
     */
    std::shared_ptr<Common::StarSystem> getLocation() override;

    /*!
     * \brief Get the status of the mission completed or still going.
     * \return boolean value
     */
    bool getStatus() override;

    /*!
     * \brief Tell Mission if it's completed.
     */
    void tryComplete();

signals:

    /*!
     * \brief Signal if mission is failed.
     */
    void attemptFailed();

    /*!
     * \brief Signal if mission succeeded.
     */
    void missionSuccess(std::shared_ptr<Common::StarSystem> location, int reward);

    /*!
     * \brief missionFailed
     * \param location
     */
    void missionFailed(std::shared_ptr<Common::StarSystem> location);

    /*!
     * \brief opened the dialog window.
     */
    void dialogOpened();

    /*!
     * \brief closed the dialog window
     */
    void dialogClosed();

public slots:

    /*!
     * \brief Slot to add turn to mission. Emit missionFailed if time_== 0
     */
    void reduceTurn();

private slots:

    /*!
     * \brief closeDialog
     */
    void closeDialog();

private:

    /*!
     * \brief Pointer to StarSystem.
     */
    std::shared_ptr<Common::StarSystem> location_;

    /*!
     * \brief Current time for mission.
     */
    unsigned time_;

    /*!
     * \brief Status if mission is completed.
     */
    bool finished_;

    /*!
     * \brief Status if mission is failed.
     */
    bool failed_;

    /*!
     * \brief Random number that was generated.
     */
    double rng_;
};

}

#endif // RESCUEMISSION_H
