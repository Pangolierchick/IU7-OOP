#include <cstdio>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    scene->setSceneRect(0, 0, WIN_X, WIN_Y);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_rotateButton_clicked()
{

}

void MainWindow::on_moveButton_clicked()
{

}

void MainWindow::on_scaleButton_clicked()
{

}

void MainWindow::on_loadModelButton_clicked()
{

}

void MainWindow::on_saveModelButton_clicked()
{

}
