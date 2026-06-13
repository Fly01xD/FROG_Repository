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

    //metoda
    void startUser();
    void startAI();
private:
    MainWindow &m_window;
    GameView *gView;
    GameScene *sGame;
    CGame* game;
private slots:
    void frogDied();
};

#endif // CPLAY_H
