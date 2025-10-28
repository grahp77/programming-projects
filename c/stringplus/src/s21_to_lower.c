#include "s21_string.h"

void *s21_to_lower(const char *str) {
  if (str == s21_NULL) return s21_NULL;
  s21_size_t str_length = s21_strlen(str);
  char *ptr = s21_NULL;
  if (str_length == 0) {
    ptr = malloc(1);
    if (ptr != s21_NULL) {
      ptr[0] = '\0';
    }
  } else {
    ptr = malloc(str_length + 1);
  }
  if (ptr != s21_NULL && str_length != 0) {
    char *temp_ptr = ptr;
    while (*str != '\0') {
      if (*str >= 65 && *str <= 90) {
        *temp_ptr++ = *str++ + 32;
      } else {
        *temp_ptr++ = *str++;
      }
    }
    *temp_ptr = '\0';
  }
  return ptr;
}
