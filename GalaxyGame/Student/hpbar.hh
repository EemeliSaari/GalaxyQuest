#ifndef HPBAR_H
#define HPBAR_H

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QProgressBar>

namespace StudentUI
{

/*!
 * \brief HpBar frame that gives user information
 *        about their hp and uncertainty
 */
class HpBar : public QFrame
{
    Q_OBJECT
public:

    /*!
     * \brief Constructor
     * \param parent widget
     * \param maxHp
     * \param maxUncertainty
     */
    HpBar(QWidget *parent, int maxHp, int maxUncertainty);

    /*!
     * \brief deconstructor
     */
    ~HpBar();

    /*!
     * \brief Reset the values to default
     */
    void reset();

public slots:

    /*!
     * \brief Updates the HP progressbar
     * \param newValue
     */
    void updateHp(int newValue);

    /*!
     * \brief Updates uncertainty progressbar
     * \param newValue
     */
    void updateUncertainty(int newValue);

private:

    /*!
     * \brief Layout for the frame
     */
    QGridLayout *layout_;

    /*!
     * \brief Hp progressbar
     */
    QProgressBar *hp_;

    /*!
     * \brief uncertainty progressbar
     */
    QProgressBar *uncertainty_;

    /*!
     * \brief Text for the Hp
     */
    QLabel *hpText_;

    /*!
     * \brief Text for the uncertainty
     */
    QLabel *uncertaintyText_;

    /*!
     * \brief default Hp amount
     */
    int defaultHp_;

    /*!
     * \brief default uncertainty amount
     */
    int defaultUncertainty_;
};

} //StudentUI
#endif // HPBAR_H
