#ifndef GAMEWINDOW_HH
#define GAMEWINDOW_HH

#include <memory>

#include <QObject>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QMenu>
#include <QMenuBar>

#include "gamecontroller.hh"
#include "gamewindowlayout.hh"
#include "galaxyframe.hh"
#include "galaxyview.hh"
#include "hpbar.hh"
#include "statsframe.hh"
#include "starinfoframe.hh"

namespace StudentUI
{

/*!
 * \brief The GameWindow class is a GUI view for representing the gameplay window
 */
class GameWindow : public QFrame
{
    Q_OBJECT
public:

    /*!
     * \brief GameWindow constructor
     * \param MainWindow as a parent
     */
    GameWindow(QObject *parent);

    /*!
     * \brief starts the game
     * \param players name
     */
    void startGame(QString playerName);

    /*!
     * \brief resets game
     */
    void resetHard();

    /*!
     * \brief method for getting game state (game on process or not)
     * \return game state
     */
    bool getGame();

    /*!
     * \brief Get the player name
     * \return QString playe rname
     */
    QString getPlayerName();

public slots:

    /*!
     * \brief starts next turn
     */
    void newTurn();

    /*!
     * \brief gets called when game is over, does the high score checking
     */
    void gameOver(unsigned finalScore);

    /*!
     * \brief game is paused
     * \param location
     */
    void pause(std::string location = 0);

    /*!
     * \brief game continues
     */
    void continueGame();

private slots:

    /*!
     * \brief exits the game
     */
    void exitGame();

    /*!
     * \brief exits to main menu
     */
    void exitMainMenu();

    /*!
     * \brief ends current turn
     */
    void endTurnPressed();

    /*!
     * \brief starts new game
     */
    void newGame();

signals:

    /*!
     * \brief singal for exiting game
     */
    void exit();

    /*!
     * \brief signal for getting back to main menu / start window
     * \param game state
     */
    void mainMenu(bool var);

private:

    /*!
     * \brief game state (game on process or not)
     */
    bool state_;

    /*!
     * \brief players name
     */
    QString playerName_;

    /*!
     * \brief GameWindowLayout object
     */
    std::shared_ptr<GameWindowLayout> gameLayout_;

    /*!
     * \brief StatsFrame object
     */
    std::shared_ptr<StatsFrame> statsFrame_;

    /*!
     * \brief minimap
     */
    std::shared_ptr<QFrame> miniMap_;

    /*!
     * \brief bar widget for representing resources
     */
    std::shared_ptr<QFrame> resourceBar_;

    /*!
     * \brief player health bar
     */
    std::shared_ptr<HpBar> hpBar_;

    /*!
     * \brief end turn
     */
    std::shared_ptr<QFrame> endTurnFrame_;

    /*!
     * \brief menu bar
     */
    std::shared_ptr<QMenuBar> menu_;

    /*!
     * \brief GalaxyFrame object
     */
    std::shared_ptr<StudentUI::GalaxyFrame> gameFrame_;

    /*!
     * \brief StarInfoFrame object
     */
    std::shared_ptr<StudentUI::StarInfoFrame> infoFrame_;

    /*!
     * \brief MainWindow as a parent
     */
    QObject *parent_;

    /*!
     * \brief GameController object
     */
    std::shared_ptr<Student::GameController> controller_;

    /*!
     * \brief creates the end turn button
     */
    void createButtonFrame();

    /*!
     * \brief creates the menu button
     */
    void createMenu();
};

} //Student
#endif // GAMEWINDOW_HH
