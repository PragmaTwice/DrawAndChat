#ifndef DRAWBOARD_H
#define DRAWBOARD_H

#include <QPainter>
#include <QQuickPaintedItem>
#include <QVariantList>

#include "drawinfo.h"

class DrawShape;

class DrawBoard : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(qint32 paintState READ paintState WRITE setPaintState NOTIFY paintStateChanged)
    Q_PROPERTY(qreal paintSize READ paintSize WRITE setPaintSize NOTIFY paintSizeChanged)
    Q_PROPERTY(qreal textSize READ textSize WRITE setTextSize NOTIFY textSizeChanged)
    Q_PROPERTY(QColor paintColor READ paintColor WRITE setPaintColor NOTIFY paintColorChanged)
    Q_PROPERTY(QString nowText READ nowText WRITE setNowText NOTIFY nowTextChanged)

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
    void setNowText(const QString& inNowText);

    Q_INVOKABLE void drawPoints(int key, const QString& author, const QVariantMap &arguments);
    Q_INVOKABLE void drawLines(int key, const QString& author, const QVariantMap &arguments);
    Q_INVOKABLE void drawText(int key, const QString& author, const QVariantMap &arguments);
    Q_INVOKABLE void drawShape(int key, const QString& author, StateType state, const QVariantMap& arguments);

    void dumpPaint(DrawShape* shape);

    Q_INVOKABLE void undo();
    Q_INVOKABLE void redo();
    Q_INVOKABLE bool undoable();
    Q_INVOKABLE bool redoable();

    Q_INVOKABLE void clear();

    qint32 paintState() const;
    qreal paintSize() const;
    qreal textSize() const;
    QColor paintColor() const;
    const QString& nowText() const;

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
    QString _nowText;
    bool _enableDraw;

    //QVector<DrawShape*> _paintItems;
    //int _itemBackCount;

    QMap<qint32, DrawInfo> _paintItems;

signals:
    void paintStateChanged();
    void paintSizeChanged();
    void textSizeChanged();
    void paintColorChanged();
    void itemBackChanged();
    void nowTextChanged();

    void newPaint(StateType state, const QVariantMap& argMap);
    void deletePaint(qint32 key);

public slots:

    void gotKey(qint32 key);
    void dropKey(qint32 key);


};

#endif // DRAWBOARD_H
