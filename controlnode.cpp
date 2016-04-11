#include "controlnode.h"
#include "controlwidget.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QtMath>

#include <QDebug>

ControlNode::ControlNode(ControlWidget *controlWidget) : control(controlWidget)
{
    QGraphicsItem::setFlag(ItemIsMovable);
    QGraphicsItem::setFlag(ItemSendsGeometryChanges);
    QGraphicsItem::setCacheMode(DeviceCoordinateCache);
    QGraphicsItem::setZValue(-1);

    mousePressed = false;
    newPos.setX(0); newPos.setY(0);
    oldPos.setX(0); oldPos.setY(0);
    dPos.setX(0); dPos.setY(0);
}

void ControlNode::calculateForces()
{
    // Test if the user is moving the controlNode.
    if (!scene() || scene()->mouseGrabberItem() == this) {
        newPos = pos();
        return;
    }

    // Calculate the forces of the mass-spring-dampner system
    qreal xvel = 0;
    qreal yvel = 0;

    qreal Fx = 0;
    qreal Fy = 0;

    qreal k = 0.8, c = 0.4, m = 0.5, dt = 0.04;

    xvel = dPos.x()*dt;
    yvel = dPos.y()*dt;

    Fx = (-1)*pos().x()*k - c*(dPos.x()/dt);
    Fy = (-1)*pos().y()*k - c*(dPos.y()/dt);

    xvel += (Fx/m)*dt;
    yvel += (Fy/m)*dt;

    if (qAbs(Fx) < 0.1 && qAbs(Fy) < 0.1)
        xvel = yvel = 0;

    QRectF sceneRect = scene()->sceneRect();
    oldPos = newPos;
    newPos = pos() + QPointF(xvel, yvel);
    newPos.setX(qMin(qMax(newPos.x(), sceneRect.left() + 10), sceneRect.right() - 10));
    newPos.setY(qMin(qMax(newPos.y(), sceneRect.top() + 10), sceneRect.bottom() - 10));
    dPos = newPos - oldPos;
}

bool ControlNode::advance()
{
    if (newPos == pos())
        return false;

    setPos(newPos);
    return true;
}

QRectF ControlNode::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
}

QPainterPath ControlNode::shape() const
{
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}

void ControlNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7, -7, 20, 20);

    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, QColor(Qt::yellow).light(120));
        gradient.setColorAt(0, QColor(Qt::darkYellow).light(120));
    } else {
        gradient.setColorAt(0, Qt::yellow);
        gradient.setColorAt(1, Qt::darkYellow);
    }
    painter->setBrush(gradient);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);

    qDebug() << "PAINTING";
}

QVariant ControlNode::itemChange(GraphicsItemChange change, const QVariant &value)
{
    //qDebug() << "CHANGING" << i++;
    //Add

    switch (change) {
      case ItemPositionHasChanged:
        control->itemMoved();
        break;
      default:
        break;
    };
    return QGraphicsItem::itemChange(change, value);
}

void ControlNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    qDebug() << "MOVING";
    mousePressed = true;
    QGraphicsItem::mousePressEvent(event);
}

void ControlNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    mousePressed = false;
    QGraphicsItem::mouseReleaseEvent(event);
    control->itemMoved();
}


