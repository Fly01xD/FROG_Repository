#include "gamescene.h"
#include "cplayerbase.h"
#include "croad.h"
#include "CLane.h"
#include "cisland.h"

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
    //niszczenie starych danych na wrazie gdyby dalej jakieś istaniły, sprawdzenie czy scena jest pusta
    for (QGraphicsPixmapItem* row : m_mapRows) {
        removeItem(row);
        delete row;
    }
    m_mapRows.clear();

    if (frogItem) {
        removeItem(frogItem);
        delete frogItem;
    }

    //zbieramy wyspy i pasy
    std::vector<CLane*> logicLanes = logicRoad->getLanes();
    std::vector<CIsland*> logicIslands = logicRoad->getIslands();

    //bierzące wymiary ekranu
    qreal screenW = sceneRect().width();
    qreal screenH = sceneRect().height();

    qreal rowHeight = screenH/4.0;

    int currentRowIndex = 0;

    for(auto l : logicRoad->getLanes())
    {
        LaneItem* laneI = new LaneItem(l);
        addItem(laneI);
        laneItems.push_back(laneI);

        //rysowanie pasów ruchu:
        laneI->setPos(0, currentRowIndex * rowHeight);

        if(l->Crossing)
        {
            //umieszczenie przejścia dla pieszych
            CrossingItem* crosI = new CrossingItem(laneI, l->Crossing);
            addItem(crosI);
            crossingItems.push_back(crosI);
            crosI->setPos((screenW / 2.0), 0);
        }
        CrossingItem* crosI = new CrossingItem(laneI, l->Crossing);
        addItem(crosI);
        crossingItems.push_back(crosI);
        // jeszcze trzeba napisać rozmieszczenie przejść

        // dodanie pojazdów do sceny
        for(auto v : l->getVehicles())
        {
            //losowanie co ma się narysować
            EVehicleType randType = (QRandomGenerator::global()->bounded(2) == 0) ? EVehicleType::Car : EVehicleType::Motorcycle;

            VehicleItem* vehI = new VehicleItem(v, randType, laneI);
            addItem(vehI);
            vehicleItems.push_back(vehI);
            // jeszcze trzeba napisać rozmieszczenie pojazdóW
            vehI->setX(v->/*tu trzeba wpisać coś co będzie podawało pozycje samochodu z logiki chyba observer*/());
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
}
//update silnika
void GameScene::drawGame()
{
    //przechodzimy przez każdy pas
    for (LaneItem* visualRow : m_mapRows)
    {
        //przechodzimy przez każdy samochód
        for (VehicleItem* visVehicle : vehicleItems)
        {
            //jesli obrazek istenieje i ma podpiętą logikę to sprwadzamy jego pozycje
            if (visVehicle && visVehicle->getLogicVehicle() != nullptr)
            {
                //wskaźnik na logikę
                CVehicle* logic = visVehicle->getLogicVehicle();
                //ustawienie pozycji x obrazka pojazdu na podstawie logiki
                visVehicle->setX(logic->getPosition());
            }
        }
    }
}

void GameScene::moveGame()
{
    qreal screenW = sceneRect().width();
    qreal screenH = sceneRect().height();
    qreal rowHeight = screenH / 4.0; // Wysokość jednego rzędu

    //przesunięcie pasów w dół
    for (LaneItem* lane : laneItems)
    {
        lane->setY(lane->y() + rowHeight);
    }
    //przesunięcie wysp w dół
    for (IslandItem* island : islandItems)
    {
        island->setY(island->y() + rowHeight);
    }

    //zmienienie właśnie usuniętego pasu na ten który właśnie wszedł na ekran
    //(szukanie pasa, który spadł)
    for (LaneItem* lane : laneItems)
    {
        // jeśli pas wypadł za ekran to teleportujemy go na samą górę
        if (lane->y() >= screenH)
        {
            lane->setY(0);
        }
        //przypisanie logiki lane który właśnie wszedł na ekran
        //do lane który właśnie wyszedł za ekran
        CLane* newLogicLane = logicRoad->getLanes().back();
        lane->setLogicLane(newLogicLane);

        //czyszczenie samochodów, które były na pasie który został usunięty

        for (auto item : lane->childItems())
        {
            removeItem(item);
            delete item;
        }

        //tworzenie nowych obiektów graicznych na podstawie logiki
        if (newLogicLane->Crossing)
        {
            CrossingItem* crosI = new CrossingItem(lane, newLogicLane->Crossing);
            crosI->setPos(newLogicLane->Crossing->((screenW/2.0), 0));
        }

        for(auto v : newLogicLane->getVehicles())
        {
            EVehicleType randType = (QRandomGenerator::global()->bounded(2) == 0) ? EVehicleType::Car : EVehicleType::Motorcycle;
            VehicleItem* vehI = new VehicleItem(v, randType, lane);
            vehI->setX(v->getPosition());
        }

        break; // Znaleźliśmy i obsłużyliśmy pas, wychodzimy z pętli

    }
}

void GameScene::updateScaling(qreal windowWidth, qreal windowHeight)
{
    setSceneRect(0, 0, windowWidth, windowHeight);

    //dzielimy wysokość całego obecnie ekranu na 4 i tak dostajemy
    //wysokość jednego rzędu
    qreal rowHeight = windowHeight/4.0;

    for (size_t i = 0; i < m_mapRows.size(); ++i)
    {
        LaneItem* row = m_mapRows[i];
        if (row && !row->pixmap().isNull())
        {
            qreal scaleX = windowWidth / row->pixmap().width();
            qreal scaleY = rowHeight / row->pixmap().height();
            row->setTransform(QTransform::fromScale(scaleX, scaleY));

            // Ustawiamy pasy w pionie jeden pod drugim
            row->setPos(0, i * rowHeight);
        }
        if (frogItem && !frogItem->pixmap().isNull())
        {
            // Żaba zajmuje 60% wysokości pasa nie wiem jak to będzie wyglądało
            //więc możliwe że będzie trzeba to zmienić
            qreal frogSize = rowHeight * 0.6;
            qreal scaleXY = frogSize / frogItem->pixmap().width();
            frogItem->setTransform(QTransform::fromScale(scaleXY, scaleXY));

            //Żaba musi być na środku więc bierzemy obecną wielgość okna i ją na dwa
            qreal frogFixedX = (windowWidth / 2.0) - (frogSize / 2.0);

            // Ustawiamy na wysokości najniższego rzędu, wyśrodkowane w jego osi Y
            qreal frogFixedY = windowHeight - rowHeight + ((rowHeight - frogSize) / 2.0);

            frogItem->setPos(frogFixedX, frogFixedY);
        }
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
}


