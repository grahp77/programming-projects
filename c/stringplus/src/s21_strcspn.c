#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t index = s21_strlen(str1);
  s21_size_t res;
  int find;
  for (size_t i = 0; i < s21_strlen(str2) && index != 0; i++) {
    find = 0;
    for (res = 0; res < s21_strlen(str1) && find != 1; res++) {
      if (str1[res] == str2[i]) {
        find = 1;
        res--;
      }
    }
    index = (res < index) ? res : index;
  }
  return index;
}