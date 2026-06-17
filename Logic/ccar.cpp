#include "ccar.h"
#include <qdebug>

CCar::CCar(vehDirection _direction)
    :  CVehicle(20.0, _direction)
{
    CVehicle::randomSpeed(27.7, 36.0);
}

CCar::~CCar() {
    qDebug() << "CVehicle destroyed at" << this;
}
