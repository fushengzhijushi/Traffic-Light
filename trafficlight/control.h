#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include <QTimer>
#include <QGraphicsItem>
#include <QColor>
#include <QEvent>
#include <QLabel>

class QGraphicsScene;


class Car;
class Light;

class Control : public QObject
{
    Q_OBJECT
public:
    Control(QGraphicsScene &scene, QObject *parent = 0);
    ~Control();

    QTimer timer;
    QTimer *timer2;

    QTimer *timer3;
    QTimer *timer4;
    QTimer *timer5;

    double counttime;
    QColor col;

    QGraphicsScene &scene;
    Car *car1;
    Car *car2;
    Car *car3;
    Car *car4;


    Light *lig1;
    Light *lig2;
    Light *lig3;
    Light *lig4;

    QLabel *numLeftLabel;
    QLabel *numRightLabel;
    QLabel *numUpLabel;
    QLabel *numDownLabel;

    bool runisconnect;

private slots:
    void run();
    void manycars1();
    void yellowlight1();
    void manycars2();
    void yellowlight2();

public slots:
    void pause();
    void resume();
};
#endif // CONTROL_H
