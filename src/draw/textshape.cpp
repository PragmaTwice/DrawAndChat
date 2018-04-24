#include "textshape.h"
#include "drawboard.h"

TextShape::TextShape(DrawBoard *parent) :
    DrawShape(parent),
    _paintFont(QFont("",parent->textSize()))
{
    setPaintBrush(QBrush(Qt::NoBrush));
    setPaintPen(QPen(QBrush(parent->paintColor()),parent->paintSize()));
}

void TextShape::loadArguments(const QVariantMap &arguments)
{
    DrawShape::loadArguments(arguments);


    auto foundSize = arguments.find("size");
    if(foundSize != arguments.cend())
    {
        _paintFont.setPointSizeF(foundSize->toReal());
    }

    auto foundRect = arguments.find("rect");
    auto foundText = arguments.find("text");

    if(foundRect != arguments.cend() && foundText != arguments.cend())
    {
        auto rectVal = foundRect->toList();
        if(rectVal.size() == 4)
        {
            setPaintRect(QRectF(rectVal[0].toReal(),rectVal[1].toReal(),rectVal[2].toReal(),rectVal[3].toReal()));
        }

        setText(foundText->toString());
    }
}

QVariantMap TextShape::dumpArguments()
{
    QVariantMap arguments = DrawShape::dumpArguments();

    arguments.insert("rect", QVariantList{ _paintRect.left(), _paintRect.top(), _paintRect.width(), _paintRect.height() });

    arguments.insert("text", _text);

    arguments.insert("size", _paintFont.pointSizeF());

    return arguments;
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

    font.setPointSizeF(_paintFont.pointSizeF());

    painter->setFont(font);

    painter->drawText(_paintRect, Qt::AlignLeft | Qt::TextWrapAnywhere, _text, &_boundingRect);
    boundingRectChanged();
}

QRectF TextShape::bound() const
{
    return _paintRect;
}

int TextShape::paintState() const
{
    return DrawBoard::Text;
}


