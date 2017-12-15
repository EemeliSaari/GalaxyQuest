#ifndef GAMEOVERDIALOG_HH
#define GAMEOVERDIALOG_HH

#include <QWidget>
#include <QDialog>
#include <QFrame>
#include <QPushButton>
#include <QString>

namespace StudentUI
{

/*!
 * \brief The GameOverDialog is a dialog window shown when game is over
 */
class GameOverDialog : public QDialog
{
    Q_OBJECT
public:

    /*!
     * \brief GameOverDialog constructor
     * \param enoughForHighScore boolean value whether player gets to the high score list
     *        or not
     * \param playerName
     * \param score final score
     * \param parent
     */
    GameOverDialog(bool enoughForHighScore,
                   QString playerName,
                   unsigned score,
                   QWidget *parent = 0);

private:

    /*!
     * \brief button for getting back to main menu
     */
    QPushButton *mainMenuBtn_;

    /*!
     * \brief frame for label
     */
    QFrame *labelFrame_;
};

}//Student

#endif // GAMEOVERDIALOG_HH
