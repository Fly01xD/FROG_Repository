#include "islanditem.h"

IslandItem::IslandItem(CIsland* _island, QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent), logicIsland(_island)
{
    setPixmap(QPixmap("assets/island.png"));
    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2);
    //ustalamy wysokość wyspy z = 0 żeby była drogą
    setZValue(0);
}
