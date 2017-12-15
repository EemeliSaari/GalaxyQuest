#ifndef STARTDIALOG_HH
#define STARTDIALOG_HH

#include <QDialog>
#include <QString>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

namespace StudentUI
{

/*!
 * \brief StartDialog to give information to player about the game
 */
class StartDialog : public QDialog
{
    Q_OBJECT
public:

    /*!
     * \brief Constructor
     * \param Playername
     */
    StartDialog(QString playerName, QWidget *parent = 0);

private:

    /*!
     * \brief Player name
     */
    QString playerName_;

    /*!
     * \brief Labels are stored here.
     */
    QTabWidget *tab_;

    /*!
     * \brief Main layout for the dialog
     */
    QVBoxLayout *layout_;

    /*!
     * \brief Accept button
     */
    QPushButton *acceptButton_;

    /*!
     * \brief Create general info label
     * \return QLabel pointer
     */
    QLabel *createGeneral();

    /*!
     * \brief Create mission info label
     * \return QLabel pointer
     */
    QLabel *createMissions();

    /*!
     * \brief Create score info label
     * \return QLabel pointer
     */
    QLabel *createScore();
};

} //StudentUI
#endif // STARTDIALOG_HH
