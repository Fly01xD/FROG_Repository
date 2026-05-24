#include "cmotor.h"

CMotor::CMotor(vehDirection _direction)
    : CVehicle(10.0, _direction)
{
    CVehicle::randomSpeed(9.0, 15.0);
}

CMotor::~CMotor() {}
