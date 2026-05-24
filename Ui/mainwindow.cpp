#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "gamescene.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GameScene* SGame = new GameScene(gameDifficulty::easy);
    ui->graphicsView->setScene(SGame);
}

MainWindow::~MainWindow()
{
    delete ui;
}
