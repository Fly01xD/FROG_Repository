#include "vehicleitem.h"

VehicleItem::VehicleItem(QGraphicsItem* parent, CVehicle *_veh)
    : logicVehicle(_veh), QGraphicsPixmapItem(parent)
{}
