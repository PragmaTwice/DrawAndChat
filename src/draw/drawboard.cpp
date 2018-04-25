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
    _enableDraw(true)
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

    for(const DrawInfo& info : _paintItems)
    {
        info.shape->paint(painter);
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

void DrawBoard::drawPoints(int key, const QString& author, const QVariantMap &arguments)
{
    auto shape = new PenShape(this);

    shape->loadArguments(arguments);
    _paintItems.insert(key, DrawInfo(author, shape));
    update();
}

void DrawBoard::drawLines(int key, const QString& author, const QVariantMap &arguments)
{
    auto shape = new LinesShape(this);

    shape->loadArguments(arguments);
    _paintItems.insert(key, DrawInfo(author, shape));
    update();
}

void DrawBoard::drawText(int key, const QString& author, const QVariantMap &arguments)
{
    auto shape = new TextShape(this);

    shape->loadArguments(arguments);
    _paintItems.insert(key, DrawInfo(author, shape));
    update();
}

void DrawBoard::drawShape(int key, const QString &author, DrawBoard::StateType state, const QVariantMap &arguments)
{
    switch(state)
    {
    case Pen:
        drawPoints(key, author, arguments);
        break;
    case Lines:
        drawLines(key, author, arguments);
        break;
    case Text:
        drawText(key, author, arguments);
        break;
    default:
        break;
    }
}

void DrawBoard::dumpPaint(DrawShape *shape)
{
    _enableDraw = false;
    newPaint((StateType)shape->paintState(), shape->dumpArguments());
}

void DrawBoard::undo()
{
    if(_paintItems.find(std::numeric_limits<qint32>::max()) != _paintItems.cend())
        return;

    QMapIterator<qint32, DrawInfo> iter{_paintItems};
    for(iter.toBack(), iter.previous(); iter.hasPrevious(); iter.previous())
    {
        //qDebug() << iter.value().author;
        if(iter.value().author == "")
        {
            break;
        }
    }

    if(iter.hasPrevious())
    {
        //qDebug() << "undo" << iter.key();
        deletePaint(iter.key());
        dropKey(iter.key());
    }

    //known bug : first shape cannot be undone

}

void DrawBoard::redo()
{
}

bool DrawBoard::undoable()
{
    return true;
}

bool DrawBoard::redoable()
{
    return false;
}

void DrawBoard::clear()
{
    _paintItems.clear();
    update();
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
    if(!_enableDraw) return;

    LinesShape* lineShape = nullptr;

    switch(event->button())
    {
    case Qt::LeftButton:

        switch(_paintState)
        {
        case Pen:

            _paintItems.insert(std::numeric_limits<qint32>::max(), DrawInfo("", new PenShape(this)));
            (_paintItems.end()-1)->shape->setPainting(true);
            qobject_cast<PenShape*>((_paintItems.end()-1)->shape)->pushPoint(event->pos());

            break;
        case Lines:

            if(_paintItems.empty() || !(_paintItems.end()-1)->shape->painting())
            {
                _paintItems.insert(std::numeric_limits<qint32>::max(),DrawInfo("",new LinesShape(this)));

                (_paintItems.end()-1)->shape->setPainting(true);
                qobject_cast<LinesShape*>((_paintItems.end()-1)->shape)->pushPoint(event->pos());
            }

            lineShape = qobject_cast<LinesShape*>((_paintItems.end()-1)->shape);
            if(lineShape != nullptr)
            {
                lineShape->pushPoint(event->pos());
            }

            break;

        case Text:

            _paintItems.insert(std::numeric_limits<qint32>::max(),DrawInfo("", new TextShape(this)));
            (_paintItems.end()-1)->shape->setPainting(true);

            qobject_cast<TextShape*>((_paintItems.end()-1)->shape)->setPaintRect(QRectF(event->pos(),QSize(0,0)));
            qobject_cast<TextShape*>((_paintItems.end()-1)->shape)->setText(_nowText);

            break;

        default:;
        }
        itemBackChanged();

        break;

    case Qt::RightButton:
        switch(_paintState)
        {
        case Lines:

            if(!_paintItems.empty())
            {
                lineShape = qobject_cast<LinesShape*>((_paintItems.end()-1)->shape);
                if(lineShape != nullptr)
                {
                    lineShape->popPoint();
                    lineShape->setPainting(false);
                    dumpPaint(lineShape);
                    update();
                }
            }

            break;
        }
        break;

    default:;
    }
}


void DrawBoard::mouseMoveEvent(QMouseEvent *event)
{
    if(!_enableDraw || _paintItems.empty()) return;

    PenShape* penShape = nullptr;
    TextShape* textShape = nullptr;
    QPointF diffPos;

    auto backShape = (_paintItems.end()-1)->shape;
    switch(_paintState)
    {
    case Pen:

        penShape = qobject_cast<PenShape*>(backShape);
        if(penShape != nullptr)
        {
            penShape->pushPoint(event->pos());
            update();
        }

        break;

    case Text:

        textShape = qobject_cast<TextShape*>(backShape);
        if(textShape != nullptr)
        {
            diffPos = event->pos() - textShape->paintRect().topLeft();
            textShape->setPaintRectSize(QSize(diffPos.x(), diffPos.y()));
            update();
        }

        break;

    default:;
    }
}

void DrawBoard::mouseReleaseEvent(QMouseEvent *event)
{
    if(!_enableDraw || _paintItems.empty()) return;

    auto backShape = (_paintItems.end()-1)->shape;
    switch(_paintState)
    {
    case Pen:
        backShape->setPainting(false);
        dumpPaint(backShape);

        update();

        break;

    case Text:
        backShape->setPainting(false);
        dumpPaint(backShape);
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
    if(!_paintItems.empty() && (_paintItems.end()-1)->shape->painting())
    {
        auto linesShape = qobject_cast<LinesShape*>((_paintItems.end()-1)->shape);
        if(linesShape != nullptr)
        {
            linesShape->setBackPoint(event->pos());
            update();
        }
    }
}

void DrawBoard::hoverLeaveEvent(QHoverEvent *event)
{

}

void DrawBoard::gotKey(qint32 key)
{
    auto foundDrawing = _paintItems.find(std::numeric_limits<qint32>::max());
    if(foundDrawing != _paintItems.cend())
    {
        auto shape = foundDrawing->shape;

        _paintItems.erase(foundDrawing);
        _paintItems.insert(key, DrawInfo("", shape));

        _enableDraw = true;

        update();
    }
}

void DrawBoard::dropKey(qint32 key)
{
    auto foundDrew = _paintItems.find(key);

    if(foundDrew != _paintItems.cend())
    {
        _paintItems.erase(foundDrew);
        update();
    }
}

