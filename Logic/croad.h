#ifndef CROAD_H
#define CROAD_H

#include "cisland.h"
#include "clane.h"
#include <vector>
#include <QObject>
#include <QTimer>

enum gameDifficulty {
    hard,
    medium,
    easy
};

enum roadInfrastructure {
    island,
    lane
};

enum gameState {
    running,
    paused
};

class CObserver;

class CRoad : public QObject
{
    Q_OBJECT
private:
    QTimer logicTimer;
    CObserver* observer;
    std::vector<CLane*> Lanes;
    std::vector<CIsland*> Islands;
    unsigned Difficulty;
    int Distance;
    CFrog* Frog;
    gameState State;

public:
    CRoad(gameDifficulty _diff, CObserver* _obs);
    ~CRoad();

    void gameEnd(); // to trzeba jeszcze napisać info dla observera
    void gameBegin();
    void gamePause();

    void jump(unsigned &_njump);

    //gettery settery
    std::vector<CLane*> getLanes();
    std::vector<CIsland*> getIslands();
    void setDifficulty(gameDifficulty _diff);
    unsigned getDifficulty() {return Difficulty;}
    gameState getState() {return State;}
private slots:
    void updateGame();
};

#endif // CROAD_H
