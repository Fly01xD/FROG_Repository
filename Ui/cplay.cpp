#include "cplay.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include "cgame.h"
#include "GameScene.h"

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
    gView = new QGraphicsView(this);
    game = _game;

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(gView);

    gView->setRenderHint(QPainter::Antialiasing);
}

void CPlay::startUser()
{
    if(sGame == nullptr)
    {
        //stowrzenie nowej gry ale tylko wtedy jeśli jeszcze nie istnieje
        //po przegranej albo po odpaleniu aplikacji
        sGame = new GameScene (this,game->getRoad(),
                              m_window.getDifficulty(),
                              game->beginGame(), width(), height());
        game->setObserverSceneAndScreen(sGame, this); // tworzenie obserwatora
        // TUTAJ ZACZYNAJĄ SIĘ EKSPERYMENTY
        /*gView->setScene(sGame);
        gView->setSceneRect(gView->viewport()->rect()); // do ustawieniapełnego okna
        sGame->synchLogic(m_window.getDifficulty());*/
        // TUTAJ KOŃCZĄ SIĘ EKPERYMENTY

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
                              game->beginGameAI(), width(), height());
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
    game->newRoad();
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

void CPlay::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    if (sGame) {
        // Gra wczyta się w idealnych proporcjach zaraz po tym jak aplikacja zostanie narysowana na ekranie
        sGame->updateScaling(width(), height());
        gView->fitInView(sGame->sceneRect(), Qt::IgnoreAspectRatio);
    }
}

void CPlay::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if (gView && gView->scene())
    {
        sGame->updateScaling(width(), height());

        gView->fitInView(gView->scene()->sceneRect(), Qt::IgnoreAspectRatio);
    }
}
