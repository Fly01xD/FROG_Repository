#include "crossingitem.h"

CrossingItem::CrossingItem(QGraphicsItem* parent, CCrossing* _cros)
    : logicCrossing(_cros), QGraphicsPixmapItem(parent)
{}
