#include "graphicsview.hh"

namespace StudentUI
{

GraphicsView::GraphicsView(StudentUI::GalaxyView *v)
    : QGraphicsView(), view_(v)
{
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier)
    {
        if (event->delta() > 0)
            view_->zoomIn(6);
        else
            view_->zoomOut(6);
        event->accept();
    }

    else
    {
        QGraphicsView::wheelEvent(event);
    }
}

}//StudentUI
