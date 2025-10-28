#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *result = s21_NULL;

  const char *last_ch = s21_NULL;
  char ch = (char)c;

  while (*str != '\0') {
    if (*str == ch) {
      last_ch = (char *)str;
    }
    str++;
  }
  if (ch == '\0') {
    result = (char *)str;
  } else {
    result = (char *)last_ch;
  }

  return result;
}