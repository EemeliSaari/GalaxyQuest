#ifndef STATSFRAME_HH
#define STATSFRAME_HH

#include <memory>

#include <QFrame>
#include <QLabel>
#include <QLCDNumber>
#include <QSize>

#include "statistics.hh"

namespace StudentUI
{

/*!
 * \brief Statistics UI part.
 */
class StatsFrame : public QFrame
{
    Q_OBJECT
public:

    /*!
     * \brief Constructor
     * \param QWidget parent
     */
    StatsFrame(QWidget *parent);

    /*!
     * \brief deconstructor
     */
    ~StatsFrame();

    /*!
     * \brief Recommended size for frame
     * \return size as QSize
     */
    QSize sizeHint() const override;

    /*!
     * \brief Minumum recommended size for frame
     * \return size as QSize
     */
    QSize minimumSizeHint() const override;

    /*!
     * \brief Reset the displayed stats
     */
    void reset();

public slots:

    /*!
     * \brief Update displayed score label
     * \param new value
     */
    void updateScore(unsigned newValue);

    /*!
     * \brief Update displayed credits label
     * \param new value
     */
    void updateCredits(unsigned newValue);

    /*!
     * \brief Update displayed saved ships count label
     * \param new value
     */
    void updateSaved(unsigned newValue);

    /*!
     * \brief Update displayed lost ships count label
     * \param newValue
     */
    void updateLost(unsigned newValue);

    /*!
     * \brief Update displayed active ships count label
     * \param newValue
     */
    void updateActive(unsigned newValue);

private:
    enum { BoardWidth = 20, BoardHeight = 20};

    /*!
     * \brief QWidget parent
     */
    QWidget *parent_;

    /*!
     * \brief Score label
     */
    QLabel *score_;

    /*!
     * \brief Credits label
     */
    QLabel *credits_;

    /*!
     * \brief Lost ships label
     */
    QLabel *lost_;

    /*!
     * \brief Saved ships label
     */
    QLabel *saved_;

    /*!
     * \brief Active ships label
     */
    QLabel *active_;

protected:

    /*!
     * \brief Helper function to create simple text labels.
     * \param text of the label
     * \return QLabel
     */
    QLabel *createLabel(const QString &text);
};

}//Student

#endif // STATSFRAME_HH
