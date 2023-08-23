#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QWidget>

extern "C" {
#include "backend/s21_calc.h"
}

namespace Ui {
class CreditWindow;
}

class CreditWindow : public QWidget {
  Q_OBJECT

 public:
  CreditWindow(QWidget *parent = 0);
  ~CreditWindow();

 signals:
  void firstWindow();

 private slots:
  void on_pushButton_return_clicked();
  void on_pushButton_calc_released();

 private:
  Ui::CreditWindow *ui;
};

#endif  // CREDITWINDOW_H
