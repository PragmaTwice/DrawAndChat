#include "penshape.h"
#include "drawboard.h"

PenShape::PenShape(DrawBoard *parent) :
    DrawShape(parent)
{
    setPaintBrush(QBrush(Qt::NoBrush));
    setPaintPen(QPen(QBrush(parent->paintColor()),parent->paintSize()));
}

const QVector<QPointF> &PenShape::points()
{
    return _points;
}

void PenShape::setPoints(const QVector<QPointF> &inPoints)
{
    _points = inPoints;
    pointsChanged();
}

void PenShape::pushPoint(QPointF point)
{
    _points.push_back(point);
    pointsChanged();
}

void PenShape::popPoint()
{
    _points.pop_back();
    pointsChanged();
}

void PenShape::paint(QPainter *painter)
{
    DrawShape::paint(painter);

    if(!_points.empty())
    {
        QPainterPath path(_points.front());

        int index = 1;
        for(; index + 2 < _points.size(); index += 3)
        {
            path.cubicTo(_points[index],_points[index+1],_points[index+2]);
        }
        for(; index < _points.size(); ++index)
        {
            path.lineTo(_points[index]);
        }

        painter->drawPath(path);
    }
}

QRectF PenShape::bound() const
{
    if(!_points.empty())
    {
        auto i = _points.cbegin();

        QPointF min(*i), max(*i);

        for(++i; i != _points.cend(); ++i)
        {
            if(i->x() < min.x())
            {
                min.setX(i->x());
            }
            else if(max.x() < i->x())
            {
                max.setX(i->x());
            }
            if(i->y() < min.y())
            {
                min.setY(i->y());
            }
            else if(max.y() < i->y())
            {
                max.setY(i->y());
            }
        }

        return QRectF(min,max);
    }

    return QRectF(0,0,0,0);
}
