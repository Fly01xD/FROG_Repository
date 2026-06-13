#include "cmenu.h"
#include "mainwindow.h"
#include "cleaderboard.h" // Dołączamy, bo musimy znać klasę do connect
#include "csettings.h"
#include "cplay.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

CMenu::CMenu(MainWindow &window, QWidget *parent) : QWidget(parent), m_window(window) {}

void CMenu::setupMenu()
{
    //to odpowiada za pionowe ustawienie elementów
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *title = new QLabel("MENU");
    title->setAlignment(Qt::AlignCenter);

    QPushButton *btnPlay = new QPushButton("Graj");
    QPushButton *btnLead = new QPushButton("Leaderboard");
    QPushButton *btnAI = new QPushButton("Tryb AI");
    QPushButton *btnSett = new QPushButton("Ustawienia");

    // zwiększenie rozmiaru przycisków bo bez tego były strasznie małe
    btnPlay->setFixedHeight(60);
    btnLead->setFixedHeight(60);
    btnAI->setFixedHeight(60);
    btnSett->setFixedHeight(60);

    //każdy stworzony przycisk oraz napis będzie pionowo ustawiony dzięki temu:
    layout->addWidget(title);
    layout->addWidget(btnPlay);
    layout->addWidget(btnLead);
    layout->addWidget(btnAI);
    layout->addWidget(btnSett);

    connect(btnPlay, &QPushButton::clicked, m_window.getPlay(), &CPlay::startUser);
    connect(btnLead, &QPushButton::clicked, m_window.getLeaderboard(), &CLeaderboard::showLeaderboard);
    connect(btnAI, &QPushButton::clicked, m_window.getPlay(), &CPlay::startAI);
    connect(btnSett, &QPushButton::clicked, m_window.getSettings(), &CSettings::showSettings);
}

void CMenu::goMenu()
{
    //używamy referencji i za pomocą zmiennej m_window zmieniamy indeks w Mainwindow
    m_window.getStackedWidget()->setCurrentWidget(0);
}
