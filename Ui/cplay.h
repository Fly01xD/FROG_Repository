#ifndef CPLAY_H
#define CPLAY_H

#include <QWidget>
#include <QGraphicsView>
#include "gamescene.h"
class MainWindow;

class CPlay : public QWidget {
    Q_OBJECT
public:
    CPlay(MainWindow &window, QWidget *parent = nullptr);
    ~CPlay();
    //metoda odpowiedzialna za stworzenie graficzne
    void setupGameView();

    //metoda
    void Play();
private:
    MainWindow &m_window;
    QGraphicsView *gameView;
    GameScene *sGame;
};

#endif // CPLAY_H
