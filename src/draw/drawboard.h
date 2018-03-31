#ifndef DRAWBOARD_H
#define DRAWBOARD_H

#include <QPainter>
#include <QQuickPaintedItem>
#include <QVariantList>

class DrawShape;

class DrawBoard : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(qint32 paintState READ paintState WRITE setPaintState NOTIFY paintStateChanged)
    Q_PROPERTY(qreal paintSize READ paintSize WRITE setPaintSize NOTIFY paintSizeChanged)
    Q_PROPERTY(qreal textSize READ textSize WRITE setTextSize NOTIFY textSizeChanged)
    Q_PROPERTY(QColor paintColor READ paintColor WRITE setPaintColor NOTIFY paintColorChanged)

public:
    enum StateType
    {
        None,
        Pen,
        Lines,
        Text
    };

    Q_ENUMS(StateType)

public:
    explicit DrawBoard(QQuickItem *parent = nullptr);

    void paint(QPainter *painter);

    void setPaintState(qint32 inPaintState);
    void setPaintSize(qreal inPaintSize);
    void setTextSize(qreal inTextSize);
    void setPaintColor(QColor inPaintColor);

    Q_INVOKABLE void drawPoints(QVariantList points);
    Q_INVOKABLE void drawLines(QVariantList points);
    Q_INVOKABLE void drawText(QRectF rect, QString text);

    Q_INVOKABLE void undo();
    Q_INVOKABLE void redo();
    Q_INVOKABLE bool undoable();
    Q_INVOKABLE bool redoable();

    qint32 paintState() const;
    qreal paintSize() const;
    qreal textSize() const;
    QColor paintColor() const;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void hoverEnterEvent(QHoverEvent *event);
    void hoverMoveEvent(QHoverEvent *event);
    void hoverLeaveEvent(QHoverEvent *event);

private:
    qint32 _paintState;
    qreal _paintSize;
    qreal _textSize;
    QColor _paintColor;

    QVector<DrawShape*> _paintItems;
    int _itemBackCount;

signals:
    void paintStateChanged();
    void paintSizeChanged();
    void textSizeChanged();
    void paintColorChanged();
    void itemBackChanged();

public slots:


};

#endif // DRAWBOARD_H
