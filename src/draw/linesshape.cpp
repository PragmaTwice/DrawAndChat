#include "linesshape.h"
#include "drawboard.h"

LinesShape::LinesShape(DrawBoard *parent) :
    DrawShape(parent)
{
    setPaintBrush(QBrush(Qt::NoBrush));
    setPaintPen(QPen(QBrush(parent->paintColor()),parent->paintSize()));
}

void LinesShape::loadArguments(const QVariantMap &arguments)
{
    DrawShape::loadArguments(arguments);

    _points.clear();

    auto foundPoint = arguments.find("points");
    if(foundPoint != arguments.cend())
    {
        for(const QVariant& point: foundPoint->toList())
        {
            auto pointVal = point.toList();
            if(pointVal.size() == 2)
            {
                _points.push_back(QPointF(pointVal[0].toReal(), pointVal[1].toReal()));
            }
        }
    }

    pointsChanged();
}

QVariantMap LinesShape::dumpArguments()
{
    QVariantMap arguments = DrawShape::dumpArguments();

    QVariantList vpoints;

    for(const QPointF& point : _points)
    {
        vpoints.push_back(QVariantList{ QVariant(point.x()), QVariant(point.y()) });
    }

    arguments.insert("points", vpoints);

    return arguments;
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

QRectF LinesShape::bound() const
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

int LinesShape::paintState() const
{
    return DrawBoard::Lines;
}
