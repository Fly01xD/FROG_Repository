#include "cplayerbase.h"
#include "CRoad.h"

CPlayerBase::CPlayerBase(CRoad *_road)
    : logicRoad(_road)
{}

void CPlayerBase::FrogJump()
{
    logicRoad->jump(n);
}
