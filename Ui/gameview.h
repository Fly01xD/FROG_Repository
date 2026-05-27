#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <qgraphicsview.h>
#include <gamescene.h>

class GameView : public QGraphicsView
{
    GameScene* sGame;
    QTimer* logicTimer;
public:
    GameView(GameScene *_gamescene);
    ~GameView();
private slots:
    void updateScene();
    void pauseScene();
};

#endif // GAMEVIEW_H
