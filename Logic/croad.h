#ifndef CROAD_H
#define CROAD_H

#include "cisland.h"
#include "clane.h"
#include <vector>

enum gameDifficulty {
    easy,
    medium,
    hard
};

enum roadInfrastructure {
    island,
    lane
};

class CRoad
{
    std::vector<CLane*> Lanes;
    std::vector<CIsland*> Islands;
    unsigned Difficulty;
    int Distance;

public:
    CRoad(gameDifficulty _diff);
    ~CRoad();

    void updateGame(double dt);
    void gameEnd(); // to trzeba jeszcze napisać

    roadInfrastructure jump(unsigned &_njump);

    //gettery settery
    std::vector<CLane*> getLanes();
    std::vector<CIsland*> getIslands();
};

#endif // CROAD_H
