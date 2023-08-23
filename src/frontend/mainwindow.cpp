#include "mainwindow.h"

#include <QMessageBox>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setFixedSize(430, 610);
  sWindow = new CreditWindow();
  connect(sWindow, &CreditWindow::firstWindow, this, &MainWindow::show);
  connect(ui->pushButton_0, SIGNAL(released()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(released()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(released()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(released()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(released()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(released()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(released()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(released()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(released()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_Sign, SIGNAL(released()), this, SLOT(operations()));
  connect(ui->pushButton_Plus, SIGNAL(released()), this,
          SLOT(math_operations()));
  connect(ui->pushButton_Minus, SIGNAL(released()), this,
          SLOT(math_operations()));
  connect(ui->pushButton_Mul, SIGNAL(released()), this,
          SLOT(math_operations()));
  connect(ui->pushButton_Div, SIGNAL(released()), this,
          SLOT(math_operations()));
  connect(ui->pushButton_mod, SIGNAL(released()), this,
          SLOT(math_operations()));
  connect(ui->pushButton_sqrt, SIGNAL(released()), this, SLOT(functions()));
  connect(ui->pushButton_ln, SIGNAL(released()), this, SLOT(functions()));
  connect(ui->pushButton_log, SIGNAL(released()), this, SLOT(functions()));
  connect(ui->pushButton_sin, SIGNAL(released()), this, SLOT(functions()));
  connect(ui->pushButton_cos, SIGNAL(released()), this, SLOT(functions()));
  connect(ui->pushButton_tan, SIGNAL(released()), this, SLOT(functions()));
  connect(ui->pushButton_asin, SIGNAL(released()), this, SLOT(functions()));
  connect(ui->pushButton_acos, SIGNAL(released()), this, SLOT(functions()));
  connect(ui->pushButton_atan, SIGNAL(released()), this, SLOT(functions()));
MainWindow:
  makePlot();
}

MainWindow::~MainWindow() {
  delete ui;
  delete sWindow;
}

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  if (ui->Result_2->text().endsWith("+") ||
      ui->Result_2->text().endsWith("-") ||
      ui->Result_2->text().endsWith("*") ||
      ui->Result_2->text().endsWith("/") ||
      ui->Result_2->text().endsWith("d") ||
      ui->Result_2->text().endsWith("(") || ui->Result_2->text().isEmpty() ||
      ui->Result_2->text().endsWith("^")) {
    if (!(ui->Result_2->text().endsWith("X"))) {
      ui->Result->setText(ui->Result->text() + button->text());
    }
  }
}

void MainWindow::on_pushButton_Dot_released() {
  if (!(ui->Result->text().contains('.')) && !(ui->Result->text().isEmpty()))
    ui->Result->setText(ui->Result->text() + ".");
}

void MainWindow::operations() {
  QPushButton *button = (QPushButton *)sender();

  if (button->text() == "+/-" && !ui->Result->text().isEmpty()) {
    if (ui->Result->text().contains('-')) {
      ui->Result->setText(ui->Result->text().replace("-", ""));
    } else {
      ui->Result->setText(ui->Result->text().insert(0, "-"));
    }
  }
}

void MainWindow::math_operations() {
  QPushButton *button = (QPushButton *)sender();

  if ((ui->Result_2->text().endsWith("-") ||
       ui->Result_2->text().endsWith("+") ||
       ui->Result_2->text().endsWith("*") ||
       ui->Result_2->text().endsWith("/")) &&
      ui->Result->text() == "") {
    QString str = ui->Result_2->text();
    str.chop(1);
    ui->Result_2->setText(str + button->text());
  } else if (ui->Result_2->text().endsWith("d") && ui->Result->text() == "") {
    QString str = ui->Result_2->text();
    str.chop(3);
    ui->Result_2->setText(str + button->text());
  } else {
    ui->Result_2->setText(ui->Result_2->text() + ui->Result->text());
    ui->Result_2->setText(ui->Result_2->text() + button->text());
    ui->FinalLine->setText(ui->FinalLine->text() + ui->Result->text() + "|" +
                           button->text() + "|");
    ui->Result->setText("");
  }
}

void MainWindow::on_pushButton_AC_released() {
  ui->FinalLine->setText("");
  ui->Result_2->setText("");
  ui->Result->setText("");
}

void MainWindow::on_pushButton_Eq_released() {
  ui->Result_2->setText(ui->Result_2->text() + ui->Result->text());
  ui->FinalLine->setText(ui->FinalLine->text() + ui->Result->text());

  ui->Result_2->setText(ui->Result_2->text() + "=");
  QString temp_str = ui->FinalLine->text();
  ui->FinalLine->setText("");
  QByteArray array = temp_str.toLocal8Bit();
  char *str = array.data();
  long double result;
  char *lexems[255] = {0};
  char *temp_out[255] = {0};
  char *RPN[255] = {0};
  int code = OK;
  s21_lexems(str, lexems);
  double x = (ui->doubleSpinBox_x->text().toDouble());
  if (s21_strings_for_eval(lexems, temp_out, RPN) || s21_varification(RPN)) {
    ui->Result->setText("");
    ui->Result_2->setText("Error!");
  } else {
    result = s21_RPN_answer(RPN, x, &code);
    if (code) {
      ui->Result->setText("");
      ui->Result_2->setText("Error!");
    } else {
      QString final = QString::number(result, 'g', 16);
      ui->Result->setText(final);
    }
  }
}

void MainWindow::on_pushButton_left_released() {
  QPushButton *button = (QPushButton *)sender();
  ui->Result_2->setText(ui->Result_2->text() + "(");
  if (ui->FinalLine->text().endsWith("|")) {
    ui->FinalLine->setText(ui->FinalLine->text() + button->text() + "|");
  } else {
    ui->FinalLine->setText(ui->FinalLine->text() + "|" + button->text() + "|");
  }
}

void MainWindow::on_pushButton_right_released() {
  QPushButton *button = (QPushButton *)sender();
  ui->Result_2->setText(ui->Result_2->text() + ui->Result->text() + ")");
  ui->FinalLine->setText(ui->FinalLine->text() + ui->Result->text() + "|" +
                         button->text() + "|");
  ui->Result->setText("");
}

void MainWindow::on_pushButton_degree_released() {
  QPushButton *button = (QPushButton *)sender();
  ui->Result_2->setText(ui->Result_2->text() + ui->Result->text() + "^");
  ui->FinalLine->setText(ui->FinalLine->text() + ui->Result->text() + "|" +
                         button->text() + "|");
  ui->Result->setText("");
}

void MainWindow::functions() {
  QPushButton *button = (QPushButton *)sender();
  ui->Result_2->setText(ui->Result_2->text() + button->text() + "(");
  if (ui->FinalLine->text().endsWith("|")) {
    ui->FinalLine->setText(ui->FinalLine->text() + button->text() + "|(|");
  } else {
    ui->FinalLine->setText(ui->FinalLine->text() + "|" + button->text() +
                           "|(|");
  }
}

void MainWindow::on_pushButton_X_released() {
  QPushButton *button = (QPushButton *)sender();
  if ((ui->Result_2->text().endsWith("(") ||
       ui->Result_2->text().endsWith("+") ||
       ui->Result_2->text().endsWith("-") ||
       ui->Result_2->text().endsWith("*") ||
       ui->Result_2->text().endsWith("/") ||
       ui->Result_2->text().endsWith("d") ||
       ui->Result_2->text().endsWith("^") || ui->Result_2->text().isEmpty()) &&
      ui->Result->text().isEmpty()) {
    ui->Result_2->setText(ui->Result_2->text() + "X");
    ui->FinalLine->setText(ui->FinalLine->text() + button->text());
  }
}

void MainWindow::makePlot() {
  ui->customPlot->addGraph();
  ui->customPlot->xAxis->setLabel("x");
  ui->customPlot->yAxis->setLabel("y");
  ui->customPlot->xAxis2->setVisible(true);
  ui->customPlot->xAxis2->setTickLabels(false);
  ui->customPlot->yAxis2->setVisible(true);
  ui->customPlot->yAxis2->setTickLabels(false);
  connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)),
          ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)),
          ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));
  ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  ui->customPlot->xAxis->setRange(-10, 10);
  ui->customPlot->yAxis->setRange(-10, 10);
}

void MainWindow::on_pushButton_Graph_released() {
  if (ui->radioButton_graph->isChecked()) {
    double a = ui->doubleSpinBox_x_left->value();
    double b = ui->doubleSpinBox_x_right->value();
    double step = ui->doubleSpinBox_step->value();
    double k = ui->doubleSpinBox_y_left->value();
    double l = ui->doubleSpinBox_y_right->value();
    QString temp_str = ui->FinalLine->text();
    QByteArray array = temp_str.toLocal8Bit();
    char *str = array.data();
    long double result;
    char *lexems[255] = {0};
    char *temp_out[255] = {0};
    char *RPN[255] = {0};
    int code = OK;
    s21_lexems(str, lexems);
    if (s21_check_axis(a, b) || s21_check_axis(k, l)) {
      ui->Result_2->setText("Axis Error!");
      ui->customPlot->clearGraphs();
      ui->customPlot->replot();
    } else {
      if (s21_strings_for_eval(lexems, temp_out, RPN) ||
          s21_varification(RPN)) {
        ui->Result->setText("");
        ui->Result_2->setText("Error!");
      } else {
        unsigned int N = ((b - a) / step) + 1;
        double c = a;
        QVector<double> x(N), y(N);
        for (int i = 0; i < N;) {
          result = s21_RPN_answer(RPN, c, &code);
          if (code) {
            ui->Result->setText("");
            ui->Result_2->setText("Error!");
            break;
          }
          if (result <= k || result >= l) {
            c += step;
            x[i] = c;
            y[i++] = qQNaN();
          } else {
            x[i] = c;
            y[i++] = result;
            c += step;
          }
        }
        ui->customPlot->clearGraphs();
        ui->customPlot->addGraph();
        if (!code) ui->customPlot->graph(0)->setData(x, y);
        ui->customPlot->xAxis->setLabel("x");
        ui->customPlot->yAxis->setLabel("y");
        ui->customPlot->xAxis2->setVisible(true);
        ui->customPlot->xAxis2->setTickLabels(false);
        ui->customPlot->yAxis2->setVisible(true);
        ui->customPlot->yAxis2->setTickLabels(false);
        connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)),
                ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
        connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)),
                ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));
        ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
        ui->customPlot->xAxis->rescale();
        ui->customPlot->yAxis->rescale();
        if (ui->comboBox_style->currentIndex() == 0) {
        } else {
          ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
          ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
        }
        ui->customPlot->replot();
      }
    }
  }
}

void MainWindow::on_radioButton_graph_toggled(bool checked) {
  if (checked) {
    setFixedSize(865, 610);
  } else {
    setFixedSize(430, 610);
  }
}

void MainWindow::on_pushButton_credit_released() {
  sWindow->show();
  this->close();
}
