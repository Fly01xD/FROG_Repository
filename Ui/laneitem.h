#ifndef LANEITEM_H
#define LANEITEM_H

#include "CLane.h"
#include <QGraphicsPixmapItem>

class LaneItem : public QGraphicsPixmapItem
{
    CLane* logicLane;
public:
    LaneItem(CLane* _lane, QGraphicsItem* parent = nullptr) : QGraphicsPixmapItem(parent)
    {
        //wczytywanie grafiki z folderu assets
        setPixmap(QPixmap("assets/lane.png"));
    }
    //getter
    CLane* getLogicLane();
    void setLogicLane(CLane* _newLane) {
        logicLane = _newLane;
    }
};

#endif // LANEITEM_H
