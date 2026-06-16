#include "laneitem.h"

LaneItem::LaneItem(CLane *_lane, QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent) , logicLane(_lane)
{
    //wczytywanie grafiki z folderu assets
    setPixmap(QPixmap("assets/lane.png"));
    //ustalamy wysokość pasa z = 0 żeby był drogą
    setZValue(0);
}
