#ifndef DRAWSHAPE_H
#define DRAWSHAPE_H

#include <QPainter>

class DrawBoard;

class DrawShape : public QObject
{

    Q_OBJECT

    Q_PROPERTY(QBrush paintBrush READ paintBrush WRITE setPaintBrush NOTIFY paintBrushChanged)
    Q_PROPERTY(QPen paintPen READ paintPen WRITE setPaintPen NOTIFY paintPenChanged)
    Q_PROPERTY(bool painting READ painting WRITE setPainting NOTIFY paintingChanged)

private:

    QBrush _paintBrush;
    QPen _paintPen;
    bool _painting;

public:
    explicit DrawShape(DrawBoard* parent);

    virtual void loadArguments(const QVariantMap& arguments);
    virtual QVariantMap dumpArguments();

    virtual void paint(QPainter* painter);
    virtual QRectF bound() const;

    virtual int paintState() const;

    QBrush paintBrush() const;
    QPen paintPen() const;
    bool painting() const;

    void setPaintBrush(const QBrush& inPaintBrush);
    void setPaintPen(const QPen& inPaintPen);
    void setPainting(bool inPainting);

    virtual ~DrawShape();

signals:
    void paintBrushChanged();
    void paintPenChanged();
    void paintingChanged();

public slots:

};

#endif // DRAWSHAPE_H
