#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "laneitem.h"
#include "crossingitem.h"
#include "vehicleItem.h"
#include "FrogItem.h"
#include "IslandItem.h"
#include "croad.h"
#include <QGraphicsScene>
class CPlayerBase;

class GameScene : public QGraphicsScene
{
    Q_OBJECT
private:
    // logika sceny
    CRoad* logicRoad;

    // Graphics items (dzieci sceny)
    std::vector<LaneItem*> laneItems;
    std::vector<IslandItem*> islandItems;
    std::vector<CrossingItem*> crossingItems;
    std::vector<VehicleItem*> vehicleItems;
    std::vector<LaneItem*> m_mapRows;

    CPlayerBase* player; // gadanie z graczem
    FrogItem* frogItem;    //wskaźnik na postać gracza
public:
    GameScene(QObject* parent,CRoad* _road ,gameDifficulty _diff,
              CPlayerBase* _player, qreal _windWidth, qreal _windHeight);
    ~GameScene();

    // synchronizacja logiki z ui
    void synchLogic(gameDifficulty _diff);
    // krok symulacji gry
    void drawGame();
    // przesunięcie (iluzja) żaby
    void moveGame();
    //metoda ustawiająca wymiary i pozycje na scenie
    void updateScaling(qreal windowWidth, qreal windowHeight);

    void unPauseAI();

    // niestety settery i gettery:
    CRoad* getLogicRoad() const { return logicRoad; }
    std::vector<LaneItem*>& getLaneItems() { return laneItems;}
    std::vector<IslandItem*>& getIslandItems() { return islandItems; }
    std::vector<CrossingItem*>& getCrossingItems() { return crossingItems; }
    std::vector<VehicleItem*>& getVehicleItems() { return vehicleItems; }
    FrogItem* getFrogItem() const { return frogItem; }

    void setLogicRoad(CRoad* road) { logicRoad = road; }
    void setLaneItems(const std::vector<LaneItem*>& items) { laneItems = items; }
    void setIslandItems(const std::vector<IslandItem*>& items) { islandItems = items; }
    void setCrossingItems(const std::vector<CrossingItem*>& items) { crossingItems = items; }
    void setVehicleItems(const std::vector<VehicleItem*>& items) { vehicleItems = items; }
    void setFrogItem(FrogItem* frog) { frogItem = frog; }

    // skakanie żaby dla czlowieka
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // GAMESCENE_H
