#ifndef CLEADERBOARD_H
#define CLEADERBOARD_H

#include <QWidget>
#include <QLabel>
class MainWindow;

class CLeaderboard : public QWidget {
    Q_OBJECT
public:
    CLeaderboard(MainWindow &window, QWidget *parent = nullptr);
    //metoda stworzenia ui leaderboardu
    void setupLeaderboard();

    //metoda odświerzenia leaderboardu po kliknięciu przycisku oraz otwierania
    //widgetu setupLeaderboard czyli otwierania leaderboardu
    void showLeaderboard();
    void goMenu();
private:
    MainWindow &m_window;
    QLabel *scoreLabels[3];
};
#endif // CLEADERBOARD_H
