#ifndef CSETTINGS_H
#define CSETTINGS_H

#include <QWidget>
#include <QPushButton>
class MainWindow;

class CSettings : public QWidget {
    Q_OBJECT
public:
    CSettings(MainWindow &window, QWidget *parent = nullptr);

    //metoda tworząca ui settings
    void setupSettings();

    //metoda która otwiera settings po wciśnięciu przycisku
    void showSettings();

    //metoda która zmienia poziom trudności za pomocą przycisku
    void toggleDifficulty();
private:
    MainWindow &m_window;
    QPushButton *diffBtn;
};

#endif // CSETTINGS_H
