#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == NULL || trim_chars == NULL) {
    return NULL;
  }

  size_t size_src = 0, size_trim_chars = 0;
  while (src[size_src] != '\0') {
    size_src++;
  }
  while (trim_chars[size_trim_chars] != '\0') {
    size_trim_chars++;
  }

  size_t start = 0, end = size_src;

  while (start < size_src) {
    int found = 0;
    for (size_t j = 0; j < size_trim_chars; j++) {
      if (src[start] == trim_chars[j]) {
        found = 1;
        break;
      }
    }
    if (!found) {
      break;
    }
    start++;
  }

  while (end > start) {
    int found = 0;
    for (size_t j = 0; j < size_trim_chars; j++) {
      if (src[end - 1] == trim_chars[j]) {
        found = 1;
        break;
      }
    }
    if (!found) {
      break;
    }
    end--;
  }

  size_t result_size = end - start;
  char *result = (char *)malloc(result_size + 1);
  if (result == NULL) {
    return NULL;
  }

  for (size_t i = 0; i < result_size; i++) {
    result[i] = src[start + i];
  }
  result[result_size] = '\0';

  return result;
}