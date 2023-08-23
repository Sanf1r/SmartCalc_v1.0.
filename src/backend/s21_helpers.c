#include "s21_calc.h"

void s21_push_num(stack_num** head, long double value) {
  stack_num* node = malloc(sizeof(stack_num));

  if (node != NULL) {
    node->data = value;
    node->next = *head;
    *head = node;
  }
}

long double s21_pop_num(stack_num** head) {
  long double value = 0;
  if (*head != NULL) {
    stack_num* top = *head;
    value = top->data;
    *head = top->next;
    free(top);
  }
  return value;
}

char* s21_peek_char(stack_char** head) {
  stack_char* top = *head;
  return top->op;
}

void s21_push_char(stack_char** head, char* value) {
  stack_char* node = malloc(sizeof(stack_char));

  if (node != NULL) {
    node->op = value;
    node->next = *head;
    *head = node;
  }
}

char* s21_pop_char(stack_char** head) {
  stack_char* top = *head;
  char* value = top->op;
  *head = top->next;
  free(top);
  return value;
}

int s21_isnum(char* number) {
  int code = 1;
  char* str = number;
  for (; *number; number++) {
    if ((*number == '-' || *number == '+') && strlen(str) == 1) {
      code = 0;
      break;
    }
    if (*number != '.' && *number != '0' && *number != '1' && *number != '2' &&
        *number != '3' && *number != '4' && *number != '5' && *number != '6' &&
        *number != '7' && *number != '8' && *number != '9' && *number != '-' &&
        *number != '+' && *number != 'X') {
      code = 0;
      break;
    }
  }

  return code;
}

int s21_isfunc(char* string) {
  int code = 0;
  if (!strcmp(string, "sin") || !strcmp(string, "cos") ||
      !strcmp(string, "tan") || !strcmp(string, "asin") ||
      !strcmp(string, "acos") || !strcmp(string, "atan") ||
      !strcmp(string, "sqrt") || !strcmp(string, "ln") ||
      !strcmp(string, "log")) {
    code = 1;
  }

  return code;
}

int s21_isop(char* string) {
  int code = 0;
  if (!strcmp(string, "+") || !strcmp(string, "-") || !strcmp(string, "*") ||
      !strcmp(string, "/") || !strcmp(string, "^") || !strcmp(string, "mod")) {
    code = 1;
  }

  return code;
}

int s21_varification(char** string) {
  int code = OK;
  for (int i = 0; string[i]; i++) {
    if (!strcmp(string[i], "(")) {
      code = CALCULATION_ERROR;
      break;
    }
  }
  return code;
}

int s21_check_axis(double a, double b) {
  int code = OK;
  if (a > b) code = CALCULATION_ERROR;
  return code;
}
