#ifndef VEHICLEITEM_H
#define VEHICLEITEM_H

#include "cvehicle.h"
#include <qgraphicsitem.h>

class VehicleItem : public QGraphicsPixmapItem
{
    CVehicle* logicVehicle;
public:
    VehicleItem(QGraphicsItem* parent, CVehicle* _veh);
};

#endif // VEHICLEITEM_H
