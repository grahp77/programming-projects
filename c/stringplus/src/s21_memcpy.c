#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  s21_size_t i;

  for (i = 0; i < n && ((char *)src)[i] != '\0'; i++) {
    ((char *)dest)[i] = ((char *)src)[i];
  }
  for (; i < n; i++) {
    ((char *)dest)[i] = '\0';
  }

  return dest;
}
