#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;

  if (dst == NULL || checking_3_bytes(src)) {
    error = 1;
  } else {
    s21_truncate(src, &src);

    s21_decimal big = {{0xFFFFFFFF, 0, 0, 0}};
    s21_decimal small = {{0xFFFFFFFF, 0, 0, 0x80000000}};

    if (s21_is_greater(src, big) || s21_is_less(src, small)) {
      error = 1;
    } else {
      *dst = src.bits[0];

      if (check_sign(src)) {
        *dst = -*dst;
      }
    }
  }

  return error;
}
