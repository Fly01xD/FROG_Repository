#include "gamescene.h"
#include "cplayerbase.h"

#include <QKeyEvent>

GameScene::GameScene(QObject* parent, CRoad* _road, gameDifficulty _diff, CPlayerBase *_player)
    : logicRoad(_road), player(_player)
{
    synchLogic(_diff);
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
void GameScene::synchLogic(gameDifficulty _diff)
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
            // ustawienie dla żaby poziomu trudności
            is->getFrog()->setHP(_diff+1);
            // dodanie żaby do sceny
            FrogItem* frogI = new FrogItem(is->getFrog());
            addItem(frogI);
            frogItem = frogI;
        }
    }
}

void GameScene::drawGame()
{
    // TRZEBA NAPISAĆ RYSOWANIE ITEMÓW
}

void GameScene::moveGame()
{
    // TRZEBA NAPISAĆ RYSOWANIE RUCHU OTOCZENIA WOKÓŁ ŻABY
}

void GameScene::unPauseAI()
{
    player->playerAIPause();
}

// metoda skakania pod przyciskiem
void GameScene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)
    {
        player->jumpOnKey();
    }
    if(event->key() == Qt::Key_Escape)
    {
        logicRoad->gamePause();
        player->playerAIPause();
    }
}

