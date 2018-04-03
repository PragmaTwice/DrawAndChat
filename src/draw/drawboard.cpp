#include <QDebug>

#include "drawboard.h"
#include "drawshape.h"
#include "penshape.h"
#include "linesshape.h"
#include "textshape.h"


DrawBoard::DrawBoard(QQuickItem *parent) :
    QQuickPaintedItem(parent),
    _paintState(None),
    _paintSize(1),
    _textSize(12),
    _paintColor(Qt::black),
    _itemBackCount(0)
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

    for(int index = 0; index < _paintItems.size() - _itemBackCount; ++index)
    {
        _paintItems[index]->paint(painter);
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

void DrawBoard::setNowText(const QString &inNowText)
{
    _nowText = inNowText;
    nowTextChanged();
}

void DrawBoard::drawPoints(QVariantList  points)
{
    auto shape = new PenShape(this);
    foreach(const QVariant& arg, points)
    {
        shape->pushPoint(arg.toPointF());
    }
    _paintItems.push_back(shape);
}

void DrawBoard::drawLines(QVariantList points)
{
    auto shape = new LinesShape(this);
    foreach(const QVariant& arg, points)
    {
        shape->pushPoint(arg.toPointF());
    }
    _paintItems.push_back(shape);
}

void DrawBoard::drawText(QRectF rect, QString text)
{
    auto shape = new TextShape(this);
    shape->setPaintRect(rect);
    shape->setText(text);
    _paintItems.push_back(shape);
}

void DrawBoard::undo()
{
    if(undoable())
    {
        _itemBackCount++;
        itemBackChanged();

        update();
    }
}

void DrawBoard::redo()
{
    if(redoable())
    {
        _itemBackCount--;
        itemBackChanged();

        update();
    }
}

bool DrawBoard::undoable()
{
    return _paintItems.size() - _itemBackCount > 0;
}

bool DrawBoard::redoable()
{
    return _itemBackCount > 0;
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

const QString &DrawBoard::nowText() const
{
    return _nowText;
}

void DrawBoard::mousePressEvent(QMouseEvent *event)
{
    switch(event->button())
    {
    case Qt::LeftButton:
        if(_paintState != None && _itemBackCount != 0)
        {
            _paintItems.resize(_paintItems.size() - _itemBackCount);

            _itemBackCount = 0;
            itemBackChanged();
        }

        switch(_paintState)
        {
        case Pen:
            _paintItems.push_back(new PenShape(this));
            _paintItems.back()->setPainting(true);
            qobject_cast<PenShape*>(_paintItems.back())->pushPoint(event->pos());

            break;
        case Lines:
            if(_paintItems.empty() || !_paintItems.back()->painting())
            {
                _paintItems.push_back(new LinesShape(this));
                _paintItems.back()->setPainting(true);
                qobject_cast<LinesShape*>(_paintItems.back())->pushPoint(event->pos());
            }
            qobject_cast<LinesShape*>(_paintItems.back())->pushPoint(event->pos());

            break;

        case Text:
            _paintItems.push_back(new TextShape(this));
            _paintItems.back()->setPainting(true);
            qobject_cast<TextShape*>(_paintItems.back())->setPaintRect(QRectF(event->pos(),QSize(0,0)));
            qobject_cast<TextShape*>(_paintItems.back())->setText(_nowText);

            break;

        default:;
        }
        itemBackChanged();

        break;

    case Qt::RightButton:
        switch(_paintState)
        {
        case Lines:
            qobject_cast<LinesShape*>(_paintItems.back())->popPoint();
            _paintItems.back()->setPainting(false);
            update();

            break;
        }
        break;

    default:;
    }
}


void DrawBoard::mouseMoveEvent(QMouseEvent *event)
{
    TextShape* back;
    QPointF diffPos;

    switch(_paintState)
    {
    case Pen:
        qobject_cast<PenShape*>(_paintItems.back())->pushPoint(event->pos());
        update();

        break;

    case Text:
        back = qobject_cast<TextShape*>(_paintItems.back());
        diffPos = event->pos() - back->paintRect().topLeft();

        back->setPaintRectSize(QSize(diffPos.x(), diffPos.y()));
        update();

        break;

    default:;
    }
}

void DrawBoard::mouseReleaseEvent(QMouseEvent *event)
{
    switch(_paintState)
    {
    case Pen:
        _paintItems.back()->setPainting(false);
        update();

        break;

    case Text:
        _paintItems.back()->setPainting(false);
        update();

        break;


    default:;
    }
}

void DrawBoard::hoverEnterEvent(QHoverEvent *event)
{
}

void DrawBoard::hoverMoveEvent(QHoverEvent *event)
{
    if(!_paintItems.empty() && _paintItems.back()->painting())
    {
        qobject_cast<LinesShape*>(_paintItems.back())->setBackPoint(event->pos());
        update();
    }
}

void DrawBoard::hoverLeaveEvent(QHoverEvent *event)
{

}

