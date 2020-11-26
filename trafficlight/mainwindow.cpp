#include <QGraphicsView>
#include <QTimer>
#include <qaction.h>
#include <qmenubar.h>
#include <qapplication.h>
#include <qmessagebox.h>

#include "mainwindow.h"
#include "control.h"

#include <QIcon>

const int TILE_SIZE=10;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),//初始化列表
      scene(new QGraphicsScene(this)),
      view(new QGraphicsView(scene, this)),//灰色背景
      elements(new Control(*scene, this))//小车、红路灯、马路等元素
{
    setCentralWidget(view);
    setFixedSize(500, 500);
    setWindowIcon(QIcon(":/images/light1"));

    createActions();
    createMenus();


    initScene();
    initSceneBackground();
    QTimer::singleShot(0, this, SLOT(adjustViewSize()));//在视图绘制完毕后才去改变大小
}

MainWindow::~MainWindow()
{
}

void MainWindow::adjustViewSize()
{
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatioByExpanding);
    //调整视图大小(等比例缩放铺满屏幕，超出边界的忽略）
}

void MainWindow::createActions()
{
    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setStatusTip(tr("Exit..."));
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);

    pauseAction = new QAction(tr("&Pause"), this);
    pauseAction->setStatusTip(tr("Pause..."));
    connect(pauseAction, &QAction::triggered, elements, &Control::pause);

    resumeAction = new QAction(tr("&Resume"), this);
    resumeAction->setStatusTip(tr("Resume..."));
    connect(resumeAction, &QAction::triggered, elements, &Control::resume);
}

void MainWindow::createMenus()
{
    QMenu *options = menuBar()->addMenu(tr("&Menu"));
    options->addAction(pauseAction);
    options->addAction(resumeAction);
    options->addAction(exitAction);
}

void MainWindow::initScene()
{
    scene->setSceneRect(0, 0, 500, 500);//scene矩形边界
}

void MainWindow::initSceneBackground()
{
    view->setBackgroundBrush(QBrush(Qt::gray));
}
