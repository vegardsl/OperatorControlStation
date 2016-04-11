#include "displayselectordial.h"

#include <QPainter>
#include <QColor>

#include <cmath>

#include <QDebug>

#define M_PI 3.14159265358979323846 /* pi */

DisplaySelectorDial::DisplaySelectorDial(QWidget* parent,
                                          double knobRadius,
                                          double knobMargin)
                                         : QDial(parent),
                                           knobRadius_(knobRadius),
                                           knobMargin_(knobMargin)
{
     QDial::setRange(0,2);
}

void DisplaySelectorDial::setKnobRadius(double radius)
{
    knobRadius_ = radius;
}

double DisplaySelectorDial::getKnobRadius() const
{
    return knobRadius_;
}

void DisplaySelectorDial::setKnobMargin(double margin)
{
    knobMargin_ = margin;
}

double DisplaySelectorDial::getKnobMargin() const
{
    return knobMargin_;
}

void DisplaySelectorDial::paintEvent(QPaintEvent*)
{
    static const double degree270 = 1.5 * M_PI;

    static const double degree225 = 1.25 * M_PI;

    QPainter painter(this);

    // So that we can use the background color
    painter.setBackgroundMode(Qt::OpaqueMode);

    // Smooth out the circle
    painter.setRenderHint(QPainter::Antialiasing);

    // Use background color
    painter.setBrush(painter.background());

    // Store color from stylesheet, pen will be overriden
    QColor pointColor(painter.pen().color());

    // No border
    painter.setPen(QPen(Qt::NoPen));

    // Draw first circle
    painter.drawEllipse(0, 0, QDial::height(), QDial::height());

    // Reset color to pointColor from stylesheet
    painter.setBrush(QBrush(pointColor));

    // Get ratio between current value and maximum to calculate angle
    double ratio = static_cast<double>(QDial::value()) / QDial::maximum();

    // The maximum amount of degrees is 270, offset by 225
    double angle = ratio * degree270 - degree225;

    // Radius of background circle
    double r = QDial::height() / 2.0;

    // Add r to have (0,0) in center of dial
    double y = sin(angle) * (r - knobRadius_ - knobMargin_) + r;

    double x = cos(angle) * (r - knobRadius_ - knobMargin_) + r;

    // Draw the ellipse
    painter.drawEllipse(QPointF(x,y),knobRadius_, knobRadius_);

    qDebug() << "Painted";
}


//void QDial::sliderChange()
