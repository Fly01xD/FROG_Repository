#ifndef CVEHICLE_H
#define CVEHICLE_H

#include "ICVehicle.h"

class CVehicle : public ICVehicle
{
    double Length;
    double Speed;
    vehDirection Direction;
    double Position;
    vehState State;

public:
    CVehicle(double _length, vehDirection _direction);
    virtual ~CVehicle() = default;

    void randomSpeed(double min, double max) override;

    bool move(double _time, int max) override;
    void move(double _time) override;

    // gettery settery
    double getSpeed() override;
    void setSpeed(double _speed) override;

    double getLength() override;

    vehDirection getDirection() override;

    double getPosition() override;
    void setPosition(int _pos) override;

    vehState getState();
    void setState(vehState _state);

};

#endif // CVEHICLE_H
