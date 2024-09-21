#include "falcon.h"
#include <math.h>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;


static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}



Falcon::Falcon(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    setRotation(0);                 //устанавливаем исходный разворот (0) в точке спавна

        target = QPointF(0,0);      //устанавливаем изначальное положение курсора
        shot = false;

        gameTimer = new QTimer();
                                    //сигнал от таймера + слот обработки игрового таймера
        connect(gameTimer, &QTimer::timeout, this, &Falcon::slotGameTimer);
        gameTimer->start(10);   // Стартуем таймер

        bulletTimer = new QTimer(); //таймер создания пуль
        connect(bulletTimer, &QTimer::timeout, this, &Falcon::slotBulletTimer);
        bulletTimer->start(1000/8); //8/сек
}



Falcon::~Falcon()
{

}



QRectF Falcon::boundingRect() const //границы юнита
{
    return QRectF(-16, -19, 33, 50);
}



void Falcon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) //кораблик
{
    QPolygon lwing;
    lwing << QPoint(-13, 7) << QPoint(-6, -18) << QPoint(-6, 7);
    painter -> setBrush(Qt::gray);
    painter -> setPen(Qt::gray);
    painter -> drawPolygon(lwing);

    QPolygon rwing;
    rwing << QPoint(13, 7) << QPoint(6, -18) << QPoint(6, 7);
    painter -> setBrush(Qt::gray);
    painter -> setPen(Qt::gray);
    painter -> drawPolygon(rwing);


    painter -> setPen(Qt::black);
    painter -> setBrush(Qt::gray);
    painter -> drawEllipse(-15, 0, 30, 30);

    painter -> setPen(Qt::black);
    painter -> setBrush(Qt::black);
    painter -> drawEllipse(-6, 6, 10, 10);


    Q_UNUSED(option);
    Q_UNUSED(widget);
}



void Falcon::slotTarget(QPointF point)
{
                //определить расстояние до цели
    target = point;
    QLineF lineToTarget(QPointF(0, 0), mapFromScene(target));
                //определить угол поворота до цели
    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = TwoPi - angleToTarget;
    angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);



    //в зависимости от того, слева или справа находится Цель от Героя, устанавливаем направление поворота Героя в данном тике таймера

    if (angleToTarget >= 0 && angleToTarget < Pi) {
                        //налево
        setRotation(rotation() - angleToTarget * 180 /Pi);
    } else if (angleToTarget <= TwoPi && angleToTarget > Pi) {
                        //направо
        setRotation(rotation() + (angleToTarget - TwoPi )* (-180) /Pi);
    }
}




void Falcon::slotGameTimer()
{
                //реакция на wsad (координаты)

    if(GetAsyncKeyState('A')){
        this->setX(this->x() - 2);
    }
    if(GetAsyncKeyState('D')){
        this->setX(this->x() + 2);
    }
    if(GetAsyncKeyState('W')){
        this->setY(this->y() - 2);
    }
    if(GetAsyncKeyState('S')){
        this->setY(this->y() + 2);
    }



                //проверка выхода за границы поля

    if(this->x() - 30 < 0){
        this->setX(30);                 //слева
    }
    if(this->x() + 30 > 500){
        this->setX(500 - 30);           //справа
    }

    if(this->y() - 30 < 0){
        this->setY(30);                 //сверху
    }
    if(this->y() + 30 > 500){
        this->setY(500 - 30);           //снизу
    }


    QLineF lineToTarget(QPointF(0, 0), mapFromScene(target));
                                         //угол поворота в направлении к цели
    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = TwoPi - angleToTarget;
    angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);

                                        //поворот в зависимости от расположения цели (по градусам наиболее короткий вариант) в одном тике

    if (angleToTarget >= 0 && angleToTarget < Pi) {
        // Rotate left
        setRotation(rotation() - angleToTarget * 180 /Pi);
    } else if (angleToTarget <= TwoPi && angleToTarget > Pi) {
        // Rotate right
        setRotation(rotation() + (angleToTarget - TwoPi )* (-180) /Pi);
    }
}



void Falcon::slotBulletTimer()
{

    if(shot) emit signalBullet(QPointF(this->x(),this->y()), target);       //если стрельба разрешена, вызываем сигнал на создание пули (от сигнала в слот)

}



void Falcon::slotShot(bool shot)
{
    this->shot = shot;  //получаем разрешение или запрет на стрельбу (от сигнала в слот)
}
