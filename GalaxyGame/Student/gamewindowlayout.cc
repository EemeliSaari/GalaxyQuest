#include "gamewindowlayout.hh"
#include <iostream>
namespace StudentUI
{

GameWindowLayout::GameWindowLayout(QWidget *parent, int marging, int spacing)
    : parent_(parent)
{
    setMargin(marging);
    setSpacing(spacing);

    frameList_ = new QList<FrameWrapper*>();
}

GameWindowLayout::GameWindowLayout(int spacing)
{
    setSpacing(spacing);
}

GameWindowLayout::~GameWindowLayout()
{
    QLayoutItem *I;
    while ((I = takeAt(0)))
    {
        delete I;
    }

    delete frameList_;
}

void GameWindowLayout::resetMe()
{
    QLayoutItem *I;
    while ((I = takeAt(0)))
    {
        delete I;
    }
}

void GameWindowLayout::addItem(QLayoutItem *item)
{
    add(item, East);
}

void GameWindowLayout::addWidget(QWidget *widget, GameWindowLayout::Position position)
{
    add(new QWidgetItem(widget), position);
}

void GameWindowLayout::setGeometry(const QRect &rect)
{
    FrameWrapper *center = 0;

    int eastWidth = 0;
    int eastHeight = 0;
    int northHeight = 0;
    int northWidth = 0;
    int southHeight = 0;
    int centerHeight = 0;
    int centerWidth = 0;

    QLayout::setGeometry(rect);

    int eastCounter = 0;
    for (int i = 0; i < frameList_->size(); ++i)
    {
        FrameWrapper *wrapper = frameList_->at(i);
        QLayoutItem *item = wrapper->item;
        Position position = wrapper->position;

        if (position == East)
        {
            item->setGeometry(QRect(rect.x(),
                                    eastHeight,
                                    item->sizeHint().width(),
                                    item->sizeHint().height()));

            eastWidth += item->geometry().width() + spacing();
            eastHeight += item->geometry().height() + spacing();

            ++eastCounter;
        }
    }

    centerWidth = rect.width() - eastWidth;
    int northCounter = 0;
    for(int i = 0; i < frameList_->size(); ++i)
    {
        FrameWrapper *wrapper = frameList_->at(i);
        QLayoutItem *item = wrapper->item;
        Position position = wrapper->position;

        if (position == North)
        {
            item->setGeometry(QRect(rect.x(),
                                    northHeight,
                                    centerWidth,
                                    item->sizeHint().height()));

            northHeight += item->geometry().height() + spacing();
            ++northCounter;
        }

        else if (position == South) {
            item->setGeometry(QRect(item->geometry().x(),
                                    item->geometry().y(),
                                    centerWidth,
                                    item->sizeHint().height()));

            southHeight += item->geometry().height() + spacing();

            item->setGeometry(QRect(rect.x(),
                              rect.y() + rect.height() - southHeight + spacing(),
                              item->geometry().width(),
                              item->geometry().height()));
        }
        else if (position == Center) {
            center = wrapper;
        }
    }

    centerHeight = rect.height() - southHeight - northHeight + spacing();

    eastHeight = rect.height() / eastCounter;
    int leftOverEast = rect.height() % eastCounter;

    northWidth = centerWidth / northCounter;
    int leftOverNorth = rect.width() % northCounter;

    int trueEast = 0;
    int trueNorth = 0;

    int eastCounter_ = 0;
    int northCounter_ = 0;

    for (int i = 0; i < frameList_->size(); ++i)
    {
        FrameWrapper *wrapper = frameList_->at(i);
        QLayoutItem *item = wrapper->item;
        Position position = wrapper->position;

        if (position == East)
        {
            ++eastCounter_;
            if(eastCounter_ == eastCounter)
            {
                item->setGeometry(QRect(centerWidth,
                                        trueEast + leftOverEast,
                                        eastWidth,
                                        eastHeight));
            }
            else
            {
                item->setGeometry(QRect(centerWidth,
                                        trueEast,
                                        eastWidth,
                                        eastHeight));

                trueEast += item->geometry().height() + spacing();
            }
        }
        else if (position == North)
        {
            ++ northCounter_;
            if(northCounter_ == northCounter)
            {
                item->setGeometry(QRect(trueNorth + leftOverNorth,
                                        rect.y(),
                                        northWidth,
                                        northHeight));
                trueNorth += item->geometry().width() +spacing();
            }
            else
            {
                item->setGeometry(QRect(trueNorth,
                                        rect.y(),
                                        northWidth,
                                        northHeight));
                trueNorth += item->geometry().width() +spacing();
            }
        }

    }

    if (center)
        center->item->setGeometry(QRect(0,
                                        northHeight,
                                        rect.width() - eastWidth,
                                        centerHeight));
}

int GameWindowLayout::count() const
{
    return frameList_->size();
}

QLayoutItem *GameWindowLayout::itemAt(int index) const
{
    FrameWrapper *wrapper = frameList_->value(index);
    if (wrapper)
        return wrapper->item;
    else
        return 0;
}

QLayoutItem *GameWindowLayout::takeAt(int index)
{
    if (index >= 0 && index < frameList_->size())
    {
        FrameWrapper *layoutStruct = frameList_->takeAt(index);
        return layoutStruct->item;
    }
    return 0;
}

Qt::Orientations GameWindowLayout::expandingDirections() const
{
    return Qt::Horizontal | Qt::Vertical;
}

QSize GameWindowLayout::minimumSize() const
{
    return calculateSize(MinimumSize);
}

QSize GameWindowLayout::sizeHint() const
{
    return calculateSize(SizeHint);
}

void GameWindowLayout::add(QLayoutItem *item, GameWindowLayout::Position Position)
{
    frameList_->append(new FrameWrapper(item, Position));
}

QSize GameWindowLayout::calculateSize(GameWindowLayout::SizeType sizeType) const
{
    QSize totalSize;

    for (int i = 0; i < frameList_->size(); ++i)
    {
        FrameWrapper *wrapper = frameList_->at(i);
        Position position = wrapper->position;
        QSize itemSize;

        if (sizeType == MinimumSize)
        {
            itemSize = wrapper->item->minimumSize();
        }
        else // (sizeType == SizeHint)
        {
            itemSize = wrapper->item->sizeHint();
        }
        if (position == North || position == South || position == Center)
        {
            totalSize.rheight() += itemSize.height();
        }
        if (position == East || position == Center)
            totalSize.rwidth() += itemSize.width();
    }
    return totalSize;
}

}
