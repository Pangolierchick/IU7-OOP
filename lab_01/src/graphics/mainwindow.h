#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#define WIN_X 911
#define WIN_Y 771

#define GRAPHIC_START_X 270
#define GRAPHIC_START_Y 0

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_rotateButton_clicked();

  void on_moveButton_clicked();

  void on_scaleButton_clicked();

  void on_loadModelButton_clicked();

  void on_saveModelButton_clicked();

  int drawModel();

private:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
