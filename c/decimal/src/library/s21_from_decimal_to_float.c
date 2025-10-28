#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = 0;

  if (dst == NULL || checking_3_bytes(src)) {
    error = 1;
  } else {
    *dst = 0.0;

    s21_big_decimal tmp = bringing_to_big(src);

    s21_decimal zero = {0};
    if (s21_is_equal(src, zero)) {
      if (check_sign(src)) {
        *dst = -0.0;
      } else {
        *dst = 0.0;
      }
    } else {
      double per = 0.0;

      for (int i = 0; i < 96; i++) {
        if ((tmp.bits[i / 32] >> i) & 1) {
          per += pow(2.0, i);
        }
      }

      if (degree(src)) {
        per /= pow(10.0, degree(src));
      }

      if (check_sign(src)) {
        per = -per;
      }

      *dst = per;
    }
  }

  return error;
}
