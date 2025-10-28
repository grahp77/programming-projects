#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  int found_symbol = 0;
  unsigned char *pointer_str = (unsigned char *)str;
  void *result = NULL;

  for (s21_size_t i = 0; i < n && found_symbol == 0; i++) {
    if (c == pointer_str[i] && found_symbol == 0) {
      found_symbol = 1;
      result = (void *)&pointer_str[i];
    }
  }
  return result;
}