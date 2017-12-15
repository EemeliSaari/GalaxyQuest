#include <QtGlobal>
#include <QtMath>

#include "galaxyview.hh"
#include <iostream>
#include <QHBoxLayout>

namespace StudentUI
{

GalaxyView::GalaxyView(QWidget *parent)
    : parent_(parent)
{
    setFrameStyle(Sunken | StyledPanel);

    graphicsView_ = new GraphicsView(this);

    graphicsView_->setRenderHint(QPainter::Antialiasing, true);
    graphicsView_->setDragMode(QGraphicsView::RubberBandDrag);
    graphicsView_->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    graphicsView_->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    graphicsView_->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    graphicsView_->setContextMenuPolicy(Qt::ActionsContextMenu);

    zoomMin_ = 250;
    zoomMax_ = 350;
    zoomDefault_ = 325;
    zoomValue_ = zoomDefault_;

    graphicsView_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff );
    graphicsView_->setDragMode(QGraphicsView::NoDrag);

    QHBoxLayout *layout = new QHBoxLayout(this);

    layout->addWidget(graphicsView_);
    setLayout(layout);
    setupMatrix();
}

QGraphicsView *GalaxyView::view() const
{
    return static_cast<QGraphicsView *>(graphicsView_);
}

void GalaxyView::zoomIn(int level)
{
    if(zoomValue_ < zoomMax_)
        zoomValue_ += level;
        setupMatrix();
}

void GalaxyView::zoomOut(int level)
{
    if (zoomValue_ > zoomMin_ + level)
        zoomValue_ -= level;
        setupMatrix();
}

void GalaxyView::setupMatrix()
{
    qreal scale = qPow(qreal(2), (zoomValue_ - 250)/qreal(50)); //arbitrary values

    QMatrix matrix;
    matrix.scale(scale,scale);

    graphicsView_->setMatrix(matrix);
}

}
