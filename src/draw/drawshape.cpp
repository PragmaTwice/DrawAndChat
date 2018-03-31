#include "drawshape.h"
#include "drawboard.h"


DrawShape::DrawShape(DrawBoard *parent) :
    QObject(parent),
    _painting(true)
{
}

QBrush DrawShape::paintBrush() const
{
    return _paintBrush;
}

QPen DrawShape::paintPen() const
{
    return _paintPen;
}

bool DrawShape::painting() const
{
    return _painting;
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

void DrawShape::setPainting(bool inPainting)
{
    _painting = inPainting;
    paintingChanged();
}

DrawShape::~DrawShape()
{

}

void DrawShape::paint(QPainter *painter)
{
    if(_painting)
    {
        painter->setPen(Qt::DotLine);
        painter->drawRect(bound());
    }

    painter->setBrush(_paintBrush);
    painter->setPen(_paintPen);

}

QRectF DrawShape::bound() const
{
    return {};
}
