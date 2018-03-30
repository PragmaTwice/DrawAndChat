#ifndef DRAWSHAPE_H
#define DRAWSHAPE_H

#include <QPainter>

class DrawBoard;

class DrawShape : public QObject
{

    Q_OBJECT

    Q_PROPERTY(QBrush paintBrush READ paintBrush WRITE setPaintBrush NOTIFY paintBrushChanged)
    Q_PROPERTY(QPen paintPen READ paintPen WRITE setPaintPen NOTIFY paintPenChanged)

private:

    QBrush _paintBrush;
    QPen _paintPen;

public:
    explicit DrawShape(DrawBoard* parent);

    virtual void paint(QPainter* painter);

    QBrush paintBrush();
    QPen paintPen();

    void setPaintBrush(const QBrush& inPaintBrush);
    void setPaintPen(const QPen& inPaintPen);

    virtual ~DrawShape();

signals:
    void paintBrushChanged();
    void paintPenChanged();

public slots:

};

#endif // DRAWSHAPE_H
