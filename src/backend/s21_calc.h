#ifndef SRC_S21_CALC_H_
#define SRC_S21_CALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack_num {
  long double data;
  struct stack_num* next;
} stack_num;

typedef struct stack_char {
  char* op;
  struct stack_char* next;
} stack_char;

enum result_code { OK, CALCULATION_ERROR };

void s21_push_num(stack_num** head, long double value);
long double s21_pop_num(stack_num** head);
long double s21_eval(char op, char dop, stack_num** head);
int s21_need(char op);
int s21_isnum(char* number);
long double s21_RPN_answer(char** str, double x, int* code);
char* s21_peek_char(stack_char** head);
void s21_push_char(stack_char** head, char* value);
char* s21_pop_char(stack_char** head);
int s21_isfunc(char* string);
int s21_isop(char* string);
int s21_score(char* string);
void s21_lexems(char* str, char** lexems);
int s21_strings_for_eval(char** lexems, char** temp_out, char** RPN);
int s21_varification(char** string);
int s21_check_axis(double a, double b);
void s21_credit_calc(long double loan, long double term, long double rate,
                     long double* month_pay, long double* overpay,
                     long double* total_pay);
void s21_diff_credit_calc(long double loan, long double term, long double rate,
                          long double* max, long double* min,
                          long double* overpay, long double* total_pay);

#endif  // SRC_S21_CALC_H_
