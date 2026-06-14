#include "clane.h"
#include <random>

CLane::CLane(int _distance, vehDirection _dir)
    : Distance(_distance), Direction(_dir)
{}

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
    // segment losowania:
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> n(0,1); //który pojazd zrespić
    std::uniform_int_distribution<int> prob(1,4);
    if(prob(gen) == 1)
    {
        if(n(gen) == 0)
            addVehicle(new CCar(Direction));
        else
            addVehicle(new CMotor(Direction));
    }
}

// metoda do wywołania ruchu pojazdu i
// sprawdzenie czy pojazd wjechal na przejscie
void CLane::update(double _time)
{
    for(auto v = Vehicles.begin(); v != Vehicles.end();) {
        // jeśli pojazd już przejechał przez przejście
        // to po prostu jedzie
        if((*v)->getState() == vehState::harmless)
            (*v)->move(_time);
        // jeśli pojazd nie przejechał przez przejście
        // to wywoływana jest inna metoda
        else
        {
            if((*v)->move(_time, Distance))
            {
                // pojazd wjechał na przejście
                Crossing->setVehicle((*v));
                Crossing->checkFrogState();
                (*v)->setState(harmless);  // jesli pojazd nie potrącił żaby ustawiamy harmless (bo juz przejechal przez przejscie)
                Crossing->setVehicle(nullptr);
            }
        }
        // teraz należy usunąć te pojazdy co wyjechały poza planszę
        if((*v)->getPosition()/double(Distance) >=2)
        {
            delete *v;
            v = Vehicles.erase(v);
        }
        else
            ++v;
    }
}

// gettery settery
std::vector<CVehicle *> CLane::getVehicles() {return Vehicles;}

vehDirection CLane::getDirection() {return Direction;}

void CLane::setDirection(vehDirection _dir) {Direction = _dir;}
