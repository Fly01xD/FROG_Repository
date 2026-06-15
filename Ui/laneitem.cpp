#include "laneitem.h"

LaneItem::LaneItem(CLane *_lane, QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent) , logicLane(_lane)
{
    //wczytywanie grafiki z folderu assets
    setPixmap(QPixmap("assets/lane.png"));
}
