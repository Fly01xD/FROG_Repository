#include "gamescene.h"

#include <QKeyEvent>

GameScene::GameScene(gameDifficulty _diff)
    : logicRoad(new CRoad(_diff)), njump(0)
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

// metoda skakania pod przyciskiem
void GameScene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)
    {
        // najpierw logiczny skok żaby
        // i sprawdzenie z jakiego obiektu skoczyła
        roadInfrastructure newInf = logicRoad->jump(njump);

        // jeśli skoczyła z pasa rucu, to trzeba dodać kolejny pas ruchu
        // i usunąć ten, z którego skoczyła
        if(newInf == roadInfrastructure::lane)
        {
            // usuwanie dzieci pasa ruchu (pojazdóW i przejścia)
            for(auto c : laneItems[0]->childItems())
            {
                if(dynamic_cast<VehicleItem*>(c))
                {
                    // algorytm na usunięcie z vector konkretnej wartośći
                    vehicleItems.erase(
                        remove(vehicleItems.begin(), vehicleItems.end(), c)
                        ,vehicleItems.end());
                }
                else if(dynamic_cast<CrossingItem*>(c))
                {
                    crossingItems.erase(
                        remove(crossingItems.begin(), crossingItems.end(), c)
                        ,crossingItems.end());
                }
                removeItem(c);
                delete c;
            }
            removeItem(laneItems[0]);
            delete laneItems[0];
            laneItems.erase(laneItems.begin());


            // dodanie nowego pasa ruchu i jego dzieci (pojazdóW i przejścia)
            LaneItem* laneI = new LaneItem(logicRoad->getLanes().back());
            addItem(laneI);
            // trzeba jeszcze napisać rozmieszczenie nowego pasa
            laneItems.push_back(laneI);

            // dodawanie przejścia i pojazdóW
            CrossingItem* crosI =new CrossingItem(laneI, logicRoad->getLanes().back()->Crossing);
            addItem(crosI);
            // jeszcze trzeba napisać rozmieszczenie przejścia
            crossingItems.push_back(crosI);
            for(auto v : laneI->getLogicLane()->getVehicles())
            {
                VehicleItem* vehI = new VehicleItem(laneI, v);
                addItem(vehI);
                vehicleItems.push_back(vehI);
                // jeszcze trzeba napisać rozmieszczenie pojazdów
            }

            // !!!trzeba napisać wizualizację żaby na przejściu!!!
        }
        else if(newInf == roadInfrastructure::island)
        {
            // usuwanie wyspy, z której żaba skoczyła
            removeItem(islandItems[0]);
            delete islandItems[0];
            islandItems.erase(islandItems.begin());

            // dodanie wyspy
            IslandItem* isI = new IslandItem(logicRoad->getIslands().back());
            addItem(isI);
            islandItems.push_back(isI);

            // !!!trzeba napisać wizualizację żaby na wyspie!!!
        }
    }
}
