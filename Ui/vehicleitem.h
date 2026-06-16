#ifndef VEHICLEITEM_H
#define VEHICLEITEM_H

#include "cvehicle.h"
#include <qgraphicsitem.h>
#include <QRandomGenerator>
#include <QPixmap>
#include <QString>

enum class EVehicleType {
    Car,
    Motorcycle
};

class VehicleItem : public QGraphicsPixmapItem
{
    CVehicle* logicVehicle;
public:
    VehicleItem(CVehicle* _veh, EVehicleType type, QGraphicsItem* parent = nullptr);
    CVehicle* getLogicVehicle() const { return logicVehicle; }
};

#endif // VEHICLEITEM_H
