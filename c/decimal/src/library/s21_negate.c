#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int ret = 0;

  if (result == NULL || checking_3_bytes(value)) {
    ret = 1;
  } else {
    value.bits[3] ^= (1 << 31);
    *result = value;
  }

  return ret;
}