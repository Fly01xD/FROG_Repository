#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "croad.h"
#include "gamescene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;

    //Funckje służące do reagowania na naciśnięcie przyciskóW
    void Play();
    void showLeaderboard();
    void showSettings();
    void startAI();
    void toggleDifficulty();
    void goMenu();

    //Tutaj wypisane są jakie będą sceny (trzeba jeszcze dopisać tą główną)
    QWidget *menuScene;
    QWidget *leaderboardScene;
    QWidget *settingsScene;

    //To będzie nam pozwalało przechodzić między oknami
    QStackedWidget *stackedWidget;

    //"Kamera" żeby nasza gra była 2D i się poruszała
    QGraphicsView *gameView;
    //plansza do grania
    GameScene *sGame;

    //Dzięki temu ustawienia będą wiedziały jaki jest poziom trudności
    //Początkowo poziom trudności to easy
    gameDifficulty currentDifficulty = easy;

    //Przycisk od zmiany trudności (po kliknięci się zmienia)
    QPushButton *diffBtn;

    //sczytywanie wyników do sceny Leaderboard z CReadera
    QLabel *scoreLabels[3];

    //Funkcje tworzące sceny:
    void setupMenu();
    void setupLeaderboard();
    void setupSettings();
    void setupGameView();
};
#endif // MAINWINDOW_H