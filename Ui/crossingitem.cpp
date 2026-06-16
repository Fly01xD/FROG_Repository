#include "crossingitem.h"

CrossingItem::CrossingItem(CCrossing* _cros, QGraphicsPixmapItem* parent)
    : logicCrossing(_cros), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap("assets/crossing.png"));
    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2);
    //ustalamy wysokość przejścia z = 1 żeby był nad drogą
    setZValue(1);
}
