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
    //kosntruktor, który może wczytywać i samochody i motocykle z pliku
    VehicleItem(CVehicle* _veh, EVehicleType type, QGraphicsItem* parent = nullptr) : QGraphicsPixmapItem(parent)
    {
        logicVehicle = _veh;

        QString chosenPath;

        if (type == EVehicleType::Car)
        {
            //tablica z wszystkimi samochodami
            QString carVariants[] =
            {
                "assets/car_1.png",
                "assets/car_2.png",
                "assets/car_3.png",
                "assets/car_4.png",
                "assets/car_5.png",
                "assets/car_6.png"
            };
            //losowanie koloru samochodu, który ma się zrespić
            int randomIndex = QRandomGenerator::global()->bounded(6);
            chosenPath = carVariants[randomIndex];
        }
        else if (type == EVehicleType::Motorcycle)
        {
            // tablica z motocyklami
            QString motorVariants[] =
            {
                "assets/motor_1.png",
                "assets/motor_2.png"
            };

            int randomIndex = QRandomGenerator::global()->bounded(2);
            chosenPath = motorVariants[randomIndex];
        }
        //wczytujemy tą grafike do sceny
        QPixmap pix(chosenPath);
        setPixmap(pix);
    }
    CVehicle* getLogicVehicle() const { return logicVehicle; }
};

#endif // VEHICLEITEM_H
