#include "ccar.h"
#include <qdebug>

CCar::CCar(vehDirection _direction)
    :  CVehicle(20.0, _direction)
{
    CVehicle::randomSpeed(41.5, 54.0);
}

CCar::~CCar() {}
