#ifndef CISLAND_H
#define CISLAND_H

#include "cfrogcontainer.h"

class CIsland : public CFrogContainer
{
public:
    CIsland();
    ~CIsland();

    void addFrog(int _hp);

};

#endif // CISLAND_H
