#ifndef CGAME_H
#define CGAME_H

#include "mainwindow.h"
class CRoad;
class CPlayerBase;

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
private:
    MainWindow* mWindow;
    CRoad logicRoad;
    CPlayerBase* player; // tutaj musi być wskaźnik
    // jeszcze należy wpisać obserwatora
};

#endif // CGAME_H
