#include "cplayerbase.h"
#include "CRoad.h"

CPlayerBase::CPlayerBase(CRoad *_road)
    : logicRoad(_road), n(0)
{}

void CPlayerBase::FrogJump()
{
    logicRoad->jump(n);
}
