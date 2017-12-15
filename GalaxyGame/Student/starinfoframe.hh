#ifndef STARINFOFRAME_HH
#define STARINFOFRAME_HH

#include <memory>
#include <vector>

#include <QFrame>
#include <QWidget>
#include <QTabWidget>
#include <QLabel>

#include "starsystem.hh"
#include "ship.hh"
#include "imission.hh"

namespace StudentUI
{

/*!
 * \brief The Star info frame containing information
 *        about the selected starsystem.
 */
class StarInfoFrame : public QFrame
{
    Q_OBJECT
public:

    /*!
     * \brief Constructor for class
     * \param QWidget as parent.
     */
    StarInfoFrame(QWidget *parent);

    /*!
     * \brief Deconstructor
     */
    ~StarInfoFrame();

    /*!
     * \brief Recommended size for Frame.
     * \return size as QSize
     */
    QSize sizeHint() const override;

    /*!
     * \brief Minimum recommended size for Frame
     * \return size as QSize
     */
    QSize minimumSizeHint() const override;

    /*!
     * \brief Reset the text labels.
     */
    void reset();

public slots:

    /*!
     * \brief Update text labels according to params.
     * \param system pointer containing information about the system.
     * \param ships vector containing ships in the system.
     */
    void updateInfo(std::shared_ptr<Common::StarSystem> system,
                    std::vector<std::shared_ptr<Common::Ship>> ships);

private:
    enum { BoardWidth = 35, BoardHeight = 35};

    /*!
     * \brief Converts StarSystem::ECONOMY_TYPE to QString
     * \param StarSystem::ECONOMY_TYPE
     * \return QString
     */
    QString getEconomy(Common::StarSystem::ECONOMY_TYPE type);

    /*!
     * \brief QTabWidget containing Labels
     */
    QTabWidget *tab_;

    /*!
     * \brief QLabel containing information about starsystem
     */
    QLabel *general_;

    /*!
     * \brief QLabel containing information about ships in system.
     */
    QLabel *ships_;
};

}
#endif // STARINFOFRAME_HH
