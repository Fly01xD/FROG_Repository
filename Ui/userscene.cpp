#include "userscene.h"
#include <qevent.h>

UserScene::UserScene(gameDifficulty _diff)
    : GameScene(_diff)
{}

UserScene::~UserScene()
{}

// metoda skakania pod przyciskiem
void UserScene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)
    {
        // najpierw logiczny skok żaby
        // i sprawdzenie z jakiego obiektu skoczyła
        roadInfrastructure newInf = getLogicRoad()->jump(getNjump());
        // jeśli skoczyła z pasa rucu, to trzeba dodać kolejny pas ruchu
        // i usunąć ten, z którego skoczyła
        if(newInf == roadInfrastructure::lane)
        {
            // usuwanie dzieci pasa ruchu (pojazdóW i przejścia)
            for(auto c : getLaneItems()[0]->childItems())
            {
                if(dynamic_cast<VehicleItem*>(c))
                {
                    // algorytm na usunięcie z vector konkretnej wartośći
                    auto& vehicles = getVehicleItems();
                    vehicles.erase(
                        remove(vehicles.begin(), vehicles.end(), c)
                        ,vehicles.end());
                }
                else if(dynamic_cast<CrossingItem*>(c))
                {
                    auto& crossings = getCrossingItems();
                    crossings.erase(
                        remove(crossings.begin(), crossings.end(), c)
                        ,crossings.end());
                }
                removeItem(c);
                delete c;
            }
            removeItem(getLaneItems()[0]);
            delete getLaneItems()[0];
            getLaneItems().erase(getLaneItems().begin());

            // dodanie nowego pasu ruchu i jego dzieci (pojazdóW i przejścia)
            LaneItem* laneI = new LaneItem(getLogicRoad()->getLanes().back());
            addItem(laneI);
            // trzeba jeszcze napisać rozmieszczenie nowego pasu
            getLaneItems().push_back(laneI);

            // dodawanie przejścia i pojazdóW
            CrossingItem* crosI = new CrossingItem(laneI, getLogicRoad()->getLanes().back()->Crossing);
            addItem(crosI);
            // jeszcze trzeba napisać rozmieszczenie przejścia
            getCrossingItems().push_back(crosI);

            for(auto v : laneI->getLogicLane()->getVehicles())
            {
                VehicleItem* vehI = new VehicleItem(laneI, v);
                addItem(vehI);
                getVehicleItems().push_back(vehI);
                // jeszcze trzeba napisać rozmieszczenie pojazdów
            }
            // !!!trzeba napisać wizualizację żaby na przejściu!!!
        }
        else if(newInf == roadInfrastructure::island)
        {
            // usuwanie wyspy, z której żaba skoczyła
            removeItem(getIslandItems()[0]);
            delete getIslandItems()[0];
            getIslandItems().erase(getIslandItems().begin());

            // dodanie wyspy
            IslandItem* isI = new IslandItem(getLogicRoad()->getIslands().back());
            addItem(isI);
            getIslandItems().push_back(isI);
            // !!!trzeba napisać wizualizację żaby na wyspie!!!
        }
    }
}