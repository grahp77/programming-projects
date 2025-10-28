#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int ret = 0;

  if (result == NULL || checking_3_bytes(value)) {
    ret = 1;
  } else {
    zero(result);
    int deg = degree(value);

    int z = 0;

    s21_big_decimal one = {0};

    s21_big_decimal support = bringing_to_big(value);

    support.bits[7] = 0;

    while (deg > 0) {
      if (deg == 1) {
        z = last_number(support, 1);
      }
      div_by_10(&support);
      deg--;
    }

    one.bits[0] = 1;

    if (z > 4) {
      add(support, one, &support);
    }

    *result = reducing_to_less(support, deg, check_sign(value));
  }

  return ret;
}