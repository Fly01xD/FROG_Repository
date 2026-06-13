#include "cgame.h"
#include "mainwindow.h"

#include "cplayerai.h"
#include "cplayer.h"

CGame::CGame(MainWindow* _window)
    : mWindow(_window), logicRoad(CRoad(mWindow->getDifficulty()))
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
