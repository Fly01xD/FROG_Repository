#include "cmotor.h"
#include <qdebug.h>

CMotor::CMotor(vehDirection _direction)
    : CVehicle(10.0, _direction)
{
    CVehicle::randomSpeed(54.0, 61.5);
}

CMotor::~CMotor() {}
