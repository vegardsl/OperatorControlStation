#include "offstatusdisplay.h"

#include <QGraphicsLineItem>

OffStatusDisplay::OffStatusDisplay(QWidget *parent) : QGraphicsView(parent)
{
    qreal upperLeftX = -320, upperLeftY = -240,
            lowerLeftX = -320, lowerLeftY = 240,
            upperRightX = 320, upperRightY = -240,
            lowerRightX = 320, lowerRightY = 240;

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    scene->setSceneRect(-320, -240, 640, 480);

    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(640, 480);
    setMaximumSize(640, 480);

    scene->setBackgroundBrush(Qt::black);

    QPen linePen;
    linePen.setStyle(Qt::DashLine);
    linePen.setWidth(3);
    linePen.setBrush(Qt::red);

    QGraphicsLineItem* line1 = new QGraphicsLineItem(upperLeftX, upperLeftY,
                                                     lowerRightX, lowerRightY);
    QGraphicsLineItem* line2 = new QGraphicsLineItem(lowerLeftX, lowerLeftY,
                                                     upperRightX, upperRightY);
    line1->setPen(linePen);
    line2->setPen(linePen);

    scene->addItem(line1);
    scene->addItem(line2);
}
