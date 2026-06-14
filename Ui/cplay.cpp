#include "cplay.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include "cgame.h"

class CPlayerBase;

CPlay::CPlay(MainWindow &window, QWidget *parent)
    : QWidget(parent), m_window(window)
{
    sGame = nullptr;
    gView = nullptr;
    game = nullptr;
}

CPlay::~CPlay()
{}

void CPlay::setupGameView(CGame* _game)
{
    gView = new GameView(this);
    game = _game;
}

void CPlay::startUser()
{
    if(sGame == nullptr)
    {
        //stowrzenie nowej gry ale tylko wtedy jeśli jeszcze nie istnieje
        //po przegranej albo po odpaleniu aplikacji
        sGame = new GameScene (this,game->getRoad(),
                              m_window.getDifficulty(),
                              game->beginGame());
        game->setObserverSceneAndScreen(sGame, this); // tworzenie obserwatora
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
        game->getRoad()->gameBegin(); // no niestety, ale muszę tak zrobić
        sGame->unPauseAI();
    }
}

void CPlay::startAI()
{
    if(sGame == nullptr)
    {
        sGame = new GameScene (this,game->getRoad(),
                              m_window.getDifficulty(),
                              game->beginGameAI());
        game->setObserverSceneAndScreen(sGame,this);
        gView->setScene(sGame);
        m_window.getStackedWidget()->setCurrentIndex(3);
    }
    else
    {
        gView->setScene(sGame);
        m_window.getStackedWidget()->setCurrentIndex(3);
        game->getRoad()->gameBegin(); // no niestety, ale muszę tak zrobić
        sGame->unPauseAI();
    }
}


void CPlay::frogDied()
{
    delete sGame;
    sGame = nullptr;
    m_window.getStackedWidget()->setCurrentIndex(0);
}

void CPlay::pause()
{
    m_window.getStackedWidget()->setCurrentIndex(0);
}

void CPlay::unPause()
{
    m_window.getStackedWidget()->setCurrentIndex(3);
}
