#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error = 0;

  if (dst == NULL || isnan(src)) {
    error = 1;
  } else {
    zero(dst);

    if (src == 0) {
      if (signbit(src)) {
        dst->bits[3] |= 1 << 31;
      }
    } else if (fabs(src) > 79228162514264337593543950335. ||
               fabs(src) < 1e-28 || checking_3_bytes(*dst)) {
      error = 1;
    } else {
      char ch_num[30] = {0};
      char ch_degree[10] = {0};
      sprintf(ch_num, "%+e\n\n", src);
      strncat(ch_degree, ch_num + 10, 3);

      for (int i = 2; i < 8; i++) {
        ch_num[i] = ch_num[i + 1];
      }
      ch_num[8] = '\0';
      int num = atoi(ch_num);
      int deg = atoi(ch_degree) - 6;
      int sign = 0;
      if (num < 0) {
        sign = 1;
        num = -num;
      }
      while (num % 10 == 0 && deg < 0) {
        num /= 10;
        deg += 1;
      }
      s21_big_decimal result = bringing_to_big(*dst);
      result.bits[0] = num;
      while (deg > 0) {
        mul_by_10(&result);
        deg--;
      }
      deg = -deg;
      rounding_up(&result, &deg);
      *dst = reducing_to_less(result, abs(deg), sign);
    }
  }

  return error;
}
