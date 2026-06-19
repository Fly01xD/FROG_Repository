#include "ccrossing.h"

CCrossing::CCrossing() {}

CCrossing::~CCrossing() {}

void CCrossing::checkFrogState()
{
    if(getFrog() && Vehicle)
    {
        getFrog()->setHP(getFrog()->getHP()-1);
        if(getFrog()->getHP()<=0)
            getFrog()->setState(dead);
    }
}

void CCrossing::setVehicle(CVehicle* _v) {Vehicle = _v;}
