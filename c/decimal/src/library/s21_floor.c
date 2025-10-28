#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int return_value = 0;

  if (result == NULL || checking_3_bytes(value)) {
    return_value = 1;
  } else {
    zero(result);

    int sign = check_sign(value);
    int deg = degree(value);

    if (deg < 0) {
      return_value = 0;
    } else {
      s21_big_decimal support = bringing_to_big(value);
      s21_big_decimal one = {0};

      support.bits[7] = 0;
      int remains = 0;
      while (deg > 0) {
        if (last_number(support, 1)) remains = 1;
        div_by_10(&support);
        deg--;
      }

      if (remains == 1 && sign == 1) {
        one.bits[0] = 1;
        add(support, one, &support);
      }

      *result = reducing_to_less(support, deg, sign);
    }
  }

  return return_value;
}
