#ifndef ISLANDITEM_H
#define ISLANDITEM_H

#include "cisland.h"
#include <QGraphicsPixmapItem>

class IslandItem : public QGraphicsPixmapItem
{
    CIsland* logicIsland;
public:
    IslandItem(CIsland* _island, QGraphicsItem* parent = nullptr) : QGraphicsPixmapItem(parent)
    {
        setPixmap(QPixmap("assets/island.png"));
    }
};

#endif // ISLANDITEM_H
