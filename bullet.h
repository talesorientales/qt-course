#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QPainter>
#include <QDebug>



class Bullet : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:     //ставим callback функцию (в буллет.спп при попадании удаляется)
    explicit Bullet(QPointF start, QPointF end, QGraphicsItem *hero, QObject *parent = 0);
    ~Bullet();
    void setCallbackFunc(void (*func) (QGraphicsItem * item));

signals:


public slots:

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);     //рисует


    void (*callbackFunc)(QGraphicsItem * item);     //объявляем сигнатуру CallBack функции


private:
    QTimer *timerBullet;    //таймер пули
    QGraphicsItem *hero;
private slots:
    void slotTimerBullet(); //обработка полета пули
};

#endif // BULLET_H
