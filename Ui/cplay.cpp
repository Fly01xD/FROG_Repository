#include "cplay.h"
#include "mainwindow.h"
#include <QVBoxLayout>
class CPlayerBase;

CPlay::CPlay(MainWindow &window, QWidget *parent)
    : QWidget(parent), m_window(window)
{
    sGame = nullptr;
    gView = nullptr;
}
void CPlay::setupGameView(CGame* _game)
{
    gView = new GameView;
    game = _game;
}

void CPlay::startUser()
{
    if(sGame == nullptr)
    {
        //stowrzenie nowej gry ale tylko wtedy jeśli jeszcze nie istnieje
        //po przegranej albo po odpaleniu aplikacji
        CPlayerBase* p = game->beginGame();
        sGame = new GameScene (m_window.getDifficulty(),p);
        // TRZEBA NAPISAĆ TWORZENIE GRACZA CZLOWIEKA

        //ustawienie kamery na nową planszę
        gView->setScene(sGame);

        //po wciśnięci przycisku graj stos wybiera okno 3 czyli
        //główne okno gry
        m_window.getStackedWidget()->setCurrentIndex(3);
    }
    else
    {
        gView->setScene(sGame);
        m_window.getStackedWidget()->setCurrentIndex(3);
    }
}

void CPlay::startAI()
{
    if(sGame == nullptr)
    {
        CPlayerBase* p = game->beginGameAI();
        sGame = new GameScene (m_window.getDifficulty(),p);
        // TRZEBA NAPISAĆ TWORZENIE GRACZA CZLOWIEKA
        gView->setScene(sGame);
        m_window.getStackedWidget()->setCurrentIndex(3);
    }
    else
    {
        gView->setScene(sGame);
        m_window.getStackedWidget()->setCurrentIndex(3);
    }
}


void CPlay::frogDied()
{
    // trzeba napisać co jak żaba umrze
}
