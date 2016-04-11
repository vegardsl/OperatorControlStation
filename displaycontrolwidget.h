#ifndef DISPLAYCONTROLWIDGET_H
#define DISPLAYCONTROLWIDGET_H

#include <QGraphicsView>
#include <QDial>

#include "displayselectordial.h"

class DisplayControlWidget : public QGraphicsView
{
    Q_OBJECT
public:
    DisplayControlWidget(QWidget *parent, int _side);

private:
    DisplaySelectorDial *displaySelectorDial;

    int side;

    const int LEFT = 0;
    const int RIGHT = 1;

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;

public slots:
    void setValue();
};

#endif // DISPLAYCONTROLWIDGET_H
