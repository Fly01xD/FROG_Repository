#include "cplayerai.h"
#include <cmath>

CPlayerAI::CPlayerAI(CRoad *_road)
    : CPlayerBase(_road), gen(seed()),
    minDelay(500), maxDelay(1500)
{
    int mean = maxDelay - minDelay;
    int sigma = (maxDelay - minDelay)/6;
    std::normal_distribution<double> k(mean, sigma);
    d = k;

    checkTimer.setInterval(500);
    checkTimer.setSingleShot(false);
    connect(&checkTimer, &QTimer::timeout,
            this, &CPlayerAI::jumpOnCalc);
}

CPlayerAI::~CPlayerAI()
{}

void CPlayerAI::jumpOnKey()
{
    // tu ma być pusto!
}

void CPlayerAI::jumpOnCalc()
{
    if(calculate())
    {
        // losujemy opóźnienie
        int random = std::round(d(gen));
        // warunek na to żeby opóźnienie nie było jakieś pojebane
        if(random >= 500 && random <= 1500)
        {
            QTimer::singleShot(random, this, [this]() {
                FrogJump();
            });
        }
        else // jeśli opóźnienie jest jakieś pojebane to daję średnią
        {
            QTimer::singleShot(d.mean(), this, [this]() {
                FrogJump();
            });
        }
    }
}

bool CPlayerAI::calculate()
{
    return false;
}