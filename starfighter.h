#ifndef STARFIGHTER_H
#define STARFIGHTER_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>



class Starfighter : public QObject, public QGraphicsItem        //нанесение урона
{
    Q_OBJECT
public:
    explicit Starfighter(QObject *parent = 0);
    ~Starfighter();
    void hit(int damage);


signals:


public slots:


protected:      //сигнал для отрисовки
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


private:        // хп юнитов
    int health;
    int maxHealth;
};


#endif // STARFIGHTER_H
