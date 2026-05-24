#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "laneitem.h"
#include "crossingitem.h"
#include "vehicleItem.h"
#include "FrogItem.h"
#include "IslandItem.h"
#include "croad.h"
#include <QGraphicsScene>

class GameScene : public QGraphicsScene
{
    // logika sceny
    CRoad* logicRoad;
    // zmienna do skakania (nie wiem jak inaczej to zrobić)
    unsigned njump;

    // Graphics items (dzieci sceny)
    std::vector<LaneItem*> laneItems;
    std::vector<IslandItem*> islandItems;
    std::vector<CrossingItem*> crossingItems;
    std::vector<VehicleItem*> vehicleItems;
    FrogItem* frogItem;
public:
    GameScene(gameDifficulty _diff);
    ~GameScene();

    // synchronizacja logiki z ui
    void synchLogic();
    // skakanie żaby
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // GAMESCENE_H
