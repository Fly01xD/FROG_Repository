#ifndef ISLANDITEM_H
#define ISLANDITEM_H

#include "cisland.h"
#include <QGraphicsPixmapItem>

class IslandItem : public QGraphicsPixmapItem
{
    CIsland* logicIsland;
public:
    IslandItem(CIsland* _island, QGraphicsItem* parent = nullptr);

    //getter i setter logiki wyspy
    void setLogicIsland(CIsland* _newIsland) { logicIsland = _newIsland; }
    CIsland* getLogicIsland() const { return logicIsland; }
};

#endif // ISLANDITEM_H
