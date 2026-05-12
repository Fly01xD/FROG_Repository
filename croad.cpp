#include "croad.h"

CRoad::CRoad(gameDifficulty _diff) : Distance(100)
{
    // ustawianie liczby HP dla poziomów trudnośći
    // (poziom trudności i początkowa liczba HP jest tożsama)
    if(_diff == gameDifficulty::easy)
        Difficulty = 3;
    else if(_diff == gameDifficulty::medium)
        Difficulty = 2;
    else if(_diff == gameDifficulty::hard)
        Difficulty = 1;

    // tworzenie żaby na wyspie
    CIsland* island = new CIsland;
    island->addFrog(Difficulty);
    Islands.push_back(island);

    // tworzenie pasóW
    for(int i = 0; i<2;i++)
    {
        CLane* lane = new CLane(Distance, down);
        Lanes.push_back(lane);
    }
}

CRoad::~CRoad()
{
    for(auto l : Lanes)
        delete l;
    for(auto i : Islands)
        delete i;
}

void CRoad::updateGame(double _dt)
{
    // ruch pojazdów
    for(auto l : Lanes)
        l->update(_dt);

    // sprawdzam czy żaba żyje
    if(Islands[0]->getFrog()->getState() == frogState::dead
    || Lanes[0]->Crossing.getFrog()->getState() == frogState::dead)
    {
        gameEnd();
    }
}

//  logika jest taka, że żaba może być tylko na wyspie
//  lub pasie o indeksie 0 w tablicy
void CRoad::jump(unsigned &_njump)
{
    // kiedy żaba na wyspie
    if(Islands[0]->getFrog())
    {
        // przerzucam wskaźnik żaby z wyspy na przejscie
        Lanes[0]->Crossing.setFrog(Islands[0]->getFrog());
        Islands[0]->setFrog(nullptr);
        // odliczam pierwszy pas
        _njump = 1;
        // usuwam wyspę za żabą
        Islands.erase(Islands.begin());
        // dodaję wyspę przed żabą
        Islands.push_back(new CIsland);
        // dodaje punkt
        Lanes[0]->Crossing.getFrog()->addPoint();
    }
    // kiedy żaba na przejściu, a przed nią jest wyspa
    else if(Lanes[0]->Crossing.getFrog() && _njump == Lanes.size())
    {
        // przerzucam wskaźnik żaby z przejścia na wyspę
        Islands[0]->setFrog(Lanes[0]->Crossing.getFrog());
        Lanes[0]->Crossing.setFrog(nullptr);
        // odliczam, że żaba jest na wyspie
        _njump = 0;
        // usuwam pas za żabą
        Lanes.erase(Lanes.begin());
        // dodaję pas przed żabą
        Lanes.push_back(new CLane(Distance, down));
        // dodaje punkt
        Islands[0]->getFrog()->addPoint();
    }
    // kiedy żaba na przejściu a przed nią przejśice
    else if(Lanes[0]->Crossing.getFrog() && _njump < Lanes.size())
    {
        // przerzucam wskaźnik żaby z przejścia na kolejne przejście
        Lanes[1]->Crossing.setFrog(Lanes[0]->Crossing.getFrog());
        Lanes[0]->Crossing.setFrog(nullptr);
        // odliczam, że żaba wskoczyła na kolejny pas
        _njump++;
        // usuwam pas za żabą
        Lanes.erase(Lanes.begin());
        // dodaję pas przed żabą
        Lanes.push_back(new CLane(Distance, down));
        // dodaje punkt
        Lanes[0]->Crossing.getFrog()->addPoint();
    }
}