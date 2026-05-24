#ifndef ISLANDITEM_H
#define ISLANDITEM_H

#include "cisland.h"
#include <QGraphicsPixmapItem>

class IslandItem : public QGraphicsPixmapItem
{
    CIsland* logicIsland;
public:
    IslandItem(CIsland* _island);
};

#endif // ISLANDITEM_H
