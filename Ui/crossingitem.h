#ifndef CROSSINGITEM_H
#define CROSSINGITEM_H

#include "ccrossing.h"
#include <QGraphicsPixmapItem>

class CrossingItem : public QGraphicsPixmapItem
{
    CCrossing* logicCrossing;
public:
    CrossingItem(QGraphicsItem* parent, CCrossing* _cros);
};

#endif // CROSSINGITEM_H
