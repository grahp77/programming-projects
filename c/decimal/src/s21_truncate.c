#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int ret = 0;

  if (result == NULL || checking_3_bytes(value)) {
    ret = 1;
  } else {
    s21_big_decimal support = bringing_to_big(value);
    zero(result);
    int deg = degree(value);

    support.bits[7] = 0;

    while (deg > 0) {
      div_by_10(&support);
      deg--;
    }

    *result = reducing_to_less(support, deg, check_sign(value));
  }

  return ret;
}