#include <QDebug>

#include "drawboard.h"
#include "penshape.h"
#include "linesshape.h"


DrawBoard::DrawBoard(QQuickItem *parent) :
    QQuickPaintedItem(parent),
    _paintState(None),
    _paintSize(2),
    _textSize(12),
    _paintColor(Qt::black),
    _inHoverState(false)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);
}

void DrawBoard::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);

    painter->setBrush(QBrush(Qt::white));
    painter->setPen(Qt::white);

    painter->drawRect(QRectF(QPointF(0,0),size()));

    foreach(DrawShape* item, _paintItems)
    {
        item->paint(painter);
    }
}

void DrawBoard::setPaintState(qint32 inPaintState)
{
    _paintState = inPaintState;
    paintStateChanged();
}

void DrawBoard::setPaintSize(qreal inPaintSize)
{
    _paintSize = inPaintSize;
    paintSizeChanged();
}

void DrawBoard::setTextSize(qreal inTextSize)
{
    _textSize = inTextSize;
    textSizeChanged();
}

void DrawBoard::setPaintColor(QColor inPaintColor)
{
    _paintColor = inPaintColor;
    paintColorChanged();
}

void DrawBoard::drawPoints(QVariantList  points)
{
}

void DrawBoard::drawLines(QVariantList points)
{
}

void DrawBoard::drawText(QRectF rect, QString text)
{
}

qint32 DrawBoard::paintState() const
{
    return _paintState;
}

qreal DrawBoard::paintSize() const
{
    return _paintSize;
}

qreal DrawBoard::textSize() const
{
    return _textSize;
}

QColor DrawBoard::paintColor() const
{
    return _paintColor;
}

void DrawBoard::mousePressEvent(QMouseEvent *event)
{
    switch(event->button())
    {
    case Qt::LeftButton:
        switch(_paintState)
        {
        case Pen:
            _paintItems.push_back(new PenShape(this));
            ((PenShape*)_paintItems.back())->pushPoint(event->pos());

            break;
        case Lines:
            if(!_inHoverState)
            {
                _paintItems.push_back(new LinesShape(this));
                ((LinesShape*)_paintItems.back())->pushPoint(event->pos());
                _inHoverState = true;
            }
            ((LinesShape*)_paintItems.back())->pushPoint(event->pos());

            break;
        }
        break;

    case Qt::RightButton:
        switch(_paintState)
        {
        case Lines:
            ((LinesShape*)_paintItems.back())->popPoint();
            _inHoverState = false;
            update();

            break;
        }
        break;

    default:;
    }
}


void DrawBoard::mouseMoveEvent(QMouseEvent *event)
{
    switch(_paintState)
    {
    case Pen:
        ((PenShape*)_paintItems.back())->pushPoint(event->pos());
        update();

    default:;
    }
}

void DrawBoard::mouseReleaseEvent(QMouseEvent *event)
{
}

void DrawBoard::hoverEnterEvent(QHoverEvent *event)
{
}

void DrawBoard::hoverMoveEvent(QHoverEvent *event)
{
    if(_inHoverState)
    {
        ((LinesShape*)_paintItems.back())->setBackPoint(event->pos());
        update();
    }
}

void DrawBoard::hoverLeaveEvent(QHoverEvent *event)
{

}

