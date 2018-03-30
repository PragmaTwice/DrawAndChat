#ifndef PENSHAPE_H
#define PENSHAPE_H

#include <QPainterPath>
#include "drawshape.h"


class PenShape : public DrawShape
{
    Q_OBJECT

    Q_PROPERTY(QVector<QPointF> points READ points WRITE setPoints NOTIFY pointsChanged)

public:
    explicit PenShape(DrawBoard* parent);

    const QVector<QPointF>& points();

    void setPoints(const QVector<QPointF>& inPoints);
    void pushPoint(QPointF point);
    void popPoint();

    void paint(QPainter *painter);


private:
    QVector<QPointF> _points;

signals:
    void pointsChanged();

public slots:
};

#endif // PENSHAPE_H
