#ifndef CLANE_H
#define CLANE_H

#include "ccar.h"
#include "ccrossing.h"
#include "cmotor.h"
#include <vector>

class CLane
{
    std::vector<CVehicle*> Vehicles;
    int Distance;
    vehDirection Direction;
public:
    CLane(int _distance, vehDirection _dir);
    ~CLane ();

    // nie wiem czy przejście powinno być publiczne
    // (nie chce aby przejście było
    // zagregowane, bo charakterystyka przejścia
    // i też nie chcę kopiowania przez hardware
    // niepotrzebnie zmiennej typu CCrossing przy użyciu gettera)
    CCrossing Crossing;

    // metody do dodawania pojazdu
    void addVehicle(CCar* car);
    void addVehicle(CMotor* motor);
    void spawnVehicle();
    void despawnVehicle();

    // metoda do wywołania ruchu pojazdu i
    // sprawdzenie czy pojazd wjechal na przejscie
    void update(double _time);

    // getterki setterki
    vehDirection getDirection();
    void setDirection(vehDirection _dir);
};

#endif // CLANE_H
