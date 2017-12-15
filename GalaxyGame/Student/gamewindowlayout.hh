#ifndef GAMEWINDOWLAYOUT_HH
#define GAMEWINDOWLAYOUT_HH

#include <QLayout>
#include <QRect>
#include <QWidget>

namespace StudentUI
{

/*!
 * \brief Custom QLayout class for GameWindow.
 *        This layout has been made using the Qt
 *        example: borderlayout but is heavily
 *        modified to suit the needs of GameWindow.
 */
class GameWindowLayout : public QLayout
{
public:

    /*!
     * \brief Positions in the layout
     */
    enum Position { North, South, East, Center };

    /*!
     * \brief explicit Constructor
     * \param QWidget parent
     * \param marging, default 0
     * \param spacing, default 0
     */
    explicit GameWindowLayout(QWidget *parent,
                              int marging = 0,
                              int spacing = 0);

    /*!
     * \brief Constructor
     * \param spacing, default 0
     */
    GameWindowLayout(int spacing = 0);

    /*!
     * Deconstructor for the class
     */
    ~GameWindowLayout();

    /*!
     * \brief Deletes every item in the layout
     */
    void resetMe();

    /*!
     * \brief Adds an item to the list
     * \param QLayoutItem item pointer
     */
    void addItem(QLayoutItem *item) override;

    /*!
     * \brief Add widget to the list
     * \param QWidget widget pointer
     * \param position of the item in the layout
     */
    void addWidget(QWidget *widget, Position position);

    /*!
     * \brief Sets the geometry of the layout and is the bread
     *        and butter of the custom layout
     * \param rect sets the layout
     */
    void setGeometry(const QRect &rect) override;

    /*!
     * \brief Counts the number of items in the layout
     * \return items count
     */
    int count() const override;

    /*!
     * \brief Item at index position in the layout
     * \param item index in the layout
     * \return QLayoutItem if item was found, 0 otherwise
     */
    QLayoutItem *itemAt(int index) const override;

    /*!
     * \brief Return the item from the struct
     * \param item index in the layout
     * \return QLayoutItem if item was found, 0 otherwise
     */
    QLayoutItem *takeAt(int index) override;

    /*!
     * \brief Tells layout which directions to expand to
     * \return Orientations
     */
    Qt::Orientations expandingDirections() const override;

    /*!
     * \brief Minimum size of the layout
     * \return QSize of the size
     */
    QSize minimumSize() const override;

    /*!
     * \brief Recommended size for the layout
     * \return QSize of the size
     */
    QSize sizeHint() const override;

    /*!
     * \brief Add item to the layout
     * \param QLayoutItem item
     * \param Position of the item
     */
    void add(QLayoutItem *item, Position Position);

private:

    /*!
     * \brief FrameWrapper to handle and manage items and widgets
     *        in the layout
     */
    struct FrameWrapper
    {

        /*!
         * \brief FrameWrapper
         * \param i item
         * \param p position
         */
        FrameWrapper(QLayoutItem *i, Position p)
        {
            item = i;
            position = p;
        }

        /*!
         * \brief item
         */
        QLayoutItem *item;

        /*!
         * \brief position
         */
        Position position;
    };

    /*!
     * \brief Minimum size and recommended size for the layout
     */
    enum SizeType { MinimumSize, SizeHint };

    /*!
     * \brief Calculates the size of the layout
     * \param Size type
     * \return QSize of the size
     */
    QSize calculateSize(SizeType sizeType) const;

    /*!
     * \brief Parent widget
     */
    QWidget parent_;

    /*!
     * \brief List of the items in the layout
     */
    QList<FrameWrapper*> *frameList_;
};

}

#endif // GAMEWINDOWLAYOUT_HH
