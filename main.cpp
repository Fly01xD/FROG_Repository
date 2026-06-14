#include "mainwindow.h"
#include "CGame.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CGame g; // - kontener na grę
    MainWindow w(nullptr, &g);
    w.show();
    return QCoreApplication::exec();
}
