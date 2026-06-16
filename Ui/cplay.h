#ifndef CPLAY_H
#define CPLAY_H

#include <QWidget>
#include <QGraphicsView>
//#include "gameview.h"
class CGame;
class GameScene;
class CObserver;

class MainWindow;

class CPlay : public QWidget {
    Q_OBJECT
public:
    CPlay(MainWindow &window, QWidget *parent = nullptr);
    ~CPlay();
    //metoda odpowiedzialna za stworzenie graficzne
    void setupGameView(CGame *_game);

    //metoda
    void startUser();
    void startAI();
    void frogDied();
    void pause();
    void unPause();
private:
    MainWindow &m_window;
    QGraphicsView *gView;
    GameScene *sGame;
    CGame* game;
};

#endif // CPLAY_H
