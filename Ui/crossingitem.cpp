#include "crossingitem.h"

CrossingItem::CrossingItem(CCrossing* _cros, QGraphicsPixmapItem* parent)
    : logicCrossing(_cros), QGraphicsPixmapItem(parent)
{
    QPixmap pixmap("assets/crossing.png");

    //ustalamy wysokość przejścia z = 1 żeby był nad drogą
    setZValue(1);
}
