#ifndef CONTROLNODE_H
#define CONTROLNODE_H

//#include "mainwindow.h"

#include <QGraphicsItem>
#include <QWidget>
#include <QList>

class ControlWidget;

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class ControlNode : public QGraphicsItem
{
public:
    ControlNode(ControlWidget *controlWidget);

    enum { Type = UserType + 1 };
    int type() const Q_DECL_OVERRIDE { return Type; }

    void updateNodePosition();
    bool advance();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QList<QPointF *> anchorList;
    QPointF newPos, oldPos, dPos;
    //int i = 0;

    QPointF anchorNode1, anchorNode2, anchorNode3, anchorNode4, anchorNode5,
            anchorNode6, anchorNode7, anchorNode8, anchorNode9;

    bool mousePressed;

    ControlWidget *control;
};

#endif // CONTROLNODE_H
