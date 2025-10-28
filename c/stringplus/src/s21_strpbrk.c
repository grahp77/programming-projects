#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = NULL;
  int found = 0;
  for (s21_size_t end_str1 = 0; str1[end_str1] != '\0' && !found; end_str1++) {
    for (s21_size_t i = 0; str2[i] != '\0' && !found; i++) {
      if (str1[end_str1] == str2[i]) {
        result = (char *)&str1[end_str1];
        found = 1;
      }
    }
  }

  return result;
}