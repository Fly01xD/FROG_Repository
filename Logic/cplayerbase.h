#ifndef CPLAYERBASE_H
#define CPLAYERBASE_H

class CRoad;

class CPlayerBase
{
    CRoad* logicRoad;
    unsigned n; // n jest zmienną do liczenia przestrzeni
    // na których żaba była, robi to dla AI i CRoad za oczy żeby
    // wiedziały czy żaba jest na pasie ruchu czy na wyspie
    // na podstawie tego ile już żaba skoczyła
public:
    CPlayerBase(CRoad* _road);
    virtual ~CPlayerBase() = default;

    void FrogJump();
    virtual void jumpOnKey() = 0;

    virtual void jumpOnCalc() = 0;

    CRoad* getRoad() {return logicRoad;}
    unsigned getN() const {return n;}
};

#endif // CPLAYERBASE_H
