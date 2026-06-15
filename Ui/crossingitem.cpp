#include "crossingitem.h"

CrossingItem::CrossingItem(QGraphicsItem* parent, CCrossing* _cros)
    : logicCrossing(_cros), QGraphicsPixmapItem(parent)
{
    QPixmap pixmap("assets/crossing.png");

    //ustalamy wysokość przejścia z = 1 żeby był nad drogą
    setZValue(1);
}
