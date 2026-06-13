#include "gamescene.h"
#include "cplayerbase.h"

#include <QKeyEvent>

GameScene::GameScene(gameDifficulty _diff, CPlayerBase *_player)
    : logicRoad(new CRoad(_diff)), player(_player)
{
    synchLogic();
}

GameScene::~GameScene()
{
    // usuwanie dzieci, pasy i samochody
    for(auto l : laneItems)
    {
        for(auto c : l->childItems()) {
            removeItem(c);
            delete c;
        }
        laneItems.erase(laneItems.begin());
        removeItem(l);
        delete l;
    }
    // usuwanie dzieci, wyspy i żaba
    for(auto i : islandItems)
    {
        for(auto c : i->childItems()) {
            removeItem(c);
            delete c;
        }
        islandItems.erase(islandItems.begin());
        removeItem(i);
        delete i;
    }
}



// metoda do podłączenia ItemóW graficznych do klas logicznych
// oraz dodania ich na scenę i zrobienie rodziecielstwa
void GameScene::synchLogic()
{
    for(auto l : logicRoad->getLanes())
    {
        LaneItem* laneI = new LaneItem(l);
        addItem(laneI);
        laneItems.push_back(laneI);
        // jeszcze trzeba napisać rozmieszczenie pasóW

        // dodanie przejścia do sceny
        CrossingItem* crosI = new CrossingItem(laneI, l->Crossing);
        addItem(crosI);
        crossingItems.push_back(crosI);
        // jeszcze trzeba napisać rozmieszczenie przejść

        // dodanie pojazdów do sceny
        for(auto v : l->getVehicles())
        {
            VehicleItem* vehI = new VehicleItem(laneI, v);
            addItem(vehI);
            vehicleItems.push_back(vehI);
            // jeszcze trzeba napisać rozmieszczenie pojazdóW
        }
    }
    for(auto is : logicRoad->getIslands())
    {
        IslandItem* isI = new IslandItem(is);
        addItem(isI);
        islandItems.push_back(isI);
        // trzeba jeszcze napisać rozmieszczenie wysp
        if(is->getFrog())
        {
            // dodanie żaby do sceny
            FrogItem* frogI = new FrogItem(is->getFrog());
            addItem(frogI);
            frogItem = frogI;
        }
    }
}

frogState GameScene::updateGame()
{
    return logicRoad->updateGame(1);
}
// metoda skakania pod przyciskiem
void GameScene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)
    {
        player->jumpOnKey();
    }
}

