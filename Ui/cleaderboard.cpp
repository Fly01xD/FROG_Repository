#include "cleaderboard.h"
#include "creader.h"
#include "cmenu.h"
#include "mainwindow.h"
#include <qboxlayout.h>
#include <qpushbutton.h>


CLeaderboard::CLeaderboard(MainWindow &window, QWidget *parent) : QWidget(parent), m_window(window) {}
void CLeaderboard::setupLeaderboard()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *title = new QLabel("TWOJE TOP 3 WYNIKI:");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    //tworzymy okno oraz wczytujemy do niego dane z klasy CReader
    int T[3] = {0, 0, 0};
    CReader reader;
    reader.ReadScore(T);

    //Pętla tworząca etykiety, do których wrzuca dane wcześniej wczytane
    for(int i = 0; i < 3; i++)
    {
        scoreLabels[i] = new QLabel(QString::number(i + 1) + ". Wynik: " + QString::number(T[i]) + " pkt");
        scoreLabels[i]->setAlignment(Qt::AlignCenter);
        layout->addWidget(scoreLabels[i]);
    }

    //Przycisk powrotu do menu
    QPushButton *btnBack = new QPushButton("Powrót");
    connect(btnBack, &QPushButton::clicked, this, &CLeaderboard::goMenu);

    btnBack->setFixedHeight(60);
    layout->addWidget(btnBack);

}
void CLeaderboard::showLeaderboard()
{
    int T[3] = {0, 0 ,0 };
    CReader reader;
    reader.ReadScore(T);

    for(int i = 0; i < 3; i++) {
        scoreLabels[i]->setText(QString::number(i + 1) + ". Wynik: " + QString::number(T[i]) + " pkt");
    }

    //po wciśnięciu przycisku stos wybiera okno 1 czyli leaderboard
    m_window.getStackedWidget()->setCurrentIndex(1);
}

void CLeaderboard::goMenu()
{
    m_window.getStackedWidget()->setCurrentIndex(0);
}
