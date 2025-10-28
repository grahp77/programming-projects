#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  if (str == NULL) {
    return s21_NULL;
  }

  s21_size_t i;

  for (i = 0; i < n; i++) {
    ((char *)str)[i] = (char)c;
  }

  return str;
}
