#include "cobserver.h"
#include "cplay.h"
#include "gamescene.h"

CObserver::CObserver(GameScene *_scene, CPlay *_play)
    : sGame(_scene), playScreen(_play)
{}

CObserver::~CObserver()
{}

void CObserver::informSceneDraw()
{
    sGame->drawGame();
}

void CObserver::informSceneMove()
{
    sGame->drawGame();
}

void CObserver::informScreenPause()
{
    playScreen->pause();
}

void CObserver::informScreenUnPause()
{
    playScreen->unPause();
}

void CObserver::informScreenEnd()
{
    sGame->drawGame(); // powinno się to tym różnić
    // od zwykłego rysowania, że FrogItem ma inny
    // PNG kiedy jest nieżywy - FrogItem
    // sprawdza czy żaba jest żywa i zmienia PNG.
    // oprócz tego nie powinno być różnicy

    // należy napisać odczekanie, tak z 1.5s
    // zanim zmieni się Widget na Cmenu
    playScreen->frogDied();

}
