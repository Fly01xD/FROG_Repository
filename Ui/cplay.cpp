#include "cplay.h"
#include "mainwindow.h"
#include <QVBoxLayout>

CPlay::CPlay(MainWindow &window, QWidget *parent): QWidget(parent), m_window(window)
{
    sGame = nullptr;
}
void CPlay::setupGameView()
{
    //trzeba to napisać, !prawdopodobnie trzeba z tego zrobić kolejną klase!
}

void CPlay::Play()
{
    if(sGame == nullptr)
    {
        //stowrzenie nowej gry ale tylko wtedy jeśli jeszcze nie istnieje
        //po przegranej albo po odpaleniu aplikacji
        sGame = new GameScene (m_window.getDifficulty());

        //ustawienie kamery na nową planszę
        gameView->setScene(sGame);

        //po wciśnięci przycisku graj stos wybiera okno 3 czyli
        //główne okno gry
        m_window.getStackedWidget()->setCurrentIndex(3);
    }
}
