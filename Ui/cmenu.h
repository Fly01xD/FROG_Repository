#ifndef CMENU_H
#define CMENU_H

#include <QWidget>

class MainWindow;

class CMenu : public QWidget {
    Q_OBJECT
public:
    CMenu(MainWindow &window, QWidget *parent = nullptr);

    //metoda wizualnego tworzenia funkcji
    void setupMenu();

private:
    MainWindow &m_window;

public slots:
    //metoda która pozwala wrócić nam do menu
    void goMenu();
};

#endif // CMENU_H
