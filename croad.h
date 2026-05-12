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

    void jump(unsigned &_njump);
};

#endif // CROAD_H
