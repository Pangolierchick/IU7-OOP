#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
