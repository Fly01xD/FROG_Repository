#ifndef COBSERVER_H
#define COBSERVER_H

class GameScene;
class CPlay;

class CObserver
{
private:
    GameScene* sGame;
    CPlay* playScreen;
public:
    CObserver(GameScene* _scene,CPlay* _play);
    ~CObserver();

    void informSceneDraw(); // metoda do informowania o ruchu pojazdów
    void informSceneMove(); // metoda do informowania o skakaniu żaby
    void informScreenPause(); // metoda do informowania CPlay o pazuie
    void informScreenUnPause(); // metoda do informowania CPlay o końcu pauzy
    void informScreenEnd(); // metoda do informowania o śmierci żaby
};

#endif // COBSERVER_H
