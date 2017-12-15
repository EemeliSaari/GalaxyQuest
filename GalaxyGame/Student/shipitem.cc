#include "shipitem.hh"

namespace StudentUI
{

ShipItem::ShipItem(int x, int y)
    : x_(x), y_(y)
{
    setFlag(ItemIsSelectable, false);
}

QRectF ShipItem::boundingRect() const
{
    return QRectF(0,0,10,10);
}

QPainterPath ShipItem::shape() const
{
    QPainterPath path;
    path.moveTo(5,0);
    path.lineTo(3,2);
    path.lineTo(3,5);
    path.lineTo(2,6);
    path.lineTo(2,9);
    path.lineTo(5,7);
    path.lineTo(8,9);
    path.lineTo(8,6);
    path.lineTo(7,5);
    path.lineTo(7,2);
    path.lineTo(5,0);
    path.closeSubpath();

    return path;
}

void ShipItem::paint(QPainter *painter,
                     const QStyleOptionGraphicsItem *option,
                     QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QColor shipColor = QColor(127, 0, 255);

    painter->setBrush(shipColor);
    painter->setPen(Qt::white);

    painter->fillPath(shape(), QBrush(shipColor));
}

}//StudentUI
