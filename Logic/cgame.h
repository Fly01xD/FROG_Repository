#ifndef CGAME_H
#define CGAME_H

#include "cobserver.h"
#include "croad.h"
class CPlayerBase;
class CPlay;

class CGame
{

public:
    CGame();
    ~CGame();

    // odpala timery i daje hp dla żaby;
    CPlayerBase* beginGameAI(); // jeszcze trzeba napisać timery
    CPlayerBase* beginGame();

    void setObserverSceneAndScreen(GameScene* _scene, CPlay* _play)
        {observer = CObserver(_scene, _play);}
    CRoad* getRoad();
    void newRoad();
private:
    CObserver observer;
    CRoad* logicRoad; // niestety musi to być wskaźnik bo jest to QObiekt
    CPlayerBase* player; // tutaj musi być wskaźnik
};

#endif // CGAME_H
