#ifndef LIGHT_H
#define LIGHT_H

#include <QGraphicsItem>
#include <QRectF>
#include <QPen>
#include <QColor>
class Light : public QGraphicsItem
{
public:
    Light(qreal x, qreal y);//确定位置

    QColor cl;//颜色(红灯 or 绿灯)

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QPainterPath shape() const;

};

#endif // LIGHT_H
