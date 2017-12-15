#ifndef SHIPITEM_HH
#define SHIPITEM_HH

#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QRectF>

namespace StudentUI
{

/*!
 * \brief Ship QGraphicsItem to reprecent flying ships.
 */
class ShipItem : public QGraphicsItem
{
public:

    /*!
     * \brief Constructor
     * \param x coordinate
     * \param y coordinate
     */
    ShipItem(int x, int y);

    /*!
     * \brief Bounding box for the item.
     * \return
     */
    QRectF boundingRect() const override;

    /*!
     * \brief Shape of the painted object.
     * \return
     */
    QPainterPath shape() const override;

    /*!
     * \brief Paints the object in the scene.
     * \param QPainter painter
     * \param Scene specific options
     * \param QWidget
     */
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

private:

    /*!
     * \brief items local x-coordinate.
     */
    int x_;

    /*!
     * \brief items local y-coordinate.
     */
    int y_;
};

}
#endif // SHIPITEM_HH
