#include "mainwindow.h"
#include "cleaderboard.h"
#include "cmenu.h"
#include "cplay.h"
#include "csettings.h"

#include <QVBoxLayout>
#include <qgraphicsview.h>

MainWindow::MainWindow(QWidget *parent, CGame *_game): QMainWindow(parent)
{
    //Inicjalizacja stosu widgetów, który wybiera nr ideksu w zależności od tego
    //co kliknie urzytkownik
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    //Rezerwujemy pamięć pod ekrany które będą istaniały, dlatego że przyciski,
    //leaderboard czy ustawienia tworzą te widgety za pomocą metod, które istnieją w klasach
    //dlatego potrzebujemy wydzielonej pamięci na to
    menuScreen        = new CMenu(*this, this);
    leaderboardScreen = new CLeaderboard (*this, this);
    settingsScreen    = new CSettings(*this, this);
    playScreen        = new CPlay(*this, this);

    //tworzymy wizualnie wszystkie widgety, żeby móc im przydzielić odpowiednie indeksy
    menuScreen->setupMenu();
    leaderboardScreen->setupLeaderboard();
    settingsScreen->setupSettings();
    playScreen->setupGameView(_game);

    stackedWidget->addWidget(menuScreen);        // 0
    stackedWidget->addWidget(leaderboardScreen); // 1
    stackedWidget->addWidget(settingsScreen);    // 2
    stackedWidget->addWidget(playScreen);        // 3

    //ustawienie podstawowego rozmiaru okna
    // setWindowState(Qt::WindowFullScreen);

    //ustaienie indeksu na 0 czyli menu główne (po odpaleniu ma się wyświetlić menu)
    stackedWidget->setCurrentIndex(0);
}
MainWindow::~MainWindow() {}
