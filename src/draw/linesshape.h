#ifndef LINESSHAPE_H
#define LINESSHAPE_H

#include <QPainter>
#include "drawshape.h"

class LinesShape : public DrawShape
{
    Q_OBJECT

    Q_PROPERTY(QVector<QPointF> points READ points WRITE setPoints NOTIFY pointsChanged)

public:
    explicit LinesShape(DrawBoard *parent);

    const QVector<QPointF>& points();

    void setPoints(const QVector<QPointF>& inPoints);
    void pushPoint(QPointF point);
    void popPoint();
    void setBackPoint(QPointF point);

    void paint(QPainter *painter);

private:
    QVector<QPointF> _points;

signals:
    void pointsChanged();

public slots:
};

#endif // LINESSHAPE_H
