#include "islanditem.h"

IslandItem::IslandItem(CIsland* _island, QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent), logicIsland(_island)
{
    setPixmap(QPixmap("assets/island.png"));
}
