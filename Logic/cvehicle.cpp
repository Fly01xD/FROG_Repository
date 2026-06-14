#include "cvehicle.h"
#include <random>

CVehicle::CVehicle(double _length, vehDirection _direction)
    : Length(_length), Direction(_direction),
    Position(0.0), State(dangerous), Speed(0.0)
{}


// metoda do nadawania losowej wartosci predkosci
void CVehicle::randomSpeed(double min, double max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<double> randSpeed(min,max);
    Speed = randSpeed(gen);
}

// metody do poruszania pojazdem
bool CVehicle::move(double _time, int _dist)
{
    Position = (_time*Speed*0.001)+Position;
    if(Position/_dist >= 1)
        return true;
    else
        return false;
}

void CVehicle::move(double _time)
{
    Position = (_time*Speed)+Position;
}

// getery settery
double CVehicle::getSpeed() {return Speed;}
void CVehicle::setSpeed(double _speed) {Speed = _speed;}

double CVehicle::getLength() {return Length;}

vehDirection CVehicle::getDirection() {return Direction;}

double CVehicle::getPosition() {return Position;}

vehState CVehicle::getState() {return State;}

void CVehicle::setState(vehState _state) {State = _state;}

