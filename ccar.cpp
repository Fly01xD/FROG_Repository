#include "ccar.h"

CCar::CCar(vehDirection _direction)
    :  CVehicle(20.0, _direction)
{
    CVehicle::randomSpeed(6.0, 10.0);
}

CCar::~CCar() {}
