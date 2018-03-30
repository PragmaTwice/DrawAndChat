#include "linesshape.h"
#include "drawboard.h"

LinesShape::LinesShape(DrawBoard *parent) :
    DrawShape(parent)
{
    setPaintBrush(QBrush(Qt::NoBrush));
    setPaintPen(QPen(QBrush(parent->paintColor()),parent->paintSize()));
}

const QVector<QPointF> &LinesShape::points()
{
    return _points;
}

void LinesShape::setPoints(const QVector<QPointF> &inPoints)
{
    _points = inPoints;
    pointsChanged();
}

void LinesShape::pushPoint(QPointF point)
{
    _points.push_back(point);
    pointsChanged();
}

void LinesShape::popPoint()
{
    _points.pop_back();
    pointsChanged();
}

void LinesShape::setBackPoint(QPointF point)
{
    _points.back() = point;
    pointsChanged();
}

void LinesShape::paint(QPainter *painter)
{
    DrawShape::paint(painter);

    painter->drawPolyline(_points.data(), _points.size());
}
