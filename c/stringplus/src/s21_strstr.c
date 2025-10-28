#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = NULL;

  if (!*needle) {
    result = (char *)haystack;
  } else {
    for (const char *h = haystack; *h != '\0' && result == NULL; h++) {
      const char *h_ptr = h;
      const char *n_ptr = needle;

      while (*h_ptr != '\0' && *n_ptr != '\0' && *h_ptr == *n_ptr) {
        h_ptr++;
        n_ptr++;
      }

      if (*n_ptr == '\0') {
        result = (char *)h;
      }
    }
  }

  return result;
}