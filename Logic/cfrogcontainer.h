#ifndef CFROGCONTAINER_H
#define CFROGCONTAINER_H

#include "cfrog.h"

class CFrogContainer
{
    CFrog* Frog;
public:
    CFrogContainer();
    ~CFrogContainer();

    CFrog* getFrog();
    void setFrog(CFrog* _frog);
};

#endif // CFROGCONTAINER_H
