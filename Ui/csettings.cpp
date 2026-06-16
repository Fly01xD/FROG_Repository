#include "csettings.h"
#include "cmenu.h"
#include "mainwindow.h"
#include <qboxlayout.h>
#include <qlabel.h>

CSettings::CSettings(MainWindow &window, QWidget *parent) : QWidget(parent), m_window(window) {}

void CSettings::setupSettings()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *title = new QLabel("USTAWIENIA");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    //Zmienna diffBtn będzie umożliwiała nam zmianę napisu na przycisku
    //w zaleźności od ustawionego poziomu trudności
    diffBtn = new QPushButton("Poziom: ŁATWY");
    connect(diffBtn, &QPushButton::clicked, this, &::CSettings::toggleDifficulty);

    QPushButton *btnBack = new QPushButton("Powrót");
    connect(btnBack, &QPushButton::clicked, this, &CSettings::goMenu);

    diffBtn->setFixedHeight(60);
    btnBack->setFixedHeight(60);

    layout->addWidget(diffBtn);
    layout->addWidget(btnBack);
}

void CSettings::showSettings()
{
    //przełączenie na scene z ustawieniami
    m_window.getStackedWidget()->setCurrentIndex(2);
}

void CSettings::toggleDifficulty()
{
    gameDifficulty &currentDiff = m_window.getDifficulty();
    if (currentDiff == easy)
    {
        currentDiff = medium;
        diffBtn->setText("Poziom: ŚREDNI");
    }
    else if (currentDiff == medium)
    {
        currentDiff = hard;
        diffBtn->setText("Poziom: TRUDNY");
    }
    else if (currentDiff == hard)
    {
        currentDiff = easy;
        diffBtn->setText("Poziom: ŁATWY");
    }
}

void CSettings::goMenu()
{
    m_window.getStackedWidget()->setCurrentIndex(0);
}
