#ifndef TEXTSHAPE_H
#define TEXTSHAPE_H

#include <QPainter>
#include "drawshape.h"

class TextShape : public DrawShape
{
    Q_OBJECT

    Q_PROPERTY(QFont paintFont READ paintFont WRITE setPaintFont NOTIFY paintFontChanged)
    Q_PROPERTY(QRectF paintRect READ paintRect WRITE setPaintRect NOTIFY paintRectChanged)
    Q_PROPERTY(QRectF boundingRect READ boundingRect NOTIFY boundingRectChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

public:
    explicit TextShape(DrawBoard *parent);

    const QFont& paintFont();
    QRectF paintRect();
    QRectF boundingRect();
    const QString& text();

    void setPaintFont(const QFont& inPaintFont);
    void setPaintRect(const QRectF& inPaintRect);
    void setPaintRectSize(QSizeF inSize);
    void setText(const QString& inText);

    void paint(QPainter* painter);
    QRectF bound() const;

private:
    QFont _paintFont;
    QRectF _paintRect;
    QRectF _boundingRect;
    QString _text;

signals:
    void paintFontChanged();
    void paintRectChanged();
    void boundingRectChanged();
    void textChanged();

public slots:
};

#endif // TEXTSHAPE_H
