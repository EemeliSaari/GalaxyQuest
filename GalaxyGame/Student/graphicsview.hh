#ifndef GRAPHICSVIEW_HH
#define GRAPHICSVIEW_HH

#include <QGraphicsView>
#include <QWheelEvent>

#include "galaxyview.hh"

namespace StudentUI
{

class GalaxyView;

/*!
 * \brief GraphicsView class to give more control
 *        over the GalaxyView
 */
class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:

    /*!
     * \brief Constructor
     * \param v GalaxyView view
     */
    GraphicsView(GalaxyView *v);

private:

    /*!
     * \brief GalaxyView
     */
    GalaxyView *view_;

protected:

    /*!
     * \brief Wheel event to notify GalaxyView about zooming
     * \param event
     */
    void wheelEvent(QWheelEvent *event) override;
};

} //StudentUI

#endif // GRAPHICSVIEW_HH
