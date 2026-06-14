#ifndef CGAME_H
#define CGAME_H

#include "mainwindow.h"
#include "cobserver.h"

class CRoad;
class CPlayerBase;
class CPlay;

class CGame
{

public:
    CGame(MainWindow* _window);
    ~CGame();

    // setter dla CPlay
    void setPlayer(CPlayerBase* _player) {player = _player;}
    // odpala timery i daje hp dla żaby;
    CPlayerBase* beginGameAI(); // jeszcze trzeba napisać
    CPlayerBase* beginGame();

    //impuls przekazywany z CBasePlayer do CRoad
    //unsigned sprawia, że n musi być liczbą dodatnią
private:
    MainWindow* mWindow;
    CRoad logicRoad;
    CPlayerBase* player;   // tutaj musi być wskaźnik
    CObserver* observer;
};

#endif // CGAME_H
