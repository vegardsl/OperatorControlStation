#ifndef DISPLAYCONTROLWIDGET_H
#define DISPLAYCONTROLWIDGET_H

#include <QGraphicsView>
#include <QDial>

class DisplayControlWidget : public QGraphicsView
{
public:
    DisplayControlWidget(QWidget *parent, int _side);

private:
    QDial *displayControlDial;

    int side;

    const int LEFT = 0;
    const int RIGHT = 1;

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;
};

#endif // DISPLAYCONTROLWIDGET_H
