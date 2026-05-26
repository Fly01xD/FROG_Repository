#include "mainwindow.h"

#include <QVBoxLayout>
#include <qgraphicsview.h>
#include "creader.h"
#include "gamescene.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
//AI powiedział, że skoro budujemy kod ręcznie to to jest zbędne:
//, ui(new Ui::MainWindow)
//ui->setupUi(this);
{
    //Inicjalizacja okien, które będą się podmieniały w zależności od tego
    //co kliknie urzytkownik
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // GameScene* SGame = new GameScene(gameDifficulty::easy);
    // ui->graphicsView->setScene(SGame);

    //gra nie istnieje dopuki urzytkownik nie kliknie graj
    sGame = nullptr;

    //inicjalizujemy funckję w odopwiedniej kolejności aby nadać im
    //odpowiednie indeksy (od 0 do 3)
    setupMenu();          //0
    setupLeaderboard();   //1
    setupSettings();      //2
    setupGameView();      //3

    stackedWidget->setCurrentIndex(0);
}

void MainWindow::setupMenu()
{
    menuScene = new QWidget();
    //to odpowiada za pionowe ustawienie elementów
    QVBoxLayout *layout = new QVBoxLayout(menuScene);

    QLabel *title = new QLabel("MENU GŁÓWNE");
    title->setAlignment(Qt::AlignCenter);

    QPushButton *btnGraj = new QPushButton("Graj");
    QPushButton *btnLead = new QPushButton("Leaderboard");
    QPushButton *btnAI = new QPushButton("Tryb AI");
    QPushButton *btnSett = new QPushButton("Ustawienia");

    //każdy stworzony przycisk oraz napis będzie pionowo ustawiony dzięki temu:
    layout->addWidget(title);
    layout->addWidget(btnGraj);
    layout->addWidget(btnLead);
    layout->addWidget(btnAI);
    layout->addWidget(btnSett);

    connect(btnGraj, &QPushButton::clicked, this, &MainWindow::Play);
    connect(btnLead, &QPushButton::clicked, this, &MainWindow::showLeaderboard);
    connect(btnAI, &QPushButton::clicked, this, &MainWindow::startAI);
    connect(btnSett, &QPushButton::clicked, this, &MainWindow::showSettings);

    //dodanie stworzonego ekranu do stosu:
    stackedWidget->addWidget(menuScene);
}

void MainWindow::setupLeaderboard()
{
    leaderboardScene = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(leaderboardScene);

    QLabel *title = new QLabel("TWOJE TOP 3 WYNIKI:");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    //tworzymy okno oraz wczytujemy do niego dane z klasy CReader
    int T[3];
    CReader reader;
    reader.ReadScore(T);

    //Pętla tworząca etykiety, do których wrzuca dane wcześniej wczytane
    for(int i = 0; i < 3; i++) {
        scoreLabels[i] = new QLabel(QString::number(i + 1) + ". Wynik: " + QString::number(T[i]) + " pkt");
        scoreLabels[i]->setAlignment(Qt::AlignCenter);
        layout->addWidget(scoreLabels[i]);
    }

    //Przycisk powrotu do menu
    QPushButton *btnBack = new QPushButton("Powrót");
    connect(btnBack, &QPushButton::clicked, this, &MainWindow::goMenu);

    layout->addWidget(btnBack);

    //dodanie stworzonego ekranu do stosu:
    stackedWidget->addWidget(leaderboardScene);
}

void MainWindow::setupSettings()
{
    settingsScene = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(settingsScene);

    QLabel *title = new QLabel("USTAWIENIA");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    //Zmienna diffBtn będzie umożliwiała nam zmianę napisu na przycisku
    //w zaleźności od ustawionego poziomu trudności
    diffBtn = new QPushButton("Poziom: ŁATWY");
    connect(diffBtn, &QPushButton::clicked, this, &MainWindow::toggleDifficulty);

    QPushButton *btnBack = new QPushButton("Powrót");
    connect(btnBack, &QPushButton::clicked, this, &MainWindow::goMenu);

    layout->addWidget(diffBtn);
    layout->addWidget(btnBack);

    //dodanie ekranu do stosu wszystkich ekranów:
    stackedWidget->addWidget(settingsScene);
}

void MainWindow::setupGameView()
{
    //Trzeba napisać kamere do gry
    //na końcu dodać: stackedWidget->addWidget(gameView);
}

void MainWindow::Play()
{
    if(sGame == nullptr)
    {
        //stowrzenie nowej gry ale tylko wtedy jeśli jeszcze nie istnieje
        //po przegranej albo po odpaleniu aplikacji
        sGame = new GameScene (currentDifficulty);

        //ustawienie kamery na nową planszę
        gameView->setScene(sGame);

        //po wciśnięci przycisku graj stos wybiera okno 3 czyli
        //główne okno gry
        stackedWidget->setCurrentIndex(3);
    }
}

void MainWindow::showLeaderboard()
{
    //jeśli zostanie pobity rekord to wtedy funckja ponownie wczyta pliki
    //i odświerzy leaderboard tak żeby był aktualny
    int T[3];
    CReader reader;
    reader.ReadScore(T);

    for(int i = 0; i < 3; i++) {
        scoreLabels[i]->setText(QString::number(i + 1) + ". Wynik: " + QString::number(T[i]) + " pkt");
    }

    //po wciśnięciu przycisku stos wybiera okno 1 czyli leaderboard
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::showSettings()
{
    //przełączenie na scene z ustawieniami
    stackedWidget->setCurrentIndex(2);
}

void MainWindow::toggleDifficulty()
{
    //Jeśli wcisniemy przycisk na poziomie easy (currentDifficulty == easy)
    //to po wciśnięciu przycisku trudność musi się zmienić na medium
    if (currentDifficulty == easy)
    {
        currentDifficulty = medium;
        diffBtn->setText("Poziom: ŚREDNI");
    }
    else if (currentDifficulty == medium)
    {
        currentDifficulty = hard;
        diffBtn->setText("Poziom: TRUDNY");
    }
    else if (currentDifficulty == hard)
    {
        currentDifficulty = easy;
        diffBtn->setText("Poziom: ŁATWY");
    }
}

void MainWindow::goMenu()
{
    //przechodzimy do menu czyli indeksu 0
    stackedWidget->setCurrentWidget(0);
}

void MainWindow::startAI()
{
    //trzeba napisać AI;
}

MainWindow::~MainWindow()
{
    //Jeśli była stworzona plansza gry to zostaje usunięta z pamięci
    if(sGame!=nullptr)
    {
        delete sGame;
    }
    delete ui;
}