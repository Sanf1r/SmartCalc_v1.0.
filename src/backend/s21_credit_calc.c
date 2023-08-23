#include "s21_calc.h"

void s21_credit_calc(long double loan, long double term, long double rate,
                     long double* month_pay, long double* overpay,
                     long double* total_pay) {
  long double month_rate = rate / 12 / 100;
  long double ann_cof = (month_rate * powl(1 + month_rate, term)) /
                        (powl(1 + month_rate, term) - 1);
  long double payment = ann_cof * loan;
  *month_pay = payment;
  *overpay = payment * term - loan;
  *total_pay = loan + *overpay;
}

void s21_diff_credit_calc(long double loan, long double term, long double rate,
                          long double* max, long double* min,
                          long double* overpay, long double* total_pay) {
  long double month_rate = rate / 12 / 100;
  long double payment = loan / term;
  long double result, total;
  result = payment + (loan - payment * 0) * month_rate;
  *max = *min = total = result;
  for (int i = 1; i < term; i++) {
    result = payment + (loan - payment * i) * month_rate;
    if (result > *max) *max = result;
    if (result < *min) *min = result;
    total += result;
  }
  *overpay = total - loan;
  *total_pay = loan + *overpay;
}
