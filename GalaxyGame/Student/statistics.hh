#ifndef STATISTICS_HH
#define STATISTICS_HH

#include <string>

#include <QObject>

#include "istatistics.hh"

namespace Student
{

/*!
 * \brief Exception class for loan
 */
class LoanExceeded
{
};

class StatisticsInvariance
{
};

/*!
 * \brief Statistic class to keep track of player score in the game
 * \invariant credits >= MAX_LOAN_ALLOWED && getPoints() > 0 && getLostShips > 0
 *            && getSavedShips > 0
 */
class Statistics : public QObject, public Common::IStatistics
{
    Q_OBJECT
public:

    /*!
     * \brief Maximum loan that is allowed
     */
    static const int MAX_LOAN_ALLOWED;

    /*!
     * \brief constructor for Statistics class.
     * \param parent QObject so class can use signals
     * \post initial values are all set to 0
     */
    Statistics(QObject *parent = 0);

    /*!
     *  \brief deconstructor
     */
    ~Statistics();

    /*!
     * \brief Gets saved ships count.
     */
    unsigned getSavedShips() const;

    /*!
     * \brief Gets lost ships count.
     */
    unsigned getLostShips() const;

    /*!
     * \brief Get the amount of current points.
     */
    unsigned getPoints() const;

    /*!
     * \brief Get the current balance of credits.
     * \return credit balance as constant.
     */
    int getCreditBalance() const;

    /*!
     * \brief Add n amount of points and emits updatePoints signal
     * \param amount of points to be added.
     * \post points = previousPoints + amount && points < MAX_UNSIGNED
     * \throw std::overflow_error if points sum exceeds the unsigned maximum limit
     */
    void addPoints(unsigned amount);

    /*!
     * \brief Reduce n amount of points. and emit updatePoints signal
     * \param amount of points to be reduced.
     * \post points = previousPoints - amount && points - amount > 0
     * \throw std::underflow_error if points - amoun <= 0
     */
    void reducePoints(unsigned amount);

    /*!
     * \brief Adds one to saved ships
     * \post savedShipsNow = savedShipsPre + 1
     * \throw std::overflow_error if savedShipsNow + 1 > MAX_UNSIGNED
     */
    void addSavedShip();

    /*!
     * \brief Add one to lost ships.
     * \post lostShipsNow = lostShipsPre + 1
     * \throw std:.overflow_error if lostShipsNow + 1 > MAX_UNSIGNED
     */
    void addLostShip();

    /*!
     * \brief Add n amount of credits.
     * \param amount of credits to be added.
     * \post creditsNow = creditsPre + amount
     * \throw std::overflow_errer if creditsNow + amount > MAX_UNSIGNED
     */
    void addCredits(unsigned amount);

    /*!
     * \brief Reduce n amount of credits.
     * \param amount of credits to be added.
     * \post creditsNow > MAX_LOAN_AMOUNT && creditsNow = creditsPre - amount
     * \throw LoanExceeded if creditsNow - amount < MAX_LOAN_AMOUNT
     * \throw std::underflow_error if creditsNow - amount < MIN_INT
     */
    void reduceCredits(unsigned amount);

signals:

    /*!
     * \brief Update saved ships signal
     * \param newValue
     */
    void updateSavedShips(unsigned newValue);

    /*!
     * \brief Update lost ships signal
     * \param newValue
     */
    void updateLostShips(unsigned newValue);

    /*!
     * \brief Update points signal
     * \param newValue
     */
    void updatePoints(unsigned newValue);

    /*!
     * \brief Update credits signal
     * \param newValue
     */
    void updateCredits(unsigned newValue);

private:

    /*!
     * \brief savedShips_ variable of the number of ships player
     *        has saved.
     */
    unsigned savedShips_;

    /*!
     * \brief lostShips_ variable of number of ships player has
     *        lost.
     */
    unsigned lostShips_;

    /*!
     * \brief points_ number of points player has gained.
     */
    unsigned points_;

    /*!
     * \brief credits_ number of credits player has.
     */
    int credits_;

};
}//Student

#endif // STATISTICS_HH
