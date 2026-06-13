#include "cgame.h"
#include "mainwindow.h"

#include "cplayerai.h"
#include "cplayer.h"
#include "cplayerai.h"
#include "cplay.h"

CGame::CGame(MainWindow* _window, CPlay* _playScreen)
    : mWindow(_window),
    logicRoad(mWindow->getDifficulty()),
    playScreen(_playScreen),
    player(nullptr)
{

}
CGame::~CGame()
{
    delete player;
}

CPlayerBase* CGame::beginGame()
{
    player = new CPlayer(&logicRoad);
    return player;
}
CPlayerBase* CGame::beginGameAI()
{
    player = new CPlayerAI(&logicRoad);
    return player;
}
void CGame::executeJump(unsigned n)
{
    logicRoad.jump(n);
}