#ifndef ICVEHICLE_H
#define ICVEHICLE_H

enum vehDirection {
    up,
    down
};

enum vehState {
    dangerous,
    harmless
};

class ICVehicle
{

public:
    virtual ~ICVehicle() = default;

    virtual bool move(double _time, int max) = 0;
    virtual void move(double _time) = 0;

    virtual void randomSpeed(double min, double max) = 0;

    // gettery settery
    virtual double getSpeed() = 0;
    virtual void setSpeed(double _speed) = 0;

    virtual double getLength() = 0;

    virtual vehDirection getDirection() = 0;

    virtual double getPosition() = 0;

};

#endif // ICVEHICLE_H
