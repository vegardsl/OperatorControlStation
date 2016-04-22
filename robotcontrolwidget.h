#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QGraphicsView>

class ControlNode;

class RobotControlWidget : public QGraphicsView
{
    Q_OBJECT
public:
    RobotControlWidget(QWidget *parent = 0);

    void itemMoved();

protected:
    void timerEvent(QTimerEvent *event);

private:
    int timerId;
    ControlNode *controlNode;

    void controlInputToCommandMessage();

signals:
    void updateCommandTransmitter(qreal linearCommand, qreal angularCommand);
};

#endif // CONTROLWIDGET_H
