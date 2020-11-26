#ifndef CAR_H
#define CAR_H

#include <QGraphicsItem>
#include <QRectF>
#include <QPen>
#include <QString>
#include <QPaintEvent>

class Control;

class Car : public QGraphicsItem
{
public:
    enum Direction {//枚举类型,小车移动方向
        NoMove,
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown
    };

    Car(Control & controller);

    QRectF boundingRect() const;//QRectF QGraphicsItem::boundingRect() const
    QPainterPath shape() const;//QPainterPath QGraphicsItem::shape() const
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    //画小车的函数

    void setMoveDirection(Direction direction);//设置移动方向
    Direction currentDirection();//返回当前方向

    QPointF        location;//位置
    Direction      moveDirection;//移动方向
    Control        &controller;//便于将Car类的实例加入Control类

    void advance(int step);

private:
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
};


#endif // CAR_H
