#ifndef DISPLAYSELECTORDIAL_H
#define DISPLAYSELECTORDIAL_H

#include <QDial>

class DisplaySelectorDial : public QDial
{
    Q_OBJECT
    Q_PROPERTY(double knobRadius READ getKnobRadius WRITE setKnobRadius)
    Q_PROPERTY(double knobMargin READ getKnobMargin WRITE setKnobMargin)

public:
    DisplaySelectorDial(QWidget *parent = 0,
                        double knobRadius = 5,
                        double knobMargin = 5);

    void setKnobRadius(double radius);
    double getKnobRadius() const;

    void setKnobMargin(double margin);
    double getKnobMargin() const;

private:
    virtual void paintEvent(QPaintEvent*) override;
    double knobRadius_;
    double knobMargin_;
};

#endif // DISPLAYSELECTORDIAL_H
