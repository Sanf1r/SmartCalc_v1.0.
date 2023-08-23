#include "s21_calc.h"

int s21_score(char* string) {
  int result = 0;
  if (!strcmp(string, "-") || !strcmp(string, "+")) result = 1;
  if (!strcmp(string, "/") || !strcmp(string, "*") || !strcmp(string, "mod"))
    result = 2;
  if (!strcmp(string, "^")) result = 3;
  if (!strcmp(string, "sin") || !strcmp(string, "cos") ||
      !strcmp(string, "tan") || !strcmp(string, "asin") ||
      !strcmp(string, "acos") || !strcmp(string, "atan") ||
      !strcmp(string, "sqrt") || !strcmp(string, "ln") ||
      !strcmp(string, "log")) {
    result = 5;
  }
  return result;
}

void s21_lexems(char* str, char** lexems) {
  int lexcount = 0;
  char* del = strtok(str, "|");
  while (del != NULL) {
    lexems[lexcount++] = del;
    del = strtok(NULL, "|");
  }
}

int s21_strings_for_eval(char** lexems, char** temp_out, char** RPN) {
  int code = OK;
  stack_char* stack = NULL;
  for (int i = 0, j = 0; lexems[i]; i++) {
    char* token = lexems[i];
    if (s21_isnum(token)) {
      temp_out[j++] = lexems[i];
    } else if (s21_isfunc(token) || !strcmp(token, "(")) {
      s21_push_char(&stack, token);
    } else if (stack && !strcmp(token, ")")) {
      while (stack && strcmp(stack->op, "(")) {
        temp_out[j++] = s21_pop_char(&stack);
      }
      if (stack) s21_pop_char(&stack);
    } else if (s21_isop(token)) {
      int score = s21_score(token);
      if (stack) {
        while (stack &&
               !(!strcmp(token, "^") && !strcmp(s21_peek_char(&stack), "^")) &&
               s21_score(s21_peek_char(&stack)) >= score) {
          temp_out[j++] = s21_pop_char(&stack);
        }
      }
      s21_push_char(&stack, token);
    } else {
      code = CALCULATION_ERROR;
      break;
    }
  }
  if (code == OK) {
    for (int i = 0; temp_out[i] || stack; i++) {
      if (temp_out[i]) {
        RPN[i] = temp_out[i];
      } else if (stack)
        RPN[i] = s21_pop_char(&stack);
    }
  }

  return code;
}

// int main() {
//   char str[] = "1|+|2|+|3|+|4|*|7|*|8|^|3|^|2|";
//   char* lexems[255] = {0};
//   char* temp_out[255] = {0};
//   char* RPN[255] = {0};

//   // char str[] =
//   // "-1|*|(|888.22|*|sin|(|(|888|-|+6|)|^|3|^|2|)|/|(|85|-|6|)|)|";
//   s21_lexems(str, lexems);
//   s21_strings_for_eval(lexems, temp_out, RPN);

//   for (int i = 0; RPN[i]; i++) {
//     printf("%s ", RPN[i]);
//   }

//   return 0;
// }
