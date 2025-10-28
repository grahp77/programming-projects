#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  s21_size_t i;
  int flag = 0;

  for (i = 0; !flag && i < n; i++) {
    if (str1[i] != str2[i]) {
      result = str1[i] - str2[i];
      flag = 1;
    }
  }
  return result;
}
