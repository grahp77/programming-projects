#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;

  if (result == NULL || checking_3_bytes(value_1) ||
      checking_3_bytes(value_2)) {
    error = 1;
  } else {
    s21_big_decimal temp1 = bringing_to_big(value_1);
    s21_big_decimal temp2 = bringing_to_big(value_2);
    s21_big_decimal temp_res = {0};

    reduction_of_degrees(&temp1, &temp2);
    int deg = big_degree(temp1);
    int sign = 0, flag = 0;

    flag = logic(temp1, temp2, *result);
    if (((flag >> 0 & 1) ^ (flag >> 1 & 1) ^ (flag >> 2 & 1)) == 0) {
      zero(result);
      add(temp1, temp2, &temp_res);
      if (flag & 4) sign = 1;

      rounding_up(&temp_res, &deg);

      s21_big_decimal temp_res_big = {{0, 0, 0, 1, 0, 0, 0, 0}};

      if ((deg < 0 && sign) ||
          (unsigned_comparison(temp_res_big, temp_res) == 26 && deg == 0 &&
           sign) ||
          deg > 28) {
        error = 2;
      } else if (deg < 0 ||
                 (unsigned_comparison(temp_res_big, temp_res) == 26 &&
                  deg == 0 && !sign)) {
        error = 1;
      } else {
        *result = reducing_to_less(temp_res, deg, sign);
      }
    } else {
      result->bits[3] ^= (1 << 31);
      error = s21_sub(value_1, value_2, result);
    }
  }

  return error;
}
