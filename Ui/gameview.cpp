#include "gameview.h"
#include <QTimer>

GameView::GameView(GameScene* _gamescene)
    : sGame(_gamescene), logicTimer(new QTimer(this))
{
    connect(logicTimer, &QTimer::timeout,
            this, &GameView::updateScene);

    logicTimer->setInterval(16);
    connect(this, &GameView::pauseScene,
            logicTimer, &QTimer::stop);
}

GameView::~GameView()
{}

void GameView::updateScene()
{
    // trzeba napisać ugdate gry
}

void GameView::pauseScene()
{
    // scena powinna sie zatrzymac po kliknieciu przycisku esc
}
