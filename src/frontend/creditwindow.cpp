#include "creditwindow.h"

#include "ui_creditwindow.h"

CreditWindow::CreditWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::CreditWindow) {
  ui->setupUi(this);
  setFixedSize(480, 560);
}

CreditWindow::~CreditWindow() { delete ui; }

void CreditWindow::on_pushButton_return_clicked() {
  this->close();
  emit firstWindow();
}

void CreditWindow::on_pushButton_calc_released() {
  long double loan = ui->doubleSpinBox_3->text().toDouble();
  long double term = ui->doubleSpinBox_2->text().toDouble();
  if (ui->comboBox_2->currentIndex() == 1) term *= 12;
  long double rate = ui->doubleSpinBox->text().toDouble();
  ui->label_6->setText(ui->comboBox_3->currentText());
  ui->label_10->setText(ui->comboBox_3->currentText());
  ui->label_11->setText(ui->comboBox_3->currentText());
  if (ui->comboBox->currentIndex() == 0) {
    long double month_pay, overpay, total_pay;
    s21_credit_calc(loan, term, rate, &month_pay, &overpay, &total_pay);
    ui->Result_2->setText(QString::number(month_pay, 'f', 2));
    ui->Result_3->setText(QString::number(overpay, 'f', 2));
    ui->Result_4->setText(QString::number(total_pay, 'f', 2));
  } else {
    long double max, min, overpay, total_pay;
    s21_diff_credit_calc(loan, term, rate, &max, &min, &overpay, &total_pay);
    ui->Result_2->setText(QString::number(max, 'f', 2) + " .. " +
                          QString::number(min, 'f', 2));
    ui->Result_3->setText(QString::number(overpay, 'f', 2));
    ui->Result_4->setText(QString::number(total_pay, 'f', 2));
  }
}
