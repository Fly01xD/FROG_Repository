#ifndef CMOTOR_H
#define CMOTOR_H

#include "cvehicle.h"

class CMotor : public CVehicle
{
public:
    CMotor(vehDirection _direction);
    ~CMotor ();
};

#endif // CMOTOR_H
