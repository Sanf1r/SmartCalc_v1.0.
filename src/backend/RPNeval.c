#include "s21_calc.h"

long double s21_eval(char op, char dop, stack_num** head) {
  long double temp;
  long double result;
  switch (op) {
    case '+':
      result = s21_pop_num(head) + s21_pop_num(head);
      break;
    case '*':
      result = s21_pop_num(head) * s21_pop_num(head);
      break;
    case '-':
      temp = s21_pop_num(head);
      result = s21_pop_num(head) - temp;
      break;
    case '/':
      temp = s21_pop_num(head);
      result = s21_pop_num(head) / temp;
      break;
    case '^':
      temp = s21_pop_num(head);
      result = powl(s21_pop_num(head), temp);
      break;
    case 'm':
      temp = s21_pop_num(head);
      result = fmodl(s21_pop_num(head), temp);
      break;
    case 's':
      switch (dop) {
        case 'q':
          result = sqrtl(s21_pop_num(head));
          break;
        default:
          result = sinl(s21_pop_num(head));
          break;
      }
      break;
    case 'c':
      result = cosl(s21_pop_num(head));
      break;
    case 't':
      result = tanl(s21_pop_num(head));
      break;
    case 'a':
      switch (dop) {
        case 's':
          result = asinl(s21_pop_num(head));
          break;
        case 'c':
          result = acosl(s21_pop_num(head));
          break;
        case 't':
          result = atanl(s21_pop_num(head));
          break;
      }
      break;
    case 'l':
      switch (dop) {
        case 'n':
          result = logl(s21_pop_num(head));
          break;
        case 'o':
          result = log10l(s21_pop_num(head));
          break;
      }
      break;
  }
  return result;
}

int s21_need(char op) {
  int result;
  switch (op) {
    case '+':
    case '*':
    case '-':
    case '/':
    case '^':
    case 'm':
      result = 2;
      break;
    case 's':
    case 'c':
    case 't':
    case 'a':
    case 'l':
      result = 1;
      break;
  }
  return result;
}

long double s21_RPN_answer(char** str, double x, int* code) {
  long double result = 0;
  stack_num* head = NULL;
  int stacksize = 0;
  long double temp;
  char op, dop = ' ';

  for (int i = 0; str[i]; i++) {
    char* token = str[i];

    if (s21_isnum(token)) {
      if (!(strcmp(token, "X"))) {
        temp = x;
      } else {
        temp = atof(token);
      }
      s21_push_num(&head, temp);
      stacksize++;
    } else {
      op = token[0];
      if (stacksize < s21_need(op)) {
        *code = CALCULATION_ERROR;
        break;
      }
      if (strlen(token) > 1) dop = token[1];
      s21_push_num(&head, s21_eval(op, dop, &head));
      stacksize -= s21_need(op) - 1;
    }
  }
  if (stacksize == 1) {
    result = s21_pop_num(&head);
  } else {
    *code = CALCULATION_ERROR;
    while (stacksize) {
      s21_pop_num(&head);
      stacksize--;
    }
  }

  return result;
}
