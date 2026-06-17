#include "cmotor.h"
#include <qdebug.h>

CMotor::CMotor(vehDirection _direction)
    : CVehicle(10.0, _direction)
{
    CVehicle::randomSpeed(36.0, 41.0);
}

CMotor::~CMotor() {
    qDebug() << "CVehicle destroyed at" << this;
}
