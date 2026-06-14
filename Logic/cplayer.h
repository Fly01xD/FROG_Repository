#ifndef CPLAYER_H
#define CPLAYER_H

#include "cplayerbase.h"

class CPlayer : public CPlayerBase
{
public:
    CPlayer(CRoad* _road);
    ~CPlayer();

    void jumpOnKey() override;
    void jumpOnCalc() override;
    void playerAIPause() override;
};

#endif // CPLAYER_H
