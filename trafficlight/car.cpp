#include <QPainter>
#include <QString>
#include <QTime>
#include <QString>
#include <QFont>
#include "control.h"
#include "car.h"

const int TILE_SIZE = 10;
static const qreal Car_RADIUS = 20.0;


Car::Car(Control &controller):
    location(0, 0),
    moveDirection(MoveRight),
    controller(controller)
{

}


QRectF Car::boundingRect() const
{
    QPointF tl = mapFromScene(location);

    QRectF bound = QRectF(tl.x()-10,tl.y()-10,20,20);//(x,y,width,height),(x,y)是矩形左上角坐标

    return bound;
 }


QPainterPath Car::shape() const
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);

    QPointF p=location;
    QPointF itemp = mapFromScene(p);

    path.addEllipse(QRectF(itemp.x()-10, itemp.y()-10, Car_RADIUS, Car_RADIUS));

    return path;

}


void Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)//自动调用
{
    //paint函数在自定义图形项中画图只能在boundingRect返回的矩形范围中画图
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    painter->fillPath(shape(), Qt::white);

    painter->restore();
}


void Car::setMoveDirection(Direction direction)

{
    moveDirection = direction;
}

Car::Direction Car::currentDirection()
{
    return moveDirection;
}

void Car::advance(int step)
{
    //QGraphicsItem::advance()函数接受一个 int 作为参数;
    //这个int代表该函数被调用的时间;
    //QGraphicsItem::advance()函数会被QGraphicsScene::advance()函数调用两次：
    //第一次时这个 int 为 0，代表即将开始调用;
    //第二次这个 int 为 1，代表已经开始调用;
    //在我们的代码中，我们只使用不为 0 的阶段，因此当 !step 时，函数直接返回;

    if (!step) {
       return;
    }
    if (moveDirection == NoMove) {
        return;
    }
    switch (moveDirection) {
        case MoveLeft:
            moveLeft();
            break;
        case MoveRight:
            moveRight();
            break;
        case MoveUp:
            moveUp();
            break;
        case MoveDown:
            moveDown();
            break;
        case NoMove:
           break;
    }

    setPos(location);
}

void Car::moveLeft()
{
     location.rx() -= 10;
    if (location.rx() < 0) {
        location.rx() = 500;
    }
}

void Car::moveRight()
{
    location.rx() += 10;
    if (location.rx() >= 500) {
        location.rx() = 0;
    }
}

void Car::moveUp()
{
    location.ry() -= 10;
    if (location.ry() < 0) {
        location.ry() = 500;
    }
}

void Car::moveDown()
{
    location.ry() += 10;
    if (location.ry() >= 500) {
        location.ry() = 0;
    }
}


