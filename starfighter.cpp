#include "starfighter.h"

static int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}



Starfighter::Starfighter(QObject *parent) :
    QObject(parent), QGraphicsItem()        //рандомное 1-15 хп, оно же максимальное
{
    health = randomBetween(1,15);
    maxHealth = health;
}



Starfighter::~Starfighter()
{

}



QRectF Starfighter::boundingRect() const
{
    return QRectF(-20,-20,40,40);   //границы юнита
}



void Starfighter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)  //юниты
{
    //истребитель
    painter->setPen(Qt::black);
    painter->setBrush(Qt::gray);
    painter->drawRect(7, 5, 10, 4);

    painter->setPen(Qt::black);
    painter->setBrush(Qt::gray);
    painter->drawRect(13, 0, 4, 14);


    painter->setPen(Qt::black);
    painter->setBrush(Qt::gray);
    painter->drawRect(-15, 5, 10, 4);

    painter->setPen(Qt::black);
    painter->setBrush(Qt::gray);
    painter->drawRect(-19, 0, 4, 14);

            ///окружность
    painter->setPen(Qt::black);
    painter->setBrush(Qt::gray);
    painter->drawEllipse(-10, -3, 18, 18);

    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);
    painter->drawEllipse(-5, 2, 8, 8);


    //хп бар
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    painter->drawRect(-20,-20, (int) 40*health/maxHealth,3);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}



void Starfighter::hit(int damage)
{
    health -= damage;   // минус хп бар при попадании
    this->update(QRectF(-20,-20,40,40));
    if(health <= 0)  this->deleteLater();


}
