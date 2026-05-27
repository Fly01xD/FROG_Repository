#include "cplay.h"
#include "mainwindow.h"
#include <QVBoxLayout>

CPlay::CPlay(MainWindow &window, QWidget *parent)
    : QWidget(parent), m_window(window)
{
    sGame = nullptr;
    gView = nullptr;
}
void CPlay::setupGameView(GameScene* _scene)
{
    gView = new GameView(_scene);
}

void CPlay::Play()
{
    if(sGame == nullptr)
    {
        //stowrzenie nowej gry ale tylko wtedy jeśli jeszcze nie istnieje
        //po przegranej albo po odpaleniu aplikacji
        sGame = new GameScene (m_window.getDifficulty());
        setupGameView(sGame);

        //ustawienie kamery na nową planszę
        gView->setScene(sGame);

        //po wciśnięci przycisku graj stos wybiera okno 3 czyli
        //główne okno gry
        m_window.getStackedWidget()->setCurrentIndex(3);
    }
}
