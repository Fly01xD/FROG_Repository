#include "cplayerai.h"
#include "croad.h"
#include <cmath>

CPlayerAI::CPlayerAI(CRoad *_road)
    : CPlayerBase(_road), gen(seed()),
    minDelay(500), maxDelay(1500), checkTimer(QTimer(this))
{
    int mean = maxDelay - minDelay;
    int sigma = (maxDelay - minDelay)/6;
    std::normal_distribution<double> k(mean, sigma);
    d = k;

    checkTimer.setInterval(500);
    checkTimer.setSingleShot(false);
    connect(&checkTimer, &QTimer::timeout,
            this, &CPlayerAI::jumpOnCalc);
    checkTimer.start();
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

void CPlayerAI::playerAIPause()
{
    if(getRoad()->getState() == running)
        checkTimer.stop();
    else
        checkTimer.start();
}

bool CPlayerAI::calculate()
{
    //pobieramy stan drogi z CRoad
    CRoad* road = getRoad();
    std::vector<CLane*> lane = road->getLanes();
    std::vector<CIsland*> island = road->getIslands();

    //zmienna która przybierze wartość pasa, na który będzie skakała żaba,
    //po to żeby wiedzieć, z którego pasa zczytać informacje o samochodach
    CLane* targetLane = nullptr;

    //tworzymy zmienna, która będzie mówiła nam o położeniu żaby
    int frogX = 0;

    //jeśli żaba znajduje się na wyspie to przed nią jest pas 0
    if (island[0]->getFrog() != nullptr)
    {
        targetLane = lane[0];
    }
    else if (lane[0]->Crossing->getFrog() != nullptr)
    {
        if (n == 0)
        {
            targetLane = lane[0];
        }
        else if(n > 0 && n < lane.size())
        {
            targetLane = lane[1];
        }
        else if(n == lane.size())
        {
            return true;
        }
    }
    //jeśli nic nie przypiszemy do tragetLane to znaczy że następna jest wyspa
    //więc żaba może skoczyć
    if (targetLane == nullptr)
    {
        return true;
    }

    //pobieramy lokalizacje samochodów na następnym pasie
    std::vector<CVehicle*> vehicles = targetLane->getVehicles();

    for (auto v : vehicles)
    {
        int vehicleX = v->getPosition();

        // Dystans matematyczny |x| samochodu do żaby
        int distance = std::abs(vehicleX - frogX);
        int dynamicSafeDistance = v->getLength() * 2;

        if (distance < dynamicSafeDistance)
        {
            return false;
        }
    }

    return true;
}