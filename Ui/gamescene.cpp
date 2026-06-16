#include "gamescene.h"
#include "cplayerbase.h"
#include "croad.h"
#include "CLane.h"
#include "cisland.h"

#include <QKeyEvent>

GameScene::GameScene(QObject* parent, CRoad* _road, gameDifficulty _diff, CPlayerBase *_player)
    : QGraphicsScene(parent), logicRoad(_road), player(_player)
{
    synchLogic(_diff);
}

GameScene::~GameScene()
{
    //metoda w QGraphicsScene, która niszczy wszystko
    clear();

    //kod który był wcześniej (jakbyś uznał, że wolisz poprzednią wersję):

    // usuwanie dzieci, pasy i samochody
    // for(auto l : laneItems)
    // {
    //     for(auto c : l->childItems()) {
    //         removeItem(c);
    //         delete c;
    //     }
    //     laneItems.erase(laneItems.begin());
    //     removeItem(l);
    //     delete l;
    // }
    // // usuwanie dzieci, wyspy i żaba
    // for(auto i : islandItems)
    // {
    //     for(auto c : i->childItems()) {
    //         removeItem(c);
    //         delete c;
    //     }
    //     islandItems.erase(islandItems.begin());
    //     removeItem(i);
    //     delete i;
    // }
}
// metoda do podłączenia ItemóW graficznych do klas logicznych
// oraz dodania ich na scenę i zrobienie rodziecielstwa
void GameScene::synchLogic(gameDifficulty _diff)
{
    //niszczenie starych danych na wrazie gdyby dalej jakieś istaniły, sprawdzenie czy scena jest pusta
    clear();
    laneItems.clear();
    islandItems.clear();
    frogItem = nullptr;

    //zbieramy wyspy i pasy
    std::vector<CLane*> logicLanes = logicRoad->getLanes();
    std::vector<CIsland*> logicIslands = logicRoad->getIslands();

    //bierzące wymiary ekranu
    qreal screenH = sceneRect().height();
    qreal rowHeight = screenH/4.0;

    int currentRowIndex = 0;

    //rysowanie pasów ruchu i ich dzieci czyli pojazdów i crossingów
    for(auto l : logicRoad->getLanes())
    {
        LaneItem* laneI = new LaneItem(l);
        addItem(laneI);
        laneItems.push_back(laneI);

        //rysowanie pasów ruchu:
        laneI->setPos(0, currentRowIndex * rowHeight);

        //pobiera dane o ilości pixeli szerokości pliku lane.png
        qreal laneW = laneI->pixmap().width();

        if(l->Crossing)
        {
            //przekazujemy konkretnego lena jako parenta konkretnego crossingu
            CrossingItem* crosI = new CrossingItem(l->Crossing, laneI);
            crosI->setPos(laneW / 2.0, 0); // Środek pasa w lokalnych współrzędnych
        }
        for(auto v : l->getVehicles())
        {
            //losowanie co ma się narysować
            if(dynamic_cast<CCar*>(v))
            {
                //przekazujemy jako parennta laneI i dlatego pojazd będzie się skalował, poruszał
                //oraz usuwał razem z lanem
                VehicleItem* vehI = new VehicleItem(v, EVehicleType::Car, laneI);
                vehI->setX((v->getPosition()/200.0)*laneW);
            }
            else if(dynamic_cast<CMotor*>(v))
            {
                VehicleItem* vehI = new VehicleItem(v, EVehicleType::Motorcycle, laneI);
                vehI->setX((v->getPosition()/200.0)*laneW);
            }
        }
        currentRowIndex++;
    }
    //rysowanie wysp
    for(auto is : logicRoad->getIslands())
    {
        IslandItem* isI = new IslandItem(is);
        addItem(isI);
        islandItems.push_back(isI);

        isI->setPos(0,currentRowIndex * rowHeight);

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
    update();
}
//update silnika
void GameScene::drawGame()
{
    //przechodzimy przez każdy pas
    for (LaneItem* lane : laneItems)
    {
        //laneW = ilość pixeli szerogości pliku lane.png (1024 chyba)
        qreal laneW = lane->pixmap().width();

        //sprawdzenie wszystkich dzieci lane'a
        for(auto child : lane->childItems())
        {
            if(VehicleItem* visVehicle = dynamic_cast<VehicleItem*>(child))
            {
                //aktualizacja pozycji samochodu zgodna z logiką
                CVehicle* logic = visVehicle->getLogicVehicle();
                if (logic) {
                    visVehicle->setX((logic->getPosition() / 200.0) * laneW);
                }
            }
        }
    }
    update();
}
// skakanie żaby
void GameScene::moveGame()
{
    qreal screenH = sceneRect().height();
    qreal rowHeight = screenH / 4.0; // Wysokość jednego rzędu

    //przesunięcie pasów w dół
    for (LaneItem* lane : laneItems)
    {
        lane->setY(lane->y() + rowHeight);
        //zmienienie właśnie usuniętego pasu na ten który właśnie wszedł na ekran
        //(szukanie pasa, który spadł)
        if (lane->y() >= screenH)
        {
            lane->setY(0);
            //przypisanie logiki lane który właśnie wszedł na ekran
            //do lane który właśnie wyszedł za ekran
            CLane* newLogicLane = logicRoad->getLanes().back();
            lane->setLogicLane(newLogicLane);

            //usunięcie wszystkich dzieci lane'a
            qDeleteAll(lane->childItems());

            qreal laneW = lane->pixmap().width();

            //tworzenie nowych obiektów graicznych na podstawie logiki
            if (newLogicLane->Crossing)
            {
                CrossingItem* crosI = new CrossingItem(newLogicLane->Crossing, lane);
                crosI->setPos((laneW/2.0), 0);
            }
            for(auto v : newLogicLane->getVehicles())
            {
                if(dynamic_cast<CCar*>(v))
                {
                    VehicleItem* vehI = new VehicleItem(v, EVehicleType::Car, lane);
                    vehI->setX((v->getPosition()/200.0)*laneW);
                }
                else if(dynamic_cast<CMotor*>(v))
                {
                    VehicleItem* vehI = new VehicleItem(v, EVehicleType::Motorcycle, lane);
                    vehI->setX((v->getPosition()/200.0)*laneW);
                }
            }
        }
    }
    //przesunięcię wyspy w dół
    for (IslandItem* island : islandItems)
    {
        island->setY(island->y() + rowHeight);

        if (island->y() >= screenH)
        {
            island->setY(0);
            CIsland* newLogicIsland = logicRoad->getIslands().back();
            island->setLogicIsland(newLogicIsland);
        }
    }
    update();
}
void GameScene::updateScaling(qreal windowWidth, qreal windowHeight)
{
    setSceneRect(0, 0, windowWidth, windowHeight);

    //dzielimy wysokość całego obecnie ekranu na 4 i tak dostajemy
    //wysokość jednego rzędu
    qreal rowHeight = windowHeight/4.0;

    //skalowanie pasów, ponieważ pas jest parentem pojazdów i crossingów
    //to pojazdy i crossingi odrazu są skalowane
    for (LaneItem* lane : laneItems)
    {
        if (lane && !lane->pixmap().isNull())
        {
            //tutaj liczmy skale, dzielimy wymiar okna na ilość pixeli pliku png
            qreal scaleX = windowWidth / lane->pixmap().width();
            qreal scaleY = rowHeight / lane->pixmap().height();

            //nakładamy tą skalę na pas (przy okazji na pojazd i crossing)
            lane->setTransform(QTransform::fromScale(scaleX, scaleY));
        }
    }
    //skalowanie wyspy (działa tak samo jak wyżej)
    for (IslandItem* island : islandItems)
    {
        if (island && !island->pixmap().isNull())
        {
            qreal scaleX = windowWidth / island->pixmap().width();
            qreal scaleY = rowHeight / island->pixmap().height();
            island->setTransform(QTransform::fromScale(scaleX, scaleY));
        }
    }
    //skalowanie żaby
    if (frogItem && !frogItem->pixmap().isNull())
    {
        qreal frogSize = rowHeight * 0.6;
        qreal scaleXY = frogSize / frogItem->pixmap().width();
        frogItem->setTransform(QTransform::fromScale(scaleXY, scaleXY));

        //ustawiamy żabę w odpowiednim miejscu
        qreal frogFixedX = (windowWidth / 2.0) - (frogSize / 2.0);
        qreal frogFixedY = windowHeight - rowHeight + ((rowHeight - frogSize) / 2.0);
        frogItem->setPos(frogFixedX, frogFixedY);
    }
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
    QGraphicsScene::keyPressEvent(event);
}


