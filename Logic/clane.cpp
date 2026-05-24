#include "clane.h"
#include <random>

CLane::CLane(int _distance, vehDirection _dir)
    : Distance(_distance), Direction(_dir)
{}  // nie napisałem jeszcze spawnowania
    // pojazdu na psaie ruchu

CLane::~CLane()
{
    for(auto v : Vehicles)
        delete v;
}

// metody o różnych argumentach do dodawania pojazdów do kontenera
void CLane::addVehicle(CMotor* motor)
{
    Vehicles.push_back(motor);
}

void CLane::addVehicle(CCar* car)
{
    Vehicles.push_back(car);
}

void CLane::spawnVehicle()
{
    // segment losowania, który pojazd zrespić:
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> n(0,1);

    if(n(gen) == 0) {
        addVehicle(new CCar(Direction));
    }
    else {
        addVehicle(new CMotor(Direction));
    }
}

void CLane::despawnVehicle()
{
    // usuwapierwszy pozostaly pojazd, który jest za przejsciem
    if(Vehicles[0]->getState() == vehState::harmless && Vehicles[0]->getPosition() == 200)
    Vehicles.erase(Vehicles.begin());
}

// metoda do wywołania ruchu pojazdu i
// sprawdzenie czy pojazd wjechal na przejscie
void CLane::update(double _time)
{
    for(auto v : Vehicles) {
        if(v->getState() == vehState::harmless)
            v->move(_time);
        else
        {
            if(v->move(_time, Distance))
            {
                Crossing->setVehicle(v);
                Crossing->checkFrogState();
                v->setState(harmless);  // jesli pojazd nie potrącił żaby ustawiamy harmless (bo juz przejechal przez przejscie)
            }
        }
    }
}

std::vector<CVehicle *> CLane::getVehicles() {return Vehicles;}

// gettery settery
vehDirection CLane::getDirection() {return Direction;}

void CLane::setDirection(vehDirection _dir) {Direction = _dir;}
