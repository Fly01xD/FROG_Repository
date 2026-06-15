#ifndef LANEITEM_H
#define LANEITEM_H

#include "CLane.h"
#include <QGraphicsPixmapItem>

class LaneItem : public QGraphicsPixmapItem
{
    CLane* logicLane;
public:
    LaneItem(CLane* _lane, QGraphicsItem* parent = nullptr);

    //getter i setter logiki Lane'a
    void setLogicLane(CLane* _newLane)
    {
        logicLane = _newLane;
    }
    CLane* getLogicLane() const {return logicLane;}
};

#endif // LANEITEM_H
