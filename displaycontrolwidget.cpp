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

    displaySelectorDial = new DisplaySelectorDial(this);
    displaySelectorDial->setAttribute(Qt::WA_TranslucentBackground, true);
    scene->addWidget(displaySelectorDial);
    displaySelectorDial->move(-50,-50);
/*
    displayControlDial->setMinimum(1);
    if(side == LEFT)
    {
        displayControlDial->setMaximum(2);
    }
    else if(side == RIGHT)
    {
        displayControlDial->setMaximum(3);
    }
    displayControlDial->setNotchesVisible(true);
*/
    displaySelectorDial->setStyleSheet("background-color: #27272B; color: #FFFFFF;");
    displaySelectorDial->setStyleSheet("qproperty-knobMargin: 5; qproperty-knobMargin: 5;");

    //QObject::connect(&displayControlDial, &QDial::sliderReleased,
    //                 this, &DisplayControlWidget::setValue);
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

void DisplayControlWidget::setValue()
{
    QPoint pos = displaySelectorDial->pos();
    qDebug() << pos.x() << pos.y();
}

