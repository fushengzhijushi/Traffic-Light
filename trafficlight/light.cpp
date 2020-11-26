#include <QPainter>

#include "light.h"

const int TILE_SIZE = 10;
static const qreal light_RADIUS = 8.0;

Light::Light(qreal x, qreal y)
{
    setPos(x, y);
}

QRectF Light::boundingRect() const//矩形属性，以(x,y)为中心,边长为 TILE_SIZE * 2 的正方形
{
    return QRectF(-TILE_SIZE,    -TILE_SIZE,
                   TILE_SIZE * 2, TILE_SIZE * 2 );
}

void Light::paint(QPainter *painter,const QStyleOptionGraphicsItem *,QWidget *)//显示时自动调用
{

    painter->save();

    painter->setRenderHint(QPainter::Antialiasing,true);//反走样
    if(cl==QColor(Qt::red)) {//红绿灯
         painter->fillPath(shape(), Qt::red);
    }
    else if (cl==QColor(Qt::yellow)){
        painter->fillPath(shape(), Qt::yellow);
    }
    else {
        painter->fillPath(shape(), Qt::green);
    }

    painter->restore();//保存画笔状态
}

QPainterPath Light::shape() const//圆在矩形里，圆心在(0,0)
{
    QPainterPath p;
    p.addEllipse(QPointF(0, 0), light_RADIUS, light_RADIUS);//
    return p;
}
