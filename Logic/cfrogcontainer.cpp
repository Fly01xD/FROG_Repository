#include "cfrogcontainer.h"

CFrogContainer::CFrogContainer() : Frog(nullptr) {}

CFrogContainer::~CFrogContainer() {}

CFrog *CFrogContainer::getFrog() {return Frog;}
void CFrogContainer::setFrog(CFrog* _frog) {Frog = _frog;}