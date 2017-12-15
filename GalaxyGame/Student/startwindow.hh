#ifndef STARTWINDOW_HH
#define STARTWINDOW_HH

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

namespace StudentUI
{

/*!
 * \brief The StartWindow class is a GUI view for representing main menu / start
 *        window. It launches when program starts.
 */
class StartWindow : public QWidget
{
    Q_OBJECT
public:

    /*!
     * \brief StartWindow constructor
     * \param MainWindow as a parent
     */
    StartWindow(QObject *parent);

    /*!
     * \brief shows or hides continue button depending on gameOn_ value
     * \param gameOn_ boolean value
     */
    void setGame(bool val);

    /*!
     * \brief gets gameOn_ value
     * \return gameOn_ value
     */
    bool getGame();

signals:

    /*!
     * \brief signal to start game
     * \param player name
     */
    void startGame(QString name);

    /*!
     * \brief signal to move to highscore page
     */
    void checkHighScore();

    /*!
     * \brief signal to continue game (move to game window)
     */
    void continueGame();

    /*!
     * \brief signal to exit game, comes from game window
     */
    void exitGame();

    /*!
     * \brief signal to exit game, comes from pushing
     *        the exit game button
     */
    void exitSignal();

private slots:

    /*!
     * \brief slot for emitting startGame signal
     */
    void pressedStart();

    /*!
     * \brief slot for emitting checkHighScore signal
     */
    void pressedHighScore();

    /*!
     * \brief slot for emitting exitGame signal
     */
    void pressedExit();

    /*!
     * \brief slot for emitting continueGame signal
     */
    void pressedContinue();

    /*!
     * \brief slot for emitting exitSignal signal
     */
    void quitGame();

private:

    QString defaultName_;
    /*!
     * \brief boolean value representing if game is paused and in
     *        process
     */
    bool gameOn_;

    /*!
     * \brief MainWindow as a parent
     */
    QObject* parent_;

    /*!
     * \brief label for player name
     */
    QLabel* playerNameLabel_;

    /*!
     * \brief input text field for player name
     */
    QLineEdit* playerNameField_;

    /*!
     * \brief button for starting the game
     */
    QPushButton* startGameBtn_;

    /*!
     * \brief button for going to high score page
     */
    QPushButton* highScoresBtn_;

    /*!
     * \brief button for continuing game, only visible if game is paused and in
     *        process
     */
    QPushButton* continueButton_;

    /*!
     * \brief button for exiting the game
     */
    QPushButton* quit_;
};

}//StudentUI
#endif // STARTWINDOW_HH
