#include "qdebug.h"

#include "build/main_autogen_include/ui_mainwindow.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent),
                                          ui_(new Ui::MainWindow) {
    qDebug() << "Elevator is located at the floor #1, doors are closed.\n"
                "Elevator is being in waiting state.";
    ui_->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui_;
}

void MainWindow::on_button_cabin_1_clicked() {
    qDebug() << "Button 1 was pressed in elevator";
    lift.call(1);
}

void MainWindow::on_button_cabin_2_clicked() {
    qDebug() << "Button 2 was pressed in elevator";
    lift.call(2);
}

void MainWindow::on_button_cabin_3_clicked() {
    qDebug() << "Button 3 was pressed in elevator";
    lift.call(3);
}

void MainWindow::on_button_cabin_4_clicked() {
    qDebug() << "Button 4 was pressed in elevator";
    lift.call(4);
}

void MainWindow::on_button_cabin_5_clicked() {
    qDebug() << "Button 5 was pressed in elevator";
    lift.call(5);
}

void MainWindow::on_button_cabin_6_clicked() {
    qDebug() << "Button 6 was pressed in elevator";
    lift.call(6);
}

void MainWindow::on_button_cabin_7_clicked() {
    qDebug() << "Button 7 was pressed in elevator";
    lift.call(7);
}

void MainWindow::on_button_cabin_8_clicked() {
    qDebug() << "Button 8 was pressed in elevator";
    lift.call(8);
}

void MainWindow::on_button_cabin_9_clicked() {
    qDebug() << "Button 9 was pressed in elevator";
    lift.call(9);
}

void MainWindow::on_button_cabin_10_clicked() {
    qDebug() << "Button 10 was pressed in elevator";
    lift.call(10);
}

void MainWindow::on_button_floor_1_clicked() {
    qDebug() << "Elevator was called at the floor # 1";
    lift.call(1);
}

void MainWindow::on_button_floor_2_clicked() {
    qDebug() << "Elevator was called at the floor # 2";
    lift.call(2);
}

void MainWindow::on_button_floor_3_clicked() {
    qDebug() << "Elevator was called at the floor # 3";
    lift.call(3);
}

void MainWindow::on_button_floor_4_clicked() {
    qDebug() << "Elevator was called at the floor # 4";
    lift.call(4);
}

void MainWindow::on_button_floor_5_clicked() {
    qDebug() << "Elevator was called at the floor # 5";
    lift.call(5);
}

void MainWindow::on_button_floor_6_clicked() {
    qDebug() << "Elevator was called at the floor # 6";
    lift.call(6);
}

void MainWindow::on_button_floor_7_clicked() {
    qDebug() << "Elevator was called at the floor # 7";
    lift.call(7);
}

void MainWindow::on_button_floor_8_clicked() {
    qDebug() << "Elevator was called at the floor # 8";
    lift.call(8);
}

void MainWindow::on_button_floor_9_clicked() {
    qDebug() << "Elevator was called at the floor # 9";
    lift.call(9);
}

void MainWindow::on_button_floor_10_clicked() {
    qDebug() << "Elevator was called at the floor # 10";
    lift.call(10);
}
