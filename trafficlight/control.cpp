#include <QEvent>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMessageBox>
#include <QColor>
#include <QColorDialog>
#include <QTime>
#include <QEventLoop>
#include <QFont>
#include <QLabel>
#include "control.h"
#include "car.h"
#include "light.h"

Control::Control(QGraphicsScene &scene, QObject *parent) ://构造函数
    QObject(parent),
    scene(scene),
    car1(new Car(*this)),car2(new Car(*this)),
    car3(new Car(*this)),car4(new Car(*this))
{

    QPen pen;//
    pen.setWidth(3);
    scene.addLine(210, 0, 210, 210,pen);//(x1,y1,x2,y2,QPen)
    scene.addLine(0, 210, 210, 210,pen);
    scene.addLine(0, 290, 210, 290,pen);
    scene.addLine(210, 500, 210, 290,pen);

    scene.addLine(290, 0, 290, 210,pen);
    scene.addLine(500, 210, 290, 210,pen);
    scene.addLine(290, 290, 500, 290,pen);
    scene.addLine(290, 290, 290, 500,pen);

    pen.setStyle(Qt::DashLine);
    scene.addLine(0, 250, 210, 250,pen);
    scene.addLine(250, 0, 250, 210,pen);
    scene.addLine(250, 290, 250, 500,pen);
    scene.addLine(290, 250, 500, 250,pen);


    QLabel *pLabel1 = new QLabel();
    pLabel1->setText("上：");
    pLabel1->setGeometry(0,0,20,10);
    scene.addWidget(pLabel1);

    QLabel *pLabel2 = new QLabel();
    pLabel2->setText("下：");
    pLabel2->setGeometry(0,20,20,10);
    scene.addWidget(pLabel2);

    QLabel *pLabel3 = new QLabel();
    pLabel3->setText("左：");
    pLabel3->setGeometry(0,40,20,10);
    scene.addWidget(pLabel3);

    QLabel *pLabel4 = new QLabel();
    pLabel4->setText("右：");
    pLabel4->setGeometry(0,60,20,10);
    scene.addWidget(pLabel4);

    numLeftLabel= new QLabel();
    numRightLabel= new QLabel();
    numUpLabel= new QLabel();
    numDownLabel= new QLabel();

    numLeftLabel->setText(QString::number(10));
    numLeftLabel->setGeometry(30,40,20,10);
    scene.addWidget(numLeftLabel);

    numRightLabel->setText(QString::number(10));
    numRightLabel->setGeometry(30,60,20,10);
    scene.addWidget(numRightLabel);
    numUpLabel->setText(QString::number(10));
    numUpLabel->setGeometry(30,0,20,10);
    scene.addWidget(numUpLabel);
    numDownLabel->setText(QString::number(10));
    numDownLabel->setGeometry(30,20,20,10);
    scene.addWidget(numDownLabel);

   lig1=new Light(210,250);//灯的位置
   lig2=new Light(290,250);
   lig3=new Light(250,210);
   lig4=new Light(250,290);

   lig1->cl=QColor(Qt::green);
   scene.addItem(lig1);
   lig2->cl=QColor(Qt::green);
   scene.addItem(lig2);
   lig3->cl=QColor(Qt::red);
   scene.addItem(lig3);
   lig4->cl=QColor(Qt::red);
   scene.addItem(lig4);

   car1->location=QPointF(190,230);//车的初始位置
   car2->location=QPointF(300,270);
   car3->location=QPointF(230,190);
   car4->location=QPointF(270,300);


   scene.addItem(car1);  
   scene.addItem(car2);
   scene.addItem(car3);
   scene.addItem(car4);


   timer3 = new QTimer(this);
   timer4 = new QTimer(this);
   timer5 = new QTimer(this);

   runisconnect=true;
   run();//先运行一波

   timer.start(50);
   connect(&timer, SIGNAL(timeout()),
           &scene, SLOT(advance()));
   //QGraphicsScene::advance()
   //控制车运动的计时器

   timer2 = new QTimer(this);
   connect(timer2, SIGNAL(timeout()), this, SLOT(run()));

   timer2->start(10000+2000);//以12s为一个周期

   timer3->start(4000);
   timer4->start(5000);
   timer5->start(11000);


}

Control::~Control()//析构函数
{
}



void Control::yellowlight1()
{
    //每次运行之后修改oddeven的值

    scene.removeItem(lig1);
    scene.removeItem(lig2);
    scene.removeItem(lig3);
    scene.removeItem(lig4);
    scene.removeItem(car1);
    scene.removeItem(car2);
    scene.removeItem(car3);
    scene.removeItem(car4);

    //作用
    lig1->cl=QColor(Qt::yellow);
    scene.addItem(lig1);
    lig2->cl=QColor(Qt::yellow);
    scene.addItem(lig2);
    lig3->cl=QColor(Qt::red);
    scene.addItem(lig3);
    lig4->cl=QColor(Qt::red);
    scene.addItem(lig4);

    car1->setMoveDirection(Car::MoveRight);
    scene.addItem(car1);
    car2->setMoveDirection(Car::MoveLeft);
    scene.addItem(car2);
    car3->setMoveDirection(Car::NoMove);
    scene.addItem(car3);
    car4->setMoveDirection(Car::NoMove);
    scene.addItem(car4);
}


void Control::yellowlight2()
{
    //每次运行之后修改oddeven的值

    scene.removeItem(lig1);
    scene.removeItem(lig2);
    scene.removeItem(lig3);
    scene.removeItem(lig4);
    scene.removeItem(car1);
    scene.removeItem(car2);
    scene.removeItem(car3);
    scene.removeItem(car4);

    //上下
    lig1->cl=QColor(Qt::red);
    scene.addItem(lig1);
    lig2->cl=QColor(Qt::red);
    scene.addItem(lig2);
    lig3->cl=QColor(Qt::yellow);
    scene.addItem(lig3);
    lig4->cl=QColor(Qt::yellow);
    scene.addItem(lig4);

    car1->setMoveDirection(Car::NoMove);
    scene.addItem(car1);
    car2->setMoveDirection(Car::NoMove);
    scene.addItem(car2);
    car3->setMoveDirection(Car::MoveDown);
    scene.addItem(car3);
    car4->setMoveDirection(Car::MoveUp);
    scene.addItem(car4);

}

void Control::manycars1()
{


    car1->location=QPointF(190,230);
    car2->location=QPointF(300,270);
    car3->location=QPointF(230,190);
    car4->location=QPointF(270,300);

    scene.removeItem(lig1);
    scene.removeItem(lig2);
    scene.removeItem(lig3);
    scene.removeItem(lig4);
    scene.removeItem(car1);
    scene.removeItem(car2);
    scene.removeItem(car3);
    scene.removeItem(car4);


    //左右
    lig1->cl=QColor(Qt::green);
    scene.addItem(lig1);
    lig2->cl=QColor(Qt::green);
    scene.addItem(lig2);
    lig3->cl=QColor(Qt::red);
    scene.addItem(lig3);
    lig4->cl=QColor(Qt::red);
    scene.addItem(lig4);

    car1->setMoveDirection(Car::MoveRight);
    scene.addItem(car1);
    car2->setMoveDirection(Car::MoveLeft);
    scene.addItem(car2);
    car3->setMoveDirection(Car::NoMove);
    scene.addItem(car3);
    car4->setMoveDirection(Car::NoMove);
    scene.addItem(car4);
}


void Control::manycars2(){


    car1->location=QPointF(190,230);
    car2->location=QPointF(300,270);
    car3->location=QPointF(230,190);
    car4->location=QPointF(270,300);

    scene.removeItem(lig1);
    scene.removeItem(lig2);
    scene.removeItem(lig3);
    scene.removeItem(lig4);
    scene.removeItem(car1);
    scene.removeItem(car2);
    scene.removeItem(car3);
    scene.removeItem(car4);

   lig1->cl=QColor(Qt::red);
   scene.addItem(lig1);
   lig2->cl=QColor(Qt::red);
   scene.addItem(lig2);
   lig3->cl=QColor(Qt::green);
   scene.addItem(lig3);
   lig4->cl=QColor(Qt::green);
   scene.addItem(lig4);

   car1->setMoveDirection(Car::NoMove);
   scene.addItem(car1);
   car2->setMoveDirection(Car::NoMove);
   scene.addItem(car2);
   car3->setMoveDirection(Car::MoveDown);
   scene.addItem(car3);
   car4->setMoveDirection(Car::MoveUp);
   scene.addItem(car4);


}


int get_random_number(int t)//生成不重复的一组随机数
{
    int i,j;
    QList<int> numbersList;//线性表
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));//当前时间(s)
    for(i=0;i<10;i++){
        numbersList.append(qrand()%10);//生成一个随机数
        bool flag=true;
        while(flag){
            for(j=0;j<i;j++){
                if(numbersList[i]==numbersList[j]){
                    break;
                }
            }
            if(j<i){
                numbersList[i]=rand()%50;
                //如果之前存在与这个随机数相同的随机数
                //就改变这个数的随机值
            }
            else if(j==i){
                flag=!flag;//所有数都不相同，跳出循环
            }
        }
    }
    return numbersList[t];
}


void Control::run(){
    double numleft=get_random_number(2)+1;//各个方向的等待车辆数
    double numright=get_random_number(4)+1;
    double numup=get_random_number(6)+1;
    double numdown=get_random_number(8)+1;

    /*测试样例
    double numleft=40;
    double numright=40;
    double numup=10;
    double numdown=10;*/

    numLeftLabel->setText(QString::number(numleft));//写入刷新的各方向车辆数
    numRightLabel->setText(QString::number(numright));
    numUpLabel->setText(QString::number(numup));
    numDownLabel->setText(QString::number(numdown));


    counttime=(numleft+numright)/(numleft+numright+numup+numdown);


    manycars1();//运行一下(让车多的方向通过)

    timer3->stop();
    timer3->start(10000*counttime);
    timer3->setSingleShot(true);
    connect(timer3, SIGNAL(timeout()), this, SLOT(yellowlight1()));

    timer4->stop();
    timer4->start(10000*counttime+1000);
    timer4->setSingleShot(true);
    connect(timer4, SIGNAL(timeout()), this, SLOT(manycars2()));

    timer5->stop();
    timer5->start(11000);
    timer5->setSingleShot(true);
    connect(timer5, SIGNAL(timeout()), this, SLOT(yellowlight2()));

}

void Control::pause()//暂停
{
    if(runisconnect){
        runisconnect=false;
        disconnect(&timer, SIGNAL(timeout()),
                   &scene, SLOT(advance()));
        disconnect(timer2, SIGNAL(timeout()),
                   this, SLOT(run()));
        disconnect(timer3, SIGNAL(timeout()),
                   this, SLOT(yellowlight1()));
        disconnect(timer4, SIGNAL(timeout()),
                   this, SLOT(manycars2()));
        disconnect(timer5, SIGNAL(timeout()),
                   this, SLOT(yellowlight2()));
    }
}

void Control::resume()//重新开始
{
    if(!runisconnect){
        runisconnect=true;
        connect(&timer, SIGNAL(timeout()),
                &scene, SLOT(advance()));
        run();
        connect(timer2, SIGNAL(timeout()),
                this, SLOT(run()));
        timer2->stop();
        timer2->start(10000+2000);

    }

}
