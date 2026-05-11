#ifndef CCROSSING_H
#define CCROSSING_H

#include "cfrog.h"
#include "cvehicle.h"

class CCrossing
{
    CFrog* Frog;
    CVehicle* Vehicle;
public:
    CCrossing();
    ~CCrossing();

    void checkFrogState();

    CFrog* getFrog();
    void setFrog(CFrog* _frog);

    void setVehicle(CVehicle* _v);
};

#endif // CCROSSING_H
