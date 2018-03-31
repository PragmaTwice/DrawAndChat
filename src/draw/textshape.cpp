#include "textshape.h"
#include "drawboard.h"

TextShape::TextShape(DrawBoard *parent) :
    DrawShape(parent),
    _paintFont(QFont("",parent->textSize()))
{
    setPaintBrush(QBrush(Qt::NoBrush));
    setPaintPen(QPen(QBrush(parent->paintColor()),parent->paintSize()));
}

const QFont &TextShape::paintFont()
{
    return _paintFont;
}

QRectF TextShape::paintRect()
{
    return _paintRect;
}

QRectF TextShape::boundingRect()
{
    return _boundingRect;
}

const QString &TextShape::text()
{
    return _text;
}

void TextShape::setPaintFont(const QFont &inPaintFont)
{
    _paintFont = inPaintFont;
    paintFontChanged();
}

void TextShape::setPaintRect(QRectF inPaintRect)
{
    _paintRect = inPaintRect;
    paintRectChanged();
}

void TextShape::setText(const QString &inText)
{
    _text = inText;
    textChanged();
}

void TextShape::paint(QPainter *painter)
{
    DrawShape::paint(painter);

    painter->setFont(_paintFont);

    painter->drawText(_paintRect, Qt::AlignLeft, _text, &_boundingRect);
    boundingRectChanged();
}

QRectF TextShape::bound() const
{
    return _paintRect;
}

