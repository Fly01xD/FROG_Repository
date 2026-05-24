#include "cfrog.h"

CFrog::CFrog(int _hp) : HP(_hp), Points(0), State(alive)
{}

CFrog::~CFrog() {}

int CFrog::getPoints() {return Points;}

void CFrog::setPoints(int _points) {Points = _points;}

void CFrog::addPoint() {Points++;}

int CFrog::getHP() {return HP;}

void CFrog::setHP(int _hp) {HP = _hp;}

void CFrog::addHP() {HP++;}

frogState CFrog::getState() {return State;}

void CFrog::setState(frogState _state) {State = _state;}
