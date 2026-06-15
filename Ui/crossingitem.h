#ifndef CROSSINGITEM_H
#define CROSSINGITEM_H

#include "ccrossing.h"
#include <QGraphicsPixmapItem>

class CrossingItem : public QGraphicsPixmapItem
{
    CCrossing* logicCrossing;
public:
    CrossingItem(CCrossing* _cros, QGraphicsPixmapItem* parent = nullptr);
};

#endif // CROSSINGITEM_H
