#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int result = 0;

  if (dst == NULL) {
    result = 1;
  } else {
    zero(dst);

    if (checking_3_bytes(*dst)) {
      result = 1;
    } else {
      set_sign(&src);
      dst->bits[0] = src;
    }
  }

  return result;
}
