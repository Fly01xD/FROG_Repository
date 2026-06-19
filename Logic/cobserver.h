#ifndef COBSERVER_H
#define COBSERVER_H

#include <vector>

class GameScene;
class CPlay;
class CLane;
class CVehicle;

class CObserver
{
private:
    GameScene* sGame;
    CPlay* playScreen;
public:
    CObserver(GameScene* _scene,CPlay* _play);
    ~CObserver();

    void informSceneDraw(int _hp); // metoda do informowania o ruchu pojazdów
    void informSceneMove(int _points); // metoda do informowania o skakaniu żaby
    void informScreenPause(); // metoda do informowania CPlay o pazuie
    void informScreenUnPause(); // metoda do informowania CPlay o końcu pauzy
    void informScreenEnd(); // metoda do informowania o śmierci żaby
    void informSceneSpawned(CLane* _lane, CVehicle *_vehicle); // metoda do mówienia scenie, że pojawił się nowy pojazd
    void informSceneDespawned(std::vector<CVehicle *> _target); // podobnie co wyżej ale usuwa
};

#endif // COBSERVER_H
