#include "cgame.h"
#include "mainwindow.h"

#include "cplayerai.h"
#include "cplayer.h"
#include "cplayerai.h"
#include "cplay.h"

CGame::CGame(MainWindow* _window)
    : mWindow(_window),
    logicRoad(mWindow->getDifficulty()),
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