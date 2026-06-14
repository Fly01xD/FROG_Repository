#include "cplayer.h"
#include "CRoad.h"
CPlayer::CPlayer(CRoad* _road)
    : CPlayerBase(_road)
{}

CPlayer::~CPlayer()
{}

void CPlayer::jumpOnKey()
{
    FrogJump();
}

void CPlayer::jumpOnCalc()
{
    // tu ma być pusto!
}

void CPlayer::playerAIPause()
{
    // tu ma być pusto!
}
