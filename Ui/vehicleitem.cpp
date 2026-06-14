#include "vehicleitem.h"

VehicleItem::VehicleItem(CVehicle *_veh, const QString &imagePath, QGraphicsItem *parent)
    : logicVehicle(_veh), QGraphicsPixmapItem(parent)
{}
