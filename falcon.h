#ifndef FALCON_H
#define FALCON_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPolygon>
#include <QTimer>
#include <QDebug>
#include <QCursor>

#include <windows.h>

class Falcon : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Falcon(QObject *parent = 0);
    ~Falcon();


signals:

    void signalBullet(QPointF start, QPointF end);      //сигналы для пули

public slots:
    void slotTarget(QPointF point);     //получение данных о координатах курсора
    void slotShot(bool shot);           //разрешение на стрельбу


private:
    QRectF boundingRect() const;        //ограничивает пространство вокруг юнита
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //рисует


private slots:
    void slotGameTimer();       //игровой слот
    void slotBulletTimer();     //слот проверки пули


private:
    bool shot;                  //состояние стрельбы
        QTimer *bulletTimer;    //таймер стрельбы
        QTimer *gameTimer;      //игровой таймер
        QPointF target;         //положение курсора
};

#endif // FALCON_H
