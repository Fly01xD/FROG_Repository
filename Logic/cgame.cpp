#include "cgame.h"
#include "mainwindow.h"

#include "cplayerai.h"
#include "cplayer.h"
#include "cplayerai.h"
#include "cplay.h"

CGame::CGame()
    :observer(CObserver(nullptr, nullptr)),
    logicRoad(new CRoad(gameDifficulty::easy,&observer)),
    player(nullptr)
{}

CGame::~CGame()
{
    delete player;
    delete logicRoad;
}

CPlayerBase* CGame::beginGame()
{
    player = new CPlayer(logicRoad);
    return player;
}
CPlayerBase* CGame::beginGameAI()
{
    player = new CPlayerAI(logicRoad);
    return player;
}