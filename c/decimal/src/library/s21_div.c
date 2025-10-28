#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;

  if (result == NULL || checking_3_bytes(value_1) ||
      checking_3_bytes(value_2) || checking_for_zero(value_2)) {
    error = 3;
  } else {
    zero(result);
    int sign = check_sign(value_1) ^ check_sign(value_2) ? 1 : 0;
    s21_big_decimal divisible = bringing_to_big(value_1);
    s21_big_decimal deductible = bringing_to_big(value_2);
    s21_big_decimal reduced = {0};
    s21_big_decimal temp_res = {0};
    if (big_degree(divisible) < big_degree(deductible))
      reduction_of_degrees(&divisible, &deductible);
    int deg = abs(big_degree(deductible) - big_degree(divisible));
    divisible.bits[7] = 0;
    deductible.bits[7] = 0;

    int bit_pos = used_bits(divisible);
    while (bit_pos >= 0) {
      if (unsigned_comparison(divisible, deductible) & 20) {
        SAR(&reduced, divisible, deductible, &bit_pos, &temp_res);
        sub(reduced, deductible, &reduced);
      } else {
        mul_by_10(&divisible);
        bit_pos = used_bits(divisible);
      }
      if (bit_pos <= 0 && used_bits(reduced) != 0 &&
          (unsigned_comparison(reduced, deductible) >> 5 & 1) &&
          used_bits(divisible) < 210) {
        mul_by_10(&divisible);
        bit_pos = used_bits(divisible);
        big_zero(&temp_res);
        big_zero(&reduced);
      }
    }
    deg += big_degree(divisible);

    rounding_up(&temp_res, &deg);

    error = s21_supprot_division(temp_res, deg, sign);

    if (error == 0) {
      *result = reducing_to_less(temp_res, deg, sign);
    }
  }

  return error;
}