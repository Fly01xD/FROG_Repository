#ifndef CPLAY_H
#define CPLAY_H

#include <QWidget>
#include <QGraphicsView>
#include "gamescene.h"
#include "gameview.h"
class MainWindow;

class CPlay : public QWidget {
    Q_OBJECT
public:
    CPlay(MainWindow &window, QWidget *parent = nullptr);
    ~CPlay();
    //metoda odpowiedzialna za stworzenie graficzne
    void setupGameView(GameScene* _scene);

    //metoda
    void Play();
private:
    MainWindow &m_window;
    GameView *gView;
    GameScene *sGame;
};

#endif // CPLAY_H
