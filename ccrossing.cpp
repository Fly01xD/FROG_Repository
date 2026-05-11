#include "ccrossing.h"

CCrossing::CCrossing() {}

CCrossing::~CCrossing() {}

void CCrossing::checkFrogState()
{
    if(Frog && Vehicle)
        Frog->setState(dead);
}

CFrog *CCrossing::getFrog() {return Frog;}

void CCrossing::setFrog(CFrog* _frog) {Frog = _frog;}

void CCrossing::setVehicle(CVehicle* _v) {Vehicle = _v;}
