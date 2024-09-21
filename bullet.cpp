#include "bullet.h"
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



Bullet::Bullet(QPointF start, QPointF end, QGraphicsItem * hero, QObject *parent)
    : QObject(parent), QGraphicsItem()
{
    this->hero = hero;                  //присваиваем и запоминаем
    this->setRotation(0);               //устанавливаем начальный разворот
    this->setPos(start);


    QLineF lineToTarget(start, end);    //определяем траекторию полёта пули

    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());    //угол поворота в направлении к цели
    if (lineToTarget.dy() < 0)
        angleToTarget = TwoPi - angleToTarget;
    angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);

                                        //поворачиваем (зависит от нынешнего угла)
    if (angleToTarget >= 0 && angleToTarget < Pi) {
        /// Rotate left
        setRotation(rotation() - angleToTarget * 180 /Pi);
    } else if (angleToTarget <= TwoPi && angleToTarget > Pi) {
        /// Rotate right
        setRotation(rotation() + (angleToTarget - TwoPi )* (-180) /Pi);
    }

                                        //таймер полета пули
    timerBullet = new QTimer();
    connect(timerBullet, &QTimer::timeout, this, &Bullet::slotTimerBullet);
    timerBullet->start(7);
}



Bullet::~Bullet()
{

}



QRectF Bullet::boundingRect() const  //границы юнита
{
    return QRectF(0,0,2,4);
}



void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) //отрисовка выстрела
{
    painter -> setPen(Qt::blue);
    painter -> setBrush(Qt::blue);
    painter -> drawRect(0, 0, 3, 6);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}



void Bullet::slotTimerBullet()
{
    setPos(mapToParent(0, -10));


    //выделяем область перед выстрелом, в нем смотрим, наткнулся ли он на объект
    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                           << mapToScene(0, 0)
                                                           << mapToScene(-1, -1)
                                                           << mapToScene(1, -1));


    //проверяем элементы, если элемент на который мы наткнулись - юнит
    foreach (QGraphicsItem *item, foundItems) {
        if (item == this || item == hero)
            continue;
        callbackFunc(item);     // Вызываем CallBack функцию
        this->deleteLater();    // Уничтожаем пулю
    }


             //если выстрел выходит за границы
    if(this->x() < 0){
        this->deleteLater();
    }
    if(this->x() > 500){
        this->deleteLater();
    }

    if(this->y() < 0){
        this->deleteLater();
    }
    if(this->y() > 500){
        this->deleteLater();
    }
}

            //вызываем функцию
void Bullet::setCallbackFunc(void (*func)(QGraphicsItem *))
{
    callbackFunc = func;
}
