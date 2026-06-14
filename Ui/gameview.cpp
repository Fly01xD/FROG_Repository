#include "gameview.h"

GameView::GameView(QWidget *parent) : QGraphicsView(parent)
{}

GameView::~GameView()
{}

void GameView::updateScene()
{}

void GameView::pauseScene()
{
    // scena powinna sie zatrzymac po kliknieciu przycisku esc
}
