#include "mainwindow.h"
#include "starfighter.h"
#include "ui_mainwindow.h"


static int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}


MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)

{

    this->resize(700,700); //окно
    this->setFixedSize(700,700);

    ui->setupUi(this);
    scene=new CustomScene();   //инициализировать кастом сцену


    ui->graphicsView->setScene(scene);  //set graphicsview widget

    scene->setSceneRect(0, 0, 600, 600);   //размеры виджета graphics view

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // сглаживание
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);



    QPixmap m_pixmap = QPixmap("://resources/cursor.png");    //курсор
    QCursor m_cursor = QCursor(m_pixmap);
    ui -> graphicsView -> setCursor(m_cursor);



    triangle = new Falcon();  //корабль на сцену
    triangle -> setPos(250,250);
    scene -> addItem(triangle);



    ui->graphicsView->setMouseTracking(true);   //разрешить юниту следить за курсором (без  нажатия кнопки мышки) на gv



    connect(scene, &CustomScene::signalTargetCoordinate, triangle, &Falcon::slotTarget);        //сигнал от графической сцены + слоту сокола

    connect(scene, &CustomScene::signalShot, triangle, &Falcon::slotShot);                      //сигнала стрельбы с графической сцены + слот разрешения стрельбы

    connect(triangle, &Falcon::signalBullet, this, &MainWindow::slotBullet);                    //сигнал на создание пули + слот содания выстрелов


        timerTarget = new QTimer();     //таймер для создания мишеней
        connect(timerTarget, &QTimer::timeout, this, &MainWindow::slotCreateTarget);
        timerTarget->start(1500);
}





MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::slotBullet(QPointF start, QPointF end)     //пулю на граф сцену
{
    Bullet *bullet = new Bullet(start, end, triangle);
    bullet->setCallbackFunc(slotHitTarget);
    scene->addItem(bullet);
}



void MainWindow::slotCreateTarget()     //здесь устанавливаем юниты целей как цели
{
    Starfighter *target = new Starfighter();
    scene->addItem(target);         //координата рандомная
    target->setPos(qrand() % ((600 - 40 + 1) - 40) + 40,
                  qrand() % ((600 - 40 + 1) - 40) + 40);
    target->setZValue(-1);
    targets.append(target);         //занести в лист целей
}



void MainWindow::slotHitTarget(QGraphicsItem *item)     //когда выстрел касается болванки, перебираем значение на урон между 1-3
{
    foreach (QGraphicsItem *targ, targets) {
        if(targ == item){           // то что в листе заносится в класс Target
            Starfighter *t = qgraphicsitem_cast <Starfighter *> (targ);
            t->hit(randomBetween(1,3));
        }
    }

}


QList<QGraphicsItem *> MainWindow::targets; // реализация списка
