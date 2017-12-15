#ifndef IMISSION_HH
#define IMISSION_HH

#include <QObject>

#include "starsystem.hh"

namespace Student
{

/*!
 * \brief The virtual mission class base.
 */
class IMission : public QObject
{
public:

    /*!
     * \brief class deconstructor
     */
    virtual ~IMission() = default;

    /*!
     * \brief get the current time left
     * \return unsigned number
     */
    virtual unsigned getTimeLeft() = 0;

    /*!
     * \brief gets the location of the mission.
     * \return pointer to Starsystem
     */
    virtual std::shared_ptr<Common::StarSystem> getLocation() = 0;

    /*!
     * \brief Get status if mission is still active.
     * \return true if not failed or succeeded.
     */
    virtual bool getStatus() = 0;

    /*!
     * \brief Try completing the mission.
     */
    virtual void tryComplete() = 0;
};

}//Student
#endif // IMISSION_HH
