#ifndef MISSIONDIALOG_HH
#define MISSIONDIALOG_HH

#include <QDialog>
#include <QFrame>
#include <QPushButton>

#include "rescuemission.hh"

namespace StudentUI
{

/*!
 * \brief Mission dialog to display mission objective.
 */
class MissionDialog : public QDialog
{
    Q_OBJECT
public:

    /*!
     * \brief Constructor for dialog
     * \param rng value
     * \param mission type
     * \param location text
     * \param playername text
     */
    MissionDialog(double rng,
                  Student::RescueMission::MISSION_TYPE type,
                  std::string location,
                  QString playerName,
                  unsigned time,
                  QWidget *parent = 0);

private:

    /*!
     * \brief OK button to close dialog.
     */
    QPushButton *okButton_;

    /*!
     * \brief Frame containing the text.
     */
    QFrame *labelFrame_;
};

}
#endif // MISSIONDIALOG_HH
