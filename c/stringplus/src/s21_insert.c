#include "s21_string.h"

void *s21_insert(const char *src, const char *str, size_t start_index) {
  if (src == s21_NULL || str == s21_NULL) return s21_NULL;
  s21_size_t cntr = 0, srcind = 0, strind = 0, src_length = s21_strlen(src),
             str_length = s21_strlen(str);
  char *ptr = s21_NULL;
  if (src_length >= start_index) {
    if (src_length + str_length == 0) {
      ptr = malloc(1);
      if (ptr != s21_NULL) {
        ptr[0] = '\0';
      }
    } else {
      ptr = malloc(src_length + str_length + 1);
    }
    if (ptr != s21_NULL && src_length + str_length != 0) {
      char *temp_ptr = ptr;
      while (cntr < start_index) {
        temp_ptr[cntr] = src[srcind];
        cntr++;
        srcind++;
      }
      while (str[strind] != '\0') {
        temp_ptr[cntr] = str[strind];
        strind++;
        cntr++;
      }
      while (src[srcind] != '\0') {
        temp_ptr[cntr] = src[srcind];
        srcind++;
        cntr++;
      }
      temp_ptr[cntr] = '\0';
    }
  }

  return ptr;
}
