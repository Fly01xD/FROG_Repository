#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "croad.h"

//deklarujemy klasy, żeby program wiedział, że istnieją nie możemy zastąpić
//ich include ponieważ doprowadziłoby to do nieskończonej pętli
class CMenu;
class CLeaderboard;
class CSettings;
class CPlay;
class CAI;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //gettery zwracające adres konkretnej sceny
    QStackedWidget* getStackedWidget() {return stackedWidget; }
    CMenu* getMenu()                   {return menuScreen; }
    CLeaderboard* getLeaderboard()     {return leaderboardScreen; }
    CSettings* getSettings()           {return settingsScreen; }
    CPlay* getPlay()                   {return playScreen; }
    CAI* getAI()                       {return AIScreen; }
    gameDifficulty& getDifficulty()    {return currentDiff; }

private:
    QStackedWidget *stackedWidget;
    gameDifficulty currentDiff = easy;

    CMenu *menuScreen;
    CLeaderboard *leaderboardScreen;
    CSettings *settingsScreen;
    CPlay *playScreen;
    CAI* AIScreen;
};
#endif // MAINWINDOW_H