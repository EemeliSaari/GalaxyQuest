#include <algorithm>
#include <QStyle>
#include <QRadialGradient>
#include <iostream>
#include <QString>
#include <QMenu>

#include "solarsystemitem.hh"
#include "objectnotfoundexception.hh"
#include "gameexception.hh"

namespace StudentUI
{

SolarSystemItem::SolarSystemItem(int x,
                                 int y,
                                 std::string name)
    : x_(x), y_(y), name_(name), ships_(0), troubleShips_(0), salvageable_(0)
{
    setFlag(ItemIsSelectable, true);

    inPlayerRange_ = false;
    hostingPlayer_ = false;
    missionSystem_ = false;
    validActions_ = true;
    validMove_ = true;
    canRepair_ = false;
}


QRectF SolarSystemItem::boundingRect() const
{
    return QRectF(0,0,20,20);
}

QPainterPath SolarSystemItem::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void SolarSystemItem::paint(QPainter *painter,
                               const QStyleOptionGraphicsItem *option,
                               QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QColor fontColor = Qt::red;

    const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());

    // Draw selected
    if(this->isSelected())
    {
        painter->setPen(QPen(Qt::darkGreen, 2));

        auto selectedArea = boundingRect();
        selectedArea.adjust(-4,-4,4,4);

        painter->drawEllipse(selectedArea);
    }

    QRadialGradient grad(QPoint(10,10),10);
    // Draw the system cyan if player is there.
    if(hostingPlayer_)
    {
        QColor color1 = Qt::black;
        QColor color2 = Qt::cyan;

        grad.setColorAt(0.0, color2);
        grad.setColorAt(0.25, color2);
        grad.setColorAt(1.0, color1);
    }
    // red if it's a missioning system
    else if(missionSystem_)
    {
        QColor color1 = Qt::black;
        QColor color2 = Qt::red;

        grad.setColorAt(0.0, color2);
        grad.setColorAt(0.25, color2);
        grad.setColorAt(1.0, color1);
    }
    // else black and white
    else
    {
        QColor color1 = Qt::black;
        QColor color2 = Qt::white;

        grad.setColorAt(0.0, color2);
        grad.setColorAt(0.25, color2);
        grad.setColorAt(1.0, color1);
    }
    painter->fillPath(shape(),grad);

    // Draw the systems in player range
    if(inPlayerRange_)
    {
        painter->setPen(QPen(Qt::darkCyan, 2));

        auto playerArea = boundingRect();
        playerArea.adjust(-7,-7,7,7);

        painter->drawEllipse(playerArea);
    }
    int r = 10;

    // Draw hosted ships
    if(!(ships_.empty()))
    {
        painter->setPen(QPen(QColor(127, 0, 255, 137), 1));

        //for(auto it = hostedShips_.begin(); it != hostedShips_.end(); ++it)
        for(auto it = ships_.begin(); it != ships_.end(); ++it)
        {
            auto shipArea = boundingRect();
            shipArea.adjust(-r,-r,r,r);

            painter->drawEllipse(shipArea);
            r += 3;
        }
    }

    // Draw ships in trouble
    if(!(troubleShips_.empty()))
    {
        painter->setPen(QPen(QColor(255, 0, 0, 255), 1));
        for(auto it = troubleShips_.begin(); it != troubleShips_.end(); ++it)
        {
            auto troubleArea = boundingRect();
            troubleArea.adjust(-r,-r,r,r);

            painter->drawEllipse(troubleArea);
            r += 3;
        }
    }

    // Draw amount of salvaged ships
    if(!(salvageable_.empty()))
    {
        painter->setPen(QPen(QColor(255, 255, 0, 155), 1));
        for(auto it = salvageable_.begin(); it != salvageable_.end(); ++it)
        {
            auto salvageArea = boundingRect();
            salvageArea.adjust(-r,-r,r,r);

            painter->drawEllipse(salvageArea);
            r += 3;
        }
    }

    // Draw the repair icon
    if(canRepair_ && !missionSystem_)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(7,9,6,2);
        path.addRect(9,7,2,6);
        painter->fillPath(path,QBrush(Qt::red));
    }
    else if(canRepair_ && missionSystem_)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(7,9,6,2);
        path.addRect(9,7,2,6);
        painter->fillPath(path,QBrush(Qt::white));
    }

    // Draw text if zoomed close enough.
    if (lod >= 2)
    {
        QString name = QString::fromStdString(name_);

        QFont font("Helvetica", 15);
        font.setStyleStrategy(QFont::ForceOutline);
        painter->setPen(fontColor);
        painter->setFont(font);
        painter->save();
        painter->scale(0.2, 0.2);
        painter->drawText(50,0, name);
        painter->restore();
    }
}

void SolarSystemItem::shipLeft(std::shared_ptr<Common::Ship> ship)
{
    auto start = ships_.begin();
    auto end = ships_.end();

    auto it = std::find(start,end,ship);

    if(it != end)
    {
        ships_.erase(it);
    }
    else
    {
        throw Common::ObjectNotFoundException();
    }
    update();
}

void SolarSystemItem::shipEntered(std::shared_ptr<Common::Ship> ship)
{
    if(!(ships_.empty()))
    {
        auto end = ships_.end();
        auto start = ships_.begin();

        auto it = std::find(start,end,ship);

        if(it == end)
        {
            ships_.push_back(ship);
        }
        else
        {
            throw Common::GameException();
        }
    }
    else
    {
        ships_.push_back(ship);
    }
    update();
}

void SolarSystemItem::shipInTrouble(std::shared_ptr<Common::Ship> ship)
{
    if(!(troubleShips_.empty()))
    {
        auto end = troubleShips_.end();
        auto start = troubleShips_.begin();

        auto it = std::find(start,end,ship);

        if(it == end)
        {
            troubleShips_.push_back(ship);
        }
        else
        {
            throw Common::GameException();
        }
    }
    else
    {
        troubleShips_.push_back(ship);
    }
    update();
}

void SolarSystemItem::shipNotInTrouble(std::shared_ptr<Common::Ship> ship)
{
    auto start = troubleShips_.begin();
    auto end = troubleShips_.end();

    auto it = std::find(start,end,ship);

    if(troubleShips_.size() > 1)
    {

        if(it != end)
        {
            troubleShips_.erase(it);
        }
        else
        {
            throw Common::ObjectNotFoundException();
        }
    }
    else
    {
        troubleShips_.erase(it);
    }
    update();
}

void SolarSystemItem::addSalvage(std::shared_ptr<Common::Ship> ship)
{
    if(!(salvageable_.empty()))
    {
        auto end = salvageable_.end();
        auto start = salvageable_.begin();

        auto it = std::find(start,end,ship);

        if(it == end)
        {
            salvageable_.push_back(ship);
        }
        else
        {
            throw Common::GameException();
        }
    }
    else
    {
        salvageable_.push_back(ship);
    }
    update();
}

void SolarSystemItem::removeSalvage(std::shared_ptr<Common::Ship> ship)
{
    auto start = salvageable_.begin();
    auto end = salvageable_.end();

    auto it = std::find(start,end,ship);

    if(salvageable_.size() > 1)
    {

        if(it != end)
        {
            salvageable_.erase(it);
        }
        else
        {
            throw Common::ObjectNotFoundException();
        }
    }
    else
    {
        salvageable_.erase(it);
    }
    update();
}

void SolarSystemItem::setHostingPlayer(bool val)
{
    if(val)
        setRange(false);

    hostingPlayer_ = val;
    update();
}

void SolarSystemItem::setRange(bool val)
{
    inPlayerRange_ = val;
    update();
}


void SolarSystemItem::setMission(bool val)
{
    missionSystem_ = val;
    update();
}

void SolarSystemItem::setActions(bool val)
{
    validActions_ = val;
    update();
}

void SolarSystemItem::setMoveable(bool val)
{
    validMove_ = val;
    update();
}

void SolarSystemItem::setRepair(bool val)
{
    canRepair_ = val;
    update();
}

void SolarSystemItem::openMenu(QPoint loc)
{
    QMenu menu;

    if(hostingPlayer_ && !(troubleShips_.empty()) && validActions_)
    {
        QSignalMapper *mapper_ = new QSignalMapper(this);
        int i = 0;
        for(auto it = troubleShips_.begin(); it != troubleShips_.end(); ++it)
        {
            QString text = QString("Save: %1").arg(QString::fromStdString((*it)->getName()));
            QAction *saveAction = menu.addAction(text);

            connect(saveAction, SIGNAL(triggered(bool)), mapper_, SLOT(map()));

            mapper_->setMapping(saveAction, i);

            ++i;
        }
        connect(mapper_, SIGNAL(mapped(int)), this, SLOT(savingShip(int)));
    }
    else if(inPlayerRange_ && validMove_ && !hostingPlayer_ && validActions_)
    {
        QString text = QString("Move to %1").arg(QString::fromStdString(name_));
        QAction *moveAction = menu.addAction(text);

        connect(moveAction, SIGNAL(triggered(bool)), this, SLOT(playerEntering()));
    }

    if(hostingPlayer_ && missionSystem_ && validActions_)
    {
        QString text = QString("Rescue people of %1").arg(QString::fromStdString(name_));
        QAction *rescueAction = menu.addAction(text);

        connect(rescueAction, SIGNAL(triggered(bool)), this, SLOT(doMission()));
    }
    if(hostingPlayer_ && !(salvageable_.empty()) && validActions_)
    {
        QSignalMapper *mapper_ = new QSignalMapper(this);
        int i = 0;
        for(auto it = salvageable_.begin(); it != salvageable_.end(); ++it)
        {
            QString text = QString("Salvage: %1").arg(QString::fromStdString((*it)->getName()));
            QAction *salvageAction = menu.addAction(text);

            connect(salvageAction, SIGNAL(triggered(bool)), mapper_, SLOT(map()));

            mapper_->setMapping(salvageAction, i);

            ++i;
        }
        connect(mapper_, SIGNAL(mapped(int)), this, SLOT(salvage(int)));
    }

    if(hostingPlayer_ && canRepair_ && validActions_)
    {
        QAction *buyAction = menu.addAction("Buy cargo ship");
        QAction *repairAction = menu.addAction("Repair");

        connect(buyAction, SIGNAL(triggered(bool)), this, SLOT(playerBuying()));
        connect(repairAction, SIGNAL(triggered(bool)), this, SLOT(playerRepair()));
    }
    menu.exec(loc);
}

void SolarSystemItem::playerEntering()
{
    emit playerMovingHere(name_);
    update();
}

void SolarSystemItem::savingShip(int index)
{   
    emit savedShip(troubleShips_[index]);

    update();
}

void SolarSystemItem::doMission()
{
    emit tryCompleteMission(name_);
}

void SolarSystemItem::salvage(int index)
{
    emit salvagedShip(troubleShips_[index]);
    update();
}

void SolarSystemItem::playerRepair()
{
    emit initRepairing(name_);
}

void SolarSystemItem::playerBuying()
{
    emit initBuying(name_);
}

void SolarSystemItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        if(!(this->isSelected()))
        {
            emit imSelected(name_);
        }
        QGraphicsItem::mousePressEvent(event);
        event->accept();
    }
    else if(event->button()==Qt::RightButton && validActions_)
    {
        openMenu(event->screenPos());
    }

}

}//StudentUI
