#include "laneitem.h"

LaneItem::LaneItem(CLane *_lane)
    : logicLane(_lane)
{}

CLane *LaneItem::getLogicLane() {return logicLane;}
