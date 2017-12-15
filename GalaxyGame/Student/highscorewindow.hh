#ifndef HIGHSCOREWINDOW_HH
#define HIGHSCOREWINDOW_HH

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

namespace StudentUI
{

/*!
 * \brief The HighScoreWindow class is a GUI view for representing
 *        current highscore
 */
class HighScoreWindow : public QWidget
{
    Q_OBJECT
public:

    /*!
     * \brief HighScoreWindow constructor
     * \param gets MainWindow as parent
     */
    HighScoreWindow(QObject *parent);

    /*!
     * \brief Updates the score labels
     */
    void updateScore();

    /*!
     * \brief initialize the Window components
     */
    void initialize();

signals:

    /*!
     * \brief signal for getting back to startwindow
     */
    void goBack();

private slots:

    /*!
     * \brief this slot emits the goBack signal,
     *        connected to back buttons click signal
     */
    void pressedBack();

private:

    /*!
     * \brief MainWindow as a parent
     */
    QObject* parent_;

    /*!
     * \brief vertical layout box for storing all the widgets used
     */
    QVBoxLayout *layout_;

    /*!
     * \brief title label
     */
    QLabel *title_;

    /*!
     * \brief 10 labels in array, used for generating top-10 ranking list
     */
    QLabel *labels[10];

    /*!
     * \brief button connected with click signal to get back to start window
     */
    QPushButton *backBtn_;

};

}//StudentUI

#endif // HIGHSCOREWINDOW_HH
