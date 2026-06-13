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
    CFrog* frog;

public:
    CRoad(gameDifficulty _diff);
    ~CRoad();

    frogState updateGame(double dt);
    void gameEnd(); // to trzeba jeszcze napisać

    roadInfrastructure jump(unsigned &_njump);

    //gettery settery
    std::vector<CLane*> getLanes();
    std::vector<CIsland*> getIslands();
    void setDifficulty(gameDifficulty _diff) {Difficulty = _diff+1;}
};

#endif // CROAD_H
