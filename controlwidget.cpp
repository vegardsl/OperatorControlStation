#include "controlwidget.h"
#include "controlnode.h"

#include <math.h>

#include <QGraphicsItem>

#include <QDebug>

ControlWidget::ControlWidget(QWidget *parent) : QGraphicsView(parent), timerId(0)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-150, -200, 300, 400);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(300,400);
    setMaximumSize(300,400);

    scene->setBackgroundBrush(Qt::black);

    controlNode = new ControlNode(this);


    QGraphicsEllipseItem* deadZoneIndicator = new QGraphicsEllipseItem(-20,-20,40,40);
    deadZoneIndicator->setBrush(Qt::green);
    deadZoneIndicator->setOpacity(0.3);
    deadZoneIndicator->setZValue(-2);

    QGraphicsRectItem* horizontalDeadZoneIndicator = new QGraphicsRectItem(-150,-20,300,40);
    horizontalDeadZoneIndicator->setBrush(Qt::green);
    horizontalDeadZoneIndicator->setOpacity(0.2);
    horizontalDeadZoneIndicator->setZValue(-3);

    scene->addItem(controlNode);
    scene->addItem(deadZoneIndicator);
    scene->addItem(horizontalDeadZoneIndicator);
    controlNode->setPos(0,0);

}

void ControlWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);

    //QPointF pos = controlNode->pos();
    //qDebug() << "XPos: " << pos.x() << " YPos: " << pos.y();
    controlInputToCommandMessage();
}



void ControlWidget::timerEvent(QTimerEvent *event)
{
  Q_UNUSED(event);

  controlNode->updateNodePosition();

  bool itemsMoved = false;
  if (controlNode->advance())
  {
    itemsMoved = true;
  }

  if (!itemsMoved) {
    killTimer(timerId);
    timerId = 0;
  }
}

void ControlWidget::controlInputToCommandMessage()
{
    QPointF pos = controlNode->pos();
    qDebug() << "XPos: " << pos.x() << " YPos: " << pos.y();
    qreal linearCommand = 0, angularCommand = 0;
    if( abs(pos.y()) > 20 )
    {
        if(pos.y() < 0)
        {
            linearCommand = ((-1)*pos.y() - 20)/100;
        }
        else
        {
            linearCommand = ((-1)*pos.y() + 20)/100;
        }

    }
    if(abs(pos.x()) > 20 )
    {
        if(pos.x() < 0)
        {
            angularCommand = ((-1)*pos.x() - 20)/100;
        }
        else
        {
            angularCommand = ((-1)*pos.x() + 20)/100;
        }
    }
    emit updateCommandTransmitter(linearCommand, angularCommand);
    qDebug() << "linearCommand: " << linearCommand << " angularCommand: " << angularCommand;
}
