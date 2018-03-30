#include "drawshape.h"


DrawShape::DrawShape(DrawBoard *parent) :
    QObject((QObject*)parent)
{
}

QBrush DrawShape::paintBrush()
{
    return _paintBrush;
}

QPen DrawShape::paintPen()
{
    return _paintPen;
}

void DrawShape::setPaintBrush(const QBrush &inPaintBrush)
{
    _paintBrush = inPaintBrush;
    paintBrushChanged();
}

void DrawShape::setPaintPen(const QPen &inPaintPen)
{
    _paintPen = inPaintPen;
    paintPenChanged();
}

DrawShape::~DrawShape()
{

}

void DrawShape::paint(QPainter *painter)
{
    painter->setBrush(_paintBrush);
    painter->setPen(_paintPen);
}
