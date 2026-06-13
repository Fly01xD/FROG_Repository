#include "mainwindow.h"
#include "CGame.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    CGame game; // - kontener na grę
    w.show();
    return QCoreApplication::exec();
}
