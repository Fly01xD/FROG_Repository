#ifndef CCROSSING_H
#define CCROSSING_H

#include "cfrogcontainer.h"
#include "cvehicle.h"

class CCrossing : public CFrogContainer
{
    CVehicle* Vehicle;
public:
    CCrossing();
    ~CCrossing();

    void checkFrogState();

    void setVehicle(CVehicle* _v);
};

#endif // CCROSSING_H
