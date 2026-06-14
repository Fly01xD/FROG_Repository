#ifndef CPLAY_H
#define CPLAY_H

#include <QWidget>
#include <QGraphicsView>
#include "gameview.h"
class CGame;

class MainWindow;

class CPlay : public QWidget {
    Q_OBJECT
public:
    CPlay(MainWindow &window, QWidget *parent = nullptr);
    ~CPlay();
    //metoda odpowiedzialna za stworzenie graficzne
    void setupGameView(CGame *_game);
    void setObserver(CObserver* _obs) {observer = _obs;}

    //metoda
    void startUser();
    void startAI();
    void frogDied();
    void pause();
    void unPause();
private:
    MainWindow &m_window;
    GameView *gView;
    GameScene *sGame;
    CGame* game;
    CObserver* observer;
};

#endif // CPLAY_H
