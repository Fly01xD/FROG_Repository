#ifndef LANEITEM_H
#define LANEITEM_H

#include "CLane.h"
#include <QGraphicsPixmapItem>

class LaneItem : public QGraphicsPixmapItem
{
    CLane* logicLane;
public:
    LaneItem(CLane* _lane);

    //getter
    CLane* getLogicLane();
};

#endif // LANEITEM_H
