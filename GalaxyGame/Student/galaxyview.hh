#ifndef GALAXYVIEW_HH
#define GALAXYVIEW_HH

#include <QFrame>
#include <QGraphicsView>

#include "graphicsview.hh"

namespace StudentUI
{
class GraphicsView;

/*!
 * \brief GalaxyView component giving the view of the QGraphicsScene.
 */
class GalaxyView : public QFrame
{
    Q_OBJECT
public:

    /*!
     * \brief GalaxyView constructor
     * \param parent
     */
    explicit GalaxyView(QWidget *parent = 0);

    /*!
     * \brief Gets the QGraphicsView.
     * \return view
     */
    QGraphicsView *view() const;

public slots:

    /*!
     * \brief Zooming in events slot.
     * \param new value
     */
    void zoomIn(int level = 1);

    /*!
     * \brief Zooming out events slot.
     * \param new value.
     */
    void zoomOut(int level = 1);

private slots:

    /*!
     * \brief Sets the scale of the scene accordingly
     */
    void setupMatrix();

private:

    /*!
     * \brief Parent that created the object.
     */
    QWidget *parent_;

    /*!
     * \brief View component
     */
    GraphicsView *graphicsView_;

    /*!
     * \brief Current zoom value.
     */
    unsigned zoomValue_;

    /*!
     * \brief Default value for zoom.
     */
    unsigned zoomDefault_;

    /*!
     * \brief Minimum zoom value.
     */
    unsigned zoomMin_;

    /*!
     * \brief Maximum zoom value.
     */
    unsigned zoomMax_;
};

}//StudentUI
#endif // GALAXYVIEW_HH
