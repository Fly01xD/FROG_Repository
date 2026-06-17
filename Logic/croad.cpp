#include "croad.h"
#include "SGameData.h"
#include "cwriter.h"
#include "CObserver.h"

CRoad::CRoad(gameDifficulty _diff, CObserver* _obs)
    : Distance(170), State(paused), observer(_obs), logicTimer(QTimer(this))
{
    // ustawianie liczby HP dla poziomów trudnośći
    // (poziom trudności i początkowa liczba HP jest tożsama+1
    if(_diff == gameDifficulty::easy)
        Difficulty = 3;
    else if(_diff == gameDifficulty::medium)
        Difficulty = 2;
    else
        Difficulty = 1;

    // ustwawianie QTimera pzdr
    logicTimer.setSingleShot(false);
    logicTimer.setInterval(100);
    connect(&logicTimer, &QTimer::timeout,
            this, &::CRoad::updateGame);

    // tworzenie żaby na wyspie
    CIsland* island = new CIsland;
    island->addFrog(Difficulty);
    Frog = island->getFrog();
    Islands.push_back(island);

    // tworzenie pasóW
    for(int i = 0; i<3;i++)
    {
        CLane* lane = new CLane(Distance, down);
        Lanes.push_back(lane);
    }
}
CRoad::~CRoad()
{
    for(auto l = Lanes.begin(); l != Lanes.end();)
    {
        delete *l;
        l = Lanes.erase(l);
    }
    for(auto i = Islands.begin(); i != Islands.end();)
    {
        delete *i;
        i = Islands.erase(i);
    }
}
void CRoad::updateGame() // rysowanie dla samochodóW
{
    if(State == running)
    {
        // ruch pojazdów
        for(auto l : Lanes)
        {
            std::vector<CVehicle*> toDelete = l->update(logicTimer.interval());
            if(!(toDelete.empty()))
                observer->informSceneDespawned(toDelete);
            if(l->spawnVehicle())
                observer->informSceneSpawned(l);
        }
        observer->informSceneDraw(Frog->getHP());

        if(Frog->getHP() <= 0) // TUTAJ ZMIENIŁEM Z: Frog->getState() == frogState::dead
        {
            gameEnd();
        }
    }
}
void CRoad::gameEnd()
{
    State = paused;
    logicTimer.stop();

    // żaba w której jest ilość punktów
    int zdobytePunkty = Frog->getPoints();

    //Zapisywanie danych z żaby do struktury
    GameData data;
    data.score = zdobytePunkty;

    //Zapisywanie do pliku
    CWriter writer(&data);

    observer->informScreenEnd();
}
void CRoad::gameBegin()
{
    if(State == paused)
    {
        State = running;
        logicTimer.start();
    }
}
void CRoad::gamePause()
{
    if(State == running)
    {
        State = paused;
        logicTimer.stop();
        observer->informScreenPause();
    }
    else
    {
        State = running;
        logicTimer.start();
        observer->informScreenUnPause();
    }
}


//  logika jest taka, że żaba może być tylko na wyspie
//  lub pasie o indeksie 0 w tablicy
void CRoad::jump(unsigned &_njump)
{
    if(State == running)
    {
    // kiedy żaba na wyspie
    if(Islands[0]->getFrog())
    {
        // przerzucam wskaźnik żaby z wyspy na przejscie
        Lanes[0]->Crossing->setFrog(Islands[0]->getFrog());
        Islands[0]->setFrog(nullptr);
        // odliczam pierwszy pas
        _njump = 1;
        // usuwam wyspę za żabą
        Islands.erase(Islands.begin());
        // dodaję wyspę przed żabą
        Islands.push_back(new CIsland);
        // dodaje punkt
        Lanes[0]->Crossing->getFrog()->addPoint();
    }
    // kiedy żaba na przejściu, a przed nią jest wyspa
    else if(Lanes[0]->Crossing->getFrog() && _njump == Lanes.size())
    {
        // przerzucam wskaźnik żaby z przejścia na wyspę
        Islands[0]->setFrog(Lanes[0]->Crossing->getFrog());
        Lanes[0]->Crossing->setFrog(nullptr);
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
    else if(Lanes[0]->Crossing->getFrog() && _njump < Lanes.size())
    {
        // przerzucam wskaźnik żaby z przejścia na kolejne przejście
        Lanes[1]->Crossing->setFrog(Lanes[0]->Crossing->getFrog());
        Lanes[0]->Crossing->setFrog(nullptr);
        // odliczam, że żaba wskoczyła na kolejny pas
        _njump++;
        // usuwam pas za żabą
        Lanes.erase(Lanes.begin());
        // dodaję pas przed żabą
        Lanes.push_back(new CLane(Distance, down));
        // dodaje punkt
        Lanes[0]->Crossing->getFrog()->addPoint();
        // wysyłam sygnał, że chcę dodać do ui drogi pas ruchu
    }
    }
    observer->informSceneMove(Frog->getPoints()); // BARDZO WAŻNE INFORMUJE ZE ŻABA SKOCZYŁA
}

std::vector<CLane *> CRoad::getLanes()  {return Lanes;}

std::vector<CIsland *> CRoad::getIslands()  {return Islands;}

void CRoad::setDifficulty(gameDifficulty _diff)
{
    if(_diff == gameDifficulty::easy)
    {
        Difficulty = 3;
        Frog->setHP(Difficulty);
    }
    else if(_diff == gameDifficulty::medium)
    {
        Difficulty = 2;
        Frog->setHP(Difficulty);
    }
    else
    {
        Difficulty = 1;
        Frog->setHP(Difficulty);
    }
}
