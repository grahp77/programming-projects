#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *last = NULL;
  char *result = NULL;

  if (str != NULL) {
    last = str;
  }
  if (last != NULL) {
    char *start = last;
    while (*start && s21_strchr(delim, *start)) {
      start++;
    }

    if (*start) {
      char *end = start;
      while (*end && !s21_strchr(delim, *end)) {
        end++;
      }

      if (*end) {
        *end = '\0';
        last = end + 1;
      } else {
        last = NULL;
      }

      result = start;
    } else {
      last = NULL;
    }
  }

  return result;
}
