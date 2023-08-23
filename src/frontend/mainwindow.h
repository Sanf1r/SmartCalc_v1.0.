#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "creditwindow.h"

extern "C" {
#include "backend/s21_calc.h"
}

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

 private:
  Ui::MainWindow *ui;
  CreditWindow *sWindow;

 private slots:
  void digits_numbers();
  void on_pushButton_Dot_released();
  void operations();
  void on_pushButton_AC_released();
  void on_pushButton_Eq_released();
  void math_operations();
  void functions();
  void on_pushButton_left_released();
  void on_pushButton_right_released();
  void on_pushButton_degree_released();
  void on_pushButton_X_released();
  void makePlot();
  void on_pushButton_Graph_released();
  void on_radioButton_graph_toggled(bool checked);
  void on_pushButton_credit_released();
};

#endif  // MAINWINDOW_H
