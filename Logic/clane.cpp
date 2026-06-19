#include "clane.h"
#include <random>

CLane::CLane(int _distance, vehDirection _dir)
    : Distance(_distance), Direction(_dir), Crossing(new CCrossing)
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

CVehicle* CLane::spawnVehicle()
{
    // segment losowania:
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> n(0,1); //który pojazd zrespić
    std::uniform_int_distribution<int> prob(1,20); // czy zrespić pojazd
    if(prob(gen) == 1)
    {
        if(n(gen) == 0)
            addVehicle(new CCar(Direction));
        else
            addVehicle(new CMotor(Direction));
        return Vehicles[Vehicles.size()-1];
    }
    else
        return nullptr;
}

// metoda do wywołania ruchu pojazdu i
// sprawdzenie czy pojazd wjechal na przejscie
std::vector<CVehicle*> CLane::update(double _time)
{
    std::vector<CVehicle*> toDelete;
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
                (*v)->setState(harmless);  // ustawiamy harmless (bo juz przejechal przez przejscie)
                Crossing->setVehicle(nullptr);
            }
        }
        // teraz należy usunąć te pojazdy co wyjechały poza planszę
        if((*v)->getPosition()/double(Distance) >=2)
        {
            toDelete.push_back(*v);
            delete *v;
            v = Vehicles.erase(v);
        }
        else
            ++v;
    }
    return toDelete;
}

// gettery settery
std::vector<CVehicle *> CLane::getVehicles() {return Vehicles;}

vehDirection CLane::getDirection() {return Direction;}

void CLane::setDirection(vehDirection _dir) {Direction = _dir;}
