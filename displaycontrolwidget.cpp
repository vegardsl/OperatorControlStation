#include "displaycontrolwidget.h"

#include <QDebug>

DisplayControlWidget::DisplayControlWidget(QWidget *parent, int _side) : QGraphicsView(parent)
{
    side = _side;

    qDebug() << "Side: " + QString::number(side);

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-320, -50, 640, 100);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(640,100);
    setMaximumSize(640,100);

    scene->setBackgroundBrush(Qt::gray);

    displayControlDial = new QDial;

    scene->addWidget(displayControlDial);
    displayControlDial->move(-50,-50);
}

void DisplayControlWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    QRectF sceneRect = this->sceneRect();

    QRectF offTextRect(-100, 30,
                    50, 30);
    QRectF camTextRect(-100, -50,
                    50, 30);
    QRectF statusTextRect(-100, -50,
                    50, 30);
    QRectF mapTextRect(50, -50,
                    50, 30);
    QString offLabel("OFF"), mapLabel("MAP"),
            camLabel("CAM"), statusLabel("STATUS");

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(14);
    painter->setFont(font);
    painter->setPen(Qt::black);
    painter->drawText(offTextRect, offLabel);

    if(side == LEFT)
    {
        painter->drawText(camTextRect, camLabel);
    }
    else if(side == RIGHT)
    {
        painter->drawText(mapTextRect, mapLabel);

        painter->drawText(statusTextRect, statusLabel);
    }
}

