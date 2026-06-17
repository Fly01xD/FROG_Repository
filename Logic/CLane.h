#ifndef CLANE_H4
#define CLANE_H4

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
    CCrossing* Crossing;

    // metody do dodawania pojazdu
    void addVehicle(CCar* car);
    void addVehicle(CMotor* motor);
    bool spawnVehicle();
    void despawnVehicle(CVehicle* target);

    // metoda do wywołania ruchu pojazdu i
    // sprawdzenie czy pojazd wjechal na przejscie
    std::vector<CVehicle *> update(double _time); // jest bool 1 - samochód usuniety, 0 nie susuniety

    // getterki setterki
    std::vector<CVehicle*> getVehicles();
    vehDirection getDirection();
    void setDirection(vehDirection _dir);
};

#endif // CLANE_H
