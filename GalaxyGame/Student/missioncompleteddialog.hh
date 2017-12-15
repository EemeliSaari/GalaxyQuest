#ifndef MISSIONCOMPLETEDDIALOG_HH
#define MISSIONCOMPLETEDDIALOG_HH

#include <QWidget>
#include <QDialog>
#include <QFrame>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

#include "rescuemission.hh"

namespace StudentUI
{

/*!
 * \brief Dialog window shown when the mission ends, either completed or failed
 */
class MissionCompletedDialog : public QDialog
{
    Q_OBJECT
public:

    /*!
     * \brief MissionCompletedDialog constructor
     * \param boolean value, completed or not(failed)
     * \param parent
     */
    MissionCompletedDialog(bool completed,
                           QWidget *parent = 0);

private:

    /*!
     * \brief continue buttons exit the dialog
     */
    QPushButton *continueBtn_;

    /*!
     * \brief frame for label
     */
    QFrame *labelFrame_;
};

}//Student

#endif // MISSIONCOMPLETEDDIALOG_HH
