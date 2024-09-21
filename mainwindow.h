#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QDebug>

#include <falcon.h>
#include <customscene.h>
#include <bullet.h>
#include <starfighter.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CustomScene  *scene;
    Falcon *triangle;
    QTimer *timerTarget;    //таймер для создания мишеней


    static QList<QGraphicsItem *> targets;          // список истребители

    static void slotHitTarget(QGraphicsItem *item); // callback

private slots:
    void slotBullet(QPointF start, QPointF end);    // это создает снаряды
    void slotCreateTarget();                        // это создает истребители

};

#endif

