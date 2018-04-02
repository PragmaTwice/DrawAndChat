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

void TextShape::setPaintRect(const QRectF &inPaintRect)
{
    _paintRect = inPaintRect;
    paintRectChanged();
}

void TextShape::setPaintRectSize(QSizeF inSize)
{
    _paintRect.setSize(inSize);
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

    auto font = painter->font();

    font.setPixelSize(_paintFont.pixelSize());

    painter->setFont(font);

    painter->drawText(_paintRect, Qt::AlignLeft | Qt::TextWrapAnywhere, _text, &_boundingRect);
    boundingRectChanged();
}

QRectF TextShape::bound() const
{
    return _paintRect;
}


