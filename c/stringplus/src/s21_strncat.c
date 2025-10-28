#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t string_length = s21_strlen(dest);
  for (s21_size_t i = string_length; i < string_length + n; i++) {
    dest[i] = src[i - string_length];
  }
  return dest;
}
