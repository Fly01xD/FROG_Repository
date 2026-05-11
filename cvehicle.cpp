#include "cvehicle.h"
#include <random>

CVehicle::CVehicle(double _length, vehDirection _direction)
    : Length(_length), Direction(_direction), Position(0.0), State(dangerous) {
}


// metoda do nadawania losowej wartosci predkosci
void CVehicle::randomSpeed(double min, double max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<double> randSpeed(min,max);
    setSpeed(randSpeed(gen));
}

// metody do poruszania pojazdem
bool CVehicle::move(double _time, int max)
{
    setPosition((_time*Speed)+Position);
    if(Position/max >= 1)
        return true;
    else
        return false;
}

void CVehicle::move(double _time)
{
    setPosition((_time*Speed)+Position);
}

// getery settery
double CVehicle::getSpeed() {return Speed;}
void CVehicle::setSpeed(double _speed) {Speed = _speed;}

double CVehicle::getLength() {return Length;}

vehDirection CVehicle::getDirection() {return Direction;}

double CVehicle::getPosition() {return Position;}
void CVehicle::setPosition(int _pos) {Position = _pos;}

vehState CVehicle::getState() {return State;}

void CVehicle::setState(vehState _state) {State = _state;}

