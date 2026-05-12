#include "cisland.h"

CIsland::CIsland()
{}

CIsland::~CIsland() {}

void CIsland::addFrog(int _hp)
{
    CFrog* frog = new CFrog(_hp);
    setFrog(frog);
}