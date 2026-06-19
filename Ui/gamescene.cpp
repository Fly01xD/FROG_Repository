#include "gamescene.h"
#include "cplayerbase.h"
#include "croad.h"
#include "CLane.h"
#include "cisland.h"

#include <QKeyEvent>

GameScene::GameScene(QObject* parent, CRoad* _road, gameDifficulty _diff,
                     CPlayerBase *_player, qreal _windWidth, qreal _windHeight)
    : QGraphicsScene(parent), logicRoad(_road), player(_player)
{
    logicRoad->setDifficulty(_diff);
    setSceneRect(0, 0, _windWidth, _windHeight);
    synchLogic(_diff);
    updateScaling(_windWidth, _windHeight);
}

GameScene::~GameScene()
{
    //metoda w QGraphicsScene, która niszczy wszystko
    clear();
}

// metoda do podłączenia ItemóW graficznych do klas logicznych
// oraz dodania ich na scenę i zrobienie rodziecielstwa
void GameScene::synchLogic(gameDifficulty _diff)
{
    //niszczenie starych danych na wrazie gdyby dalej jakieś istaniły, sprawdzenie czy scena jest pusta
    clear();
    laneItems.clear();
    islandItems.clear();
    vehicleItems.clear();
    frogItem = nullptr;
    scoreRect = nullptr;
    scoreText = nullptr;
    hpRect    = nullptr;
    hpText    = nullptr;

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
            //centrowanie pasa
            qreal crossingW = crosI->pixmap().isNull() ? 0 : crosI->pixmap().width();
            crosI->setPos((laneW / 2.0) - (crossingW / 2.0), 0);
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
                vehicleItems.push_back(vehI); // to dodałem
            }
            else if(dynamic_cast<CMotor*>(v))
            {
                VehicleItem* vehI = new VehicleItem(v, EVehicleType::Motorcycle, laneI);
                vehI->setX((v->getPosition()/200.0)*laneW);
                vehicleItems.push_back(vehI); // to dodałem
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
            //ustawienie pozycji żaby na środek i na sam dół
            if (!frogI->pixmap().isNull())
            {
                frogI->setPos((sceneRect().width() / 2.0) - (frogI->pixmap().width() / 2.0),
                              (currentRowIndex * rowHeight) + (rowHeight / 2.0) - (frogI->pixmap().height() / 2.0));
            }
        }
        currentRowIndex++;
    }
    setupScoreHpDisplay();
    update();
}

void GameScene::setupScoreHpDisplay()
{
    scoreRect = new QGraphicsRectItem(5, 5, 120, 35);
    scoreRect->setBrush(QBrush(QColor(255, 140, 0))); // pomarańczowy
    scoreRect->setPen(QPen(QColor(200, 100, 0), 2)); // ramka
    scoreRect->setZValue(5); // zawsze na wierzchu
    addItem(scoreRect);

    // Tekst z punktami
    scoreText = new QGraphicsTextItem(scoreRect);
    scoreText->setFont(QFont("Arial", 14, QFont::Bold));
    scoreText->setDefaultTextColor(Qt::white);
    scoreText->setPos(8, 4);
    scoreText->setZValue(6);

    // Pierwsze wypełnienie danymi
    updateScore(0);

    // trzeba jeszcze hp:
    double x = sceneRect().width() - 80 - 5;
    double y = 5;
    hpRect = new QGraphicsRectItem(x, y, 80, 35);
    hpRect->setBrush(QBrush(QColor(200, 0, 0))); // czerwony
    hpRect->setPen(QPen(QColor(140, 0, 0), 2)); // ramka
    hpRect->setZValue(5);
    addItem(hpRect);

    hpText = new QGraphicsTextItem(hpRect);
    hpText->setFont(QFont("Arial", 14, QFont::Bold));
    hpText->setDefaultTextColor(Qt::white);
    hpText->setPos(8, 4);
    hpText->setZValue(6);

    updateHp(logicRoad->getDifficulty());
}
// poniżej metody do updateu liczydeł
void GameScene::updateScore(int _points)
{
    scoreText->setPlainText(QString("Punkty: %1").arg(_points));
}
void GameScene::updateHp(int _hp)
{
    hpText->setPlainText(QString("HP: %1").arg(_hp));
}

// metoda do rysowania ruchu pojazdów
void GameScene::drawGame(int _hp)
{
    std::vector<VehicleItem*> toDelete; // kontener na pojazdy do usuniecia
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
                    if (visVehicle->scene() != nullptr)
                        visVehicle->setX((logic->getPosition() / 200.0) * laneW);
                }
                else
                    toDelete.push_back(visVehicle);
            }
        }
    }
    for(auto v : toDelete)
    {
        vehicleItems.erase(
            std::remove(vehicleItems.begin(), vehicleItems.end(),
                        v), vehicleItems.end());
        delete v;
    }
    updateHp(_hp);
    update();
}
// skakanie żaby
void GameScene::moveGame(int _points)
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

            //usunięcie wskaźników usuwanych samochodów z VehicleItem
            for (auto child : lane->childItems())
            {
                if (VehicleItem* vehI = dynamic_cast<VehicleItem*>(child))
                {
                    vehicleItems.erase(std::remove(vehicleItems.begin(), vehicleItems.end(), vehI), vehicleItems.end());
                }
            }
            //usunięcie wszystkich dzieci lane'a
            qDeleteAll(lane->childItems());

            qreal laneW = lane->pixmap().width();

            //tworzenie nowych obiektów graicznych na podstawie logiki
            if (newLogicLane->Crossing)
            {
                CrossingItem* crosI = new CrossingItem(newLogicLane->Crossing, lane);
                qreal crossingW = crosI->pixmap().isNull() ? 0 : crosI->pixmap().width();
                crosI->setPos((laneW / 2.0) - (crossingW / 2.0), 0);
            }
            for(auto v : newLogicLane->getVehicles())
            {
                if(dynamic_cast<CCar*>(v))
                {
                    VehicleItem* vehI = new VehicleItem(v, EVehicleType::Car, lane);
                    vehI->setX((v->getPosition()/200.0)*laneW);
                    vehicleItems.push_back(vehI);// TO DODAŁEM
                }
                else if(dynamic_cast<CMotor*>(v))
                {
                    VehicleItem* vehI = new VehicleItem(v, EVehicleType::Motorcycle, lane);
                    vehI->setX((v->getPosition()/200.0)*laneW);
                    vehicleItems.push_back(vehI);// TO DODAŁEM
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

    // jescze trzeba naryssować punkty
    updateScore(_points);
    update();
}

void GameScene::spawnVehicle(CLane* _lane, CVehicle* _vehicle)
{
    LaneItem* target = nullptr;
    for(auto laneI : laneItems)
    {
        if(laneI->getLogicLane() == _lane)
            target = laneI;
    }
    if(target)
    {
        // eksperyment
        // CVehicle* veh = _lane->getVehicles()[_lane->getVehicles().size()-1];
        // qt świruje z tym błędem że veh nigdy nie jest odczytany
        qreal laneW = target->pixmap().width();
        if(dynamic_cast<CCar*>(_vehicle))
        {
            VehicleItem* vehI = new VehicleItem(_vehicle, EVehicleType::Car, target);
            vehI->setX((_vehicle->getPosition()/200.0)*laneW);
            vehicleItems.push_back(vehI); // TO DODAŁEM
        }
        else if(dynamic_cast<CMotor*>(_vehicle))
        {
            VehicleItem* vehI = new VehicleItem(_vehicle, EVehicleType::Motorcycle, target);
            vehI->setX((_vehicle->getPosition()/200.0)*laneW);
            vehicleItems.push_back(vehI); // TO DODAŁEM
        }
    }
    update();
}

void GameScene::despawnVehicle(std::vector<CVehicle*> _target) // możliwe że nie potrzebne // jednak potzrebne
{
    for(auto logicV : _target)
    {
        for(auto visV : vehicleItems)
        {
            if(visV->getLogicVehicle() == logicV)
                visV->setLogicVehicle(nullptr);
        }
    }
}

void GameScene::updateScaling(qreal windowWidth, qreal windowHeight)
{
    //zapisujemy wielkość rzędu przed zmianąskalowania, żeby móc zlokalizować pasy
    qreal oldRowHeight = sceneRect().height() / 4.0;
    if (oldRowHeight <= 0) oldRowHeight = windowHeight / 4.0;
    //ustawiamy prostokąt sceny pasujący do okna
    setSceneRect(0,0,windowWidth,windowHeight);
    //dzielimy wysokość całego obecnie ekranu na 4 i tak dostajemy
    //wysokość jednego rzędu
    qreal rowHeight = windowHeight/4.0;

    //skalowanie pasów, ponieważ pas jest parentem pojazdów i crossingów
    //to pojazdy i crossingi odrazu są skalowane
    for (LaneItem* lane : laneItems)
    {
        if (lane && !lane->pixmap().isNull())
        {
            int rowIndex = qRound(lane->y() / oldRowHeight);
            lane->setPos(0, rowIndex * rowHeight);

            //skalujemy pas tak żeby wypełniał pełny rozmiar ekranu
            qreal scaleX = windowWidth / lane->pixmap().width();
            qreal scaleY = rowHeight / lane->pixmap().height();
            lane->setTransform(QTransform::fromScale(scaleX, scaleY));
        }
    }
    //skalowanie wyspy (działa tak samo jak wyżej)
    for (IslandItem* island : islandItems)
    {
        if (island && !island->pixmap().isNull())
        {
            int rowIndex = qRound(island->y() / oldRowHeight);
            island->setPos(0, rowIndex * rowHeight);

            qreal scaleX = windowWidth / island->pixmap().width();
            qreal scaleY = rowHeight / island->pixmap().height();
            island->setTransform(QTransform::fromScale(scaleX, scaleY));
        }
    }
    //skalowanie żaby
    if (frogItem && !frogItem->pixmap().isNull())
    {
        qreal frogSize = rowHeight * 0.3;
        qreal scaleXY = frogSize / frogItem->pixmap().width();
        frogItem->setTransform(QTransform::fromScale(scaleXY, scaleXY));

        // Musimy policzyć fizyczny rozmiar żaby po przeskalowaniu
        qreal scaledFrogW = frogItem->pixmap().width() * scaleXY;
        qreal scaledFrogH = frogItem->pixmap().height() * scaleXY;

        //ustawienie żaby w odpowiednim miejscu na podstawie jej rozmiaru
        qreal frogFixedX = (windowWidth / 2.0) - (scaledFrogW / 2.0);
        qreal frogFixedY = windowHeight - rowHeight + ((rowHeight - scaledFrogH) / 2.0);

        frogItem->setPos(frogFixedX, frogFixedY);
    }
    // przesuwanie prostokąta z hp bo nie dzialalo
    if (hpRect)
    {
        qreal x = windowWidth - 80 - 5;
        hpRect->setRect(x, 5, 80, 35);
        hpText->setPos(x + 8, 9);
    }

    update();
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


