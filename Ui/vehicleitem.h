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
    void setLogicVehicle(CVehicle* _v) {logicVehicle = _v;}
};

#endif // VEHICLEITEM_H
