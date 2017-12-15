#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QMainWindow>
#include <QFrame>
#include <QStackedWidget>

#include "eventhandler.hh"
#include "gamecontroller.hh"
#include "gamewindow.hh"
#include "ieventhandler.hh"
#include "highscorewindow.hh"
#include "ship.hh"
#include "startwindow.hh"

namespace Ui
{
class MainWindow;
}

/*!
 * \brief The MainWindow class is a top level GUI controller class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /*!
     * \brief MainWindow constructor
     */
    explicit MainWindow(QWidget *parent = 0);

    /*!
     * \brief MainWindow destructor
     */
    ~MainWindow();

private slots:

    /*!
     * \brief sets QStackedWidget index to 0 and gets user to main menu / start window
     */
    void startView();

    /*!
     * \brief exits from gameplay window to main menu / start window
     * \param boolean value whether the game is reset or not
     */
    void exitGame(bool val);

    /*!
     * \brief sets QStackedWidget index to 1 and gets user to gameplay window
     */
    void continueGame();

    /*!
     * \brief checks the state of game and and calls the continueGame method,
     *        starts new game or paused game continues
     * \param playerName
     */
    void gameView(QString playerName);

    /*!
     * \brief sets QStackedWidget index to 2 and gets user to high score window
     */
    void highscoreView();

private:
    /*!
     * \brief UI component
     */
    Ui::MainWindow *ui;

    /*!
     * \brief GUI view for game window
     */
    StudentUI::GameWindow *gameWindow_;

    /*!
     * \brief GUI view for main menu / start window
     */
    StudentUI::StartWindow *startWindow_;

    /*!
     * \brief GUI view for high score window
     */
    StudentUI::HighScoreWindow *highScoreWindow_;

    /*!
     * \brief all views are stored in QStackedWidget, accessing widgets is done
     *        through indexes
     */
    QStackedWidget *mainLayout_;

    bool launch_;
};

#endif // MAINWINDOW_H
