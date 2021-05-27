#include "mainwindow.h"
#include "design.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setup_scene();

    _facade = std::make_shared<Facade>(Facade());

    connect(ui->pushButton_load_model, &QPushButton::clicked, this, &MainWindow::on_pushButton_load_model_clicked);
    connect(ui->pushButton_del_model_cur, &QPushButton::clicked, this, &MainWindow::on_pushButton_del_model_cur_clicked);

    connect(ui->pushButton_add_camera, &QPushButton::clicked, this, &MainWindow::on_pushButton_add_camera_clicked);
    connect(ui->pushButton_del_camera_cur, &QPushButton::clicked, this, &MainWindow::on_pushButton_del_camera_cur_clicked);

    connect(ui->pushButton_del_model_all, &QPushButton::clicked, this, &MainWindow::on_pushButton_del_model_all_clicked);

    connect(ui->pushButton_camera_move_right, &QPushButton::clicked, this, &MainWindow::on_pushButton_camera_move_right_clicked);
    connect(ui->pushButton_camera_move_left, &QPushButton::clicked, this, &MainWindow::on_pushButton_camera_move_left_clicked);
    connect(ui->pushButton_camera_move_up, &QPushButton::clicked, this, &MainWindow::on_pushButton_camera_move_up_clicked);
    connect(ui->pushButton_camera_move_down, &QPushButton::clicked, this, &MainWindow::on_pushButton_camera_move_down_clicked);

    connect(ui->pushButton_move, &QPushButton::clicked, this, &MainWindow::on_pushButton_move_clicked);
    connect(ui->pushButton_scale, &QPushButton::clicked, this, &MainWindow::on_pushButton_scale_clicked);
    connect(ui->pushButton_spin, &QPushButton::clicked, this, &MainWindow::on_pushButton_spin_clicked);

    connect(ui->comboBox_cameras, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::change_cam);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setup_scene()
{
    _scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(_scene);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->graphicsView->setStyleSheet("QGraphicsView {background-color: white}");

    auto cont = ui->graphicsView->contentsRect();
    _scene->setSceneRect(0, 0, cont.width(), cont.height());

    std::shared_ptr<AbstractDrawerFactory> factory(new QtDrawerFactory(_scene));
    _drawer = factory->create_graphic();
}


void MainWindow::check_cam_exist()
{
    auto viewer_count = std::make_shared<size_t>(0);
    CameraCount viewer_cmd(viewer_count);

    _facade->execute(viewer_cmd);

    if (!*viewer_count) {
        std::string msg = "No camera found.";
        throw CameraError(msg);
    }
}


void MainWindow::check_can_delete_cam() {
    auto model_count = std::make_shared<size_t>(0);
    ModelCount model_cmd(model_count);
    _facade->execute(model_cmd);

    auto viewer_count = std::make_shared<size_t>(0);
    CameraCount viewer_cmd(viewer_count);
    _facade->execute(viewer_cmd);

    if (*viewer_count <= 1 && *model_count) {
        std::string msg = "Can not delete the last camera with the loaded models";
        throw CameraError(msg);
    }
}


void MainWindow::check_models_exist()
{
    auto model_count = std::make_shared<size_t>(0);
    ModelCount model_cmd(model_count);
    _facade->execute(model_cmd);

    if (!*model_count) {
        std::string msg = "No models found.";
        throw ModelError(msg);
    }
}


void MainWindow::on_pushButton_move_clicked()
{
    try
    {
        check_cam_exist();
        check_models_exist();
    }
    catch (const CameraError &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
        return;
    }
    catch (const ModelError &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной модели");
        return;
    }

    MoveModel move_cmd(
            ui->doubleSpinBox_move_x->value(),
            ui->doubleSpinBox_move_y->value(),
            ui->doubleSpinBox_move_z->value(),
            ui->comboBox_models->currentIndex());

    _facade->execute(move_cmd);
    update_scene();
}

void MainWindow::on_pushButton_scale_clicked()
{
    try
    {
        check_cam_exist();
        check_models_exist();
    }
    catch (const CameraError &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
        return;
    }
    catch (const ModelError &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной модели");
        return;
    }

    ScaleModel scale_cmd(
            ui->doubleSpinBox_scale_x->value(),
            ui->doubleSpinBox_scale_y->value(),
            ui->doubleSpinBox_scale_z->value(),
            ui->comboBox_models->currentIndex());

    _facade->execute(scale_cmd);
    update_scene();
}

void MainWindow::on_pushButton_spin_clicked()
{
    try
    {
        check_cam_exist();
        check_models_exist();
    }
    catch (const CameraError &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
        return;
    }
    catch (const ModelError &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной модели");
        return;
    }

    RotateModel rotate_cmd(
            ui->doubleSpinBox_spin_x->value(),
            ui->doubleSpinBox_spin_y->value(),
            ui->doubleSpinBox_spin_z->value(),
            ui->comboBox_models->currentIndex());

    _facade->execute(rotate_cmd);
    update_scene();
}

void MainWindow::on_pushButton_del_model_cur_clicked()
{
    try
    {
        check_models_exist();
    }
    catch (const ModelError &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Прежде чем удалять модель, добавьте хотя бы одну.");
        return;
    }

    RemoveModel remove_command(ui->comboBox_models->currentIndex());
    _facade->execute(remove_command);

    ui->comboBox_models->removeItem(ui->comboBox_models->currentIndex());

    update_scene();
}

void MainWindow::on_pushButton_del_model_all_clicked()
{
    try
    {
        check_models_exist();
    }
    catch (const ModelError &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Прежде чем удалять модели, добавьте хотя бы одну.");
        return;
    }

    for (int i = ui->comboBox_models->count() - 1; i >= 0; --i)
    {
        RemoveModel remove_command(i);
        _facade->execute(remove_command);

        ui->comboBox_models->removeItem(i);
    }

    update_scene();
}

void MainWindow::on_pushButton_load_model_clicked()
{
    try
    {
        check_cam_exist();
    }
    catch (const CameraError &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Прежде чем добавлять модель, добавьте хотя бы одну камеру.");
        return;
    }

    auto file = QFileDialog::getOpenFileName();

    if (file.isNull())
        return;

    auto smth = file.toUtf8().data();

    LoadModel load_command(smth);

    try
    {
        _facade->execute(load_command);
    }
    catch (const CameraError &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Что-то пошло не так при загрузке файла...");
        return;
    }

    update_scene();
    ui->comboBox_models->addItem(QFileInfo(file.toUtf8().data()).fileName());
    ui->comboBox_models->setCurrentIndex(ui->comboBox_models->count() - 1);
}

void MainWindow::on_pushButton_camera_move_up_clicked()
{
    try
    {
        check_cam_exist();
        check_models_exist();
    }
    catch (const CameraError &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
        return;
    }
    catch (const ModelError &error) {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной модели");
        return;
    }

    MoveCamera camera_command(ui->comboBox_cameras->currentIndex(), 0, 10);
    _facade->execute(camera_command);
    update_scene();
}

void MainWindow::on_pushButton_camera_move_left_clicked()
{
    try
    {
        check_cam_exist();
        check_models_exist();
    }
    catch (const CameraError &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
        return;
    }
    catch (const ModelError &error) {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной модели");
        return;
    }

    MoveCamera camera_command(ui->comboBox_cameras->currentIndex(), 10, 0);
    _facade->execute(camera_command);
    update_scene();
}

void MainWindow::on_pushButton_camera_move_down_clicked()
{
    try
    {
        check_cam_exist();
        check_models_exist();
    }
    catch (const CameraError &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
        return;
    }
    catch (const ModelError &error) {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной модели");
        return;
    }

    MoveCamera camera_command(ui->comboBox_cameras->currentIndex(), 0, -10);
    _facade->execute(camera_command);
    update_scene();
}

void MainWindow::on_pushButton_camera_move_right_clicked()
{
    try
    {
        check_cam_exist();
        check_models_exist();
    }
    catch (const CameraError &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
        return;
    }
    catch (const ModelError &error) {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной модели");
        return;
    }

    MoveCamera camera_command(ui->comboBox_cameras->currentIndex(), -10, 0);
    _facade->execute(camera_command);
    update_scene();
}

void MainWindow::on_pushButton_del_camera_cur_clicked()
{
    try
    {
        check_cam_exist();
    }
    catch (const CameraError &error) {
        QMessageBox::critical(nullptr, "Ошибка", "Прежде чем удалять камеру, добавьте хотя бы одну.");
        return;
    }

    try
    {
        check_can_delete_cam();
    }
    catch (const CameraError &error) {
        QMessageBox::critical(nullptr, "Ошибка", "Прежде чем удалять камеру, необходимо удалить оставшиеся модели.");
        return;
    }

    RemoveCamera remove_command(ui->comboBox_cameras->currentIndex());
    _facade->execute(remove_command);

    ui->comboBox_cameras->removeItem(ui->comboBox_cameras->currentIndex());

    try
    {
        check_cam_exist();
    }
    catch (const CameraError &error)
    {
        return;
    }

    update_scene();
}

void MainWindow::on_pushButton_add_camera_clicked()
{
    auto cont = ui->graphicsView->contentsRect();
    AddCamera camera_command(cont.width() / 2.0, cont.height() / 2.0, 0.0);
    _facade->execute(camera_command);

    update_scene();

    auto cam = ui->comboBox_cameras;

    if (0 == cam->count())
        cam->addItem(QString::number(1));
    else
        cam->addItem(QString::number(cam->itemText(cam->count() - 1).toInt() + 1));

    ui->comboBox_cameras->setCurrentIndex(ui->comboBox_cameras->count() - 1);
}


void MainWindow::update_scene()
{
    DrawScene draw_command(_drawer);
    _facade->execute(draw_command);
}


void MainWindow::change_cam()
{
    try
    {
        check_cam_exist();
    }
    catch (const CameraError &error)
    {
        return;
    }

    SetCamera camera_command(ui->comboBox_cameras->currentIndex());
    _facade->execute(camera_command);
    update_scene();
}


void MainWindow::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);

    _scene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());

    auto cont = ui->graphicsView->contentsRect();
    _scene->setSceneRect(0, 0, cont.width(), cont.height());
}

