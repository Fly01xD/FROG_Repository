#ifndef CLANE_H
#define CLANE_H

#include "ccar.h"
#include "ccrossing.h"
#include "cmotor.h"
#include <vector>

class CLane
{
    unsigned Index;
    std::vector<CVehicle*> Vehicles;
    int Distance;
    CCrossing Crossing;
    vehDirection Direction;
public:
    CLane(unsigned _i, int _distance);
    ~CLane ();

    // metody do dodawania pojazdu
    void addVehicle(CCar* car);
    void addVehicle(CMotor* motor);
    void spawnVehicle();

    // metoda do wywołania ruchu pojazdu i
    // sprawdzenie czy pojazd wjechal na przejscie
    void update(double _time);

    // wskakiwanie na i z przejscia
    void jumpIn(CFrog* _frog);
    CFrog* jumpOut();

    // getterki setterki
    vehDirection getDirection();
    void setDirection(vehDirection _dir);

};

#endif // CLANE_H
