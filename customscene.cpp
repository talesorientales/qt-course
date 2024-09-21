#include "customscene.h"

CustomScene::CustomScene(QObject *parent) :
    QGraphicsScene()
{
    Q_UNUSED(parent);
}


CustomScene::~CustomScene()
{

}


void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalTargetCoordinate(event->scenePos());
}


void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalShot(true);  //стрелять, когда зажата пкм
    Q_UNUSED(event);
}


void CustomScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalShot(false); //не стрелять, когда не нажата пкм
    Q_UNUSED(event);
}
