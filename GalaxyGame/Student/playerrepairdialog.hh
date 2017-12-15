#ifndef PLAYERREPAIRDIALOG_HH
#define PLAYERREPAIRDIALOG_HH

#include <QDialog>
#include <QFrame>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>

namespace StudentUI
{
/*!
 * \brief Dialog that allows player to repair their ship.
 */
class PlayerRepairDialog : public QDialog
{
    Q_OBJECT
public:

    /*!
     * \brief Constructor
     * \param Service location name
     * \param price of service
     * \param maximum amount that can be repaired
     * \param QWidget parent
     */
    PlayerRepairDialog(std::string serviceLocation,
                       int price,
                       int maximum,
                       QWidget *parent = nullptr);

public slots:

    /*!
     * \brief Overrided accept slot, emits acceptRepair signal
     */
    void accept() override;

signals:

    /*!
     * \brief Informs about the accepted repair event
     * \param value ofhow many hitspoints repaired
     * \param price for the transaction
     */
    void acceptedRepair(int value, int price);

private:

    /*!
     * \brief Helper function to generate QFrame with string labels
     * \param name of the system
     * \param price of the action
     * \return QFrame
     */
    QFrame *makeLabel(QString name = "", QString price = "");

    /*!
     * \brief maximum available value
     */
    int value_;

    /*!
     * \brief price of the repair
     */
    int price_;

    /*!
     * \brief Accept button
     */
    QPushButton *acceptButton_;

    /*!
     * \brief Cancel button
     */
    QPushButton *cancelButton_;

    /*!
     * \brief Spin box
     */
    QSpinBox *spinBox_;
};

} //StudentUI
#endif // PLAYERREPAIRDIALOG_HH
