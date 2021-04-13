#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "draw.hpp"
#include "error.hpp"
#include "logger.h"
#include "manager.hpp"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene(0, 0, WIN_X, WIN_Y, this);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow() {
    event_t event;
    event_data_t event_d;

    event.cmd = QUIT;

    task_manager(event, event_d);

    delete ui;
}

int MainWindow::drawModel() {
    graphic_view_t field;
    field.scene = ui->graphicsView->scene();
    field.width = field.scene->width();
    field.height = field.scene->height();
    field.start_x = GRAPHIC_START_X;
    field.start_y = GRAPHIC_START_Y;

    event_t event;
    event_data_t event_d;

    event.cmd = DRAW;
    event_d.field = field;

    int res = task_manager(event, event_d);

    if (res) {
        error_manager(res);
        ERROR_PRINT("Draw model failed. Error code %d\n", res);
    }

    return res;
}

void MainWindow::on_rotateButton_clicked() {
    rotate_t rotate;
    rotate.ax = ui->rotate_x_box->value();
    rotate.ay = ui->rotate_y_box->value();
    rotate.az = ui->rotate_z_box->value();

    event_t event;
    event.cmd = ROTATE;

    event_data_t event_d;
    event_d.rotate = rotate;

    int res = task_manager(event, event_d);
    if (res) {
        error_manager(res);
        ERROR_PRINT("Rotate failed. Error code %d\n", res);
    } else {
        drawModel();
    }
}

void MainWindow::on_moveButton_clicked() {
    move_t move;
    move.x = ui->move_x_box->value();
    move.y = ui->move_y_box->value();
    move.z = ui->move_z_box->value();

    event_t event;
    event.cmd = MOVE;

    event_data_t event_d;
    event_d.move = move;

    int res = task_manager(event, event_d);
    if (res) {
        ERROR_PRINT("Move failed. Error code %d\n", res);
    } else {
        drawModel();
    }
}

void MainWindow::on_scaleButton_clicked() {
    scale_t scale;
    scale.kx = ui->scale_x_box->value();
    scale.ky = ui->scale_y_box->value();
    scale.kz = ui->scale_z_box->value();

    event_t event;
    event.cmd = SCALE;

    event_data_t event_d;
    event_d.scale = scale;

    int res = task_manager(event, event_d);
    if (res) {
        ERROR_PRINT("Scale failed. Error code %d\n", res);
    } else {
        drawModel();
    }
}

void MainWindow::on_loadModelButton_clicked() {
    event_t event;
    event_data_t event_d;

    event.cmd = LOAD_FROM_FILE;
    event_d.input_filename = ui->loadEdit->toPlainText()
                                 .toLocal8Bit()
                                 .data(); // because we are using c api, not c++

    int res = task_manager(event, event_d);

    if (res) {
        error_manager(res);
        ERROR_PRINT("Load failed. Error code %d\n", res);
    } else {
        drawModel();
    }
}

void MainWindow::on_saveModelButton_clicked() {
    event_t event;
    event_data_t event_d;

    event.cmd = SAVE_TO_FILE;
    event_d.output_filename =
        ui->saveEdit->toPlainText()
            .toLocal8Bit()
            .data(); // because we are using c api, not c++

    int res = task_manager(event, event_d);

    if (res) {
        error_manager(res);
        ERROR_PRINT("Save failed. Error code %d\n", res);
    } else {
        drawModel();
    }
}
