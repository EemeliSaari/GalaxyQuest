#ifndef PLAYERBUYDIALOG_HH
#define PLAYERBUYDIALOG_HH

#include <QDialog>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QFrame>

namespace StudentUI
{

/*!
 * \brief Dialog that allows player to buy ships into the system.
 */
class PlayerBuyDialog : public QDialog
{
    Q_OBJECT
public:

    /*!
     * \brief Standard price.
     */
    static const int SHIP_PRICE;

    /*!
     * \brief Constructor
     * \param location name
     * \param playerCredits amount
     * \param parent widget.
     */
    PlayerBuyDialog(std::string location,
                    int playerCredits,
                    QWidget *parent = 0);

public slots:

    /*!
     * \brief overrided accept slot.
     */
    void accept() override;

signals:

    /*!
     * \brief Signal to inform abou
     * \param amount of ships to be purchased
     * \param total price.
     */
    void completePurchase(int amount, int price);

private:

    /*!
     * \brief Helper functio to make label
     * \param name of the string
     * \return
     */
    QFrame *makeLabel(QString name = "");

    /*!
     * \brief maximum value of spinbox
     */
    int value_;

    /*!
     * \brief Accept button
     */
    QPushButton *acceptButton_;

    /*!
     * \brief Cancel button
     */
    QPushButton *cancelButton_;

    /*!
     * \brief Sping box.
     */
    QSpinBox *spinBox_;
};

}
#endif // PLAYERBUYDIALOG_HH
