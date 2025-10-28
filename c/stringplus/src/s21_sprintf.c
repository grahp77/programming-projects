#include "s21_string.h"

typedef struct {
  int percent;
  int c;
  int d;
  int f;
  int s;
  int u;
  int plus;
  int minus;
  int space;
  int dot;
  int width;
  int accuracy;
  int length_h;
  int length_l;
} flags;

int s21_sprintf(char *str, const char *format, ...);
void parcing(char const *format, s21_size_t *i, flags *flag);
int transformation(char *buffer, va_list args, flags flag);
long int pow_int(int x, int y);
long int short_long_int(long int number, flags flag);
unsigned long int unsigned_short_long_int(unsigned long int number, flags flag);
void specifier_d(char *buffer, long int number, flags flag);
void specifier_u(char *buffer, unsigned long int number, flags flag);
void specifier_f(char *buffer, double number, flags flag);
void implementation_flag_width(char *buffer, char *str, flags flag);

void specifier_f(char *buffer, double number, flags flag) {
  flag.accuracy = (!flag.dot) ? 6 : flag.accuracy;
  int negative_number = 0;
  if (number < 0) {
    number = -number;
    negative_number = 1;
  }
  long int integer_number = (long int)number;
  long int integer_fractional_part =
      (number - integer_number) * pow_int(10, flag.accuracy + 1);
  integer_fractional_part =
      (integer_fractional_part % 10 >= 5 && flag.accuracy != 0)
          ? integer_fractional_part / 10 + 1
          : integer_fractional_part / 10;
  integer_number = ((long int)(number * 10) % 10 >= 6 && flag.accuracy == 0)
                       ? integer_number + 1
                       : integer_number;
  char str[10000] = "";
  int i = 0;
  while (i < flag.accuracy) {
    str[i++] = integer_fractional_part % 10 + '0';
    integer_fractional_part /= 10;
  }
  if (flag.accuracy > 0) {
    str[i++] = '.';
  }
  do {
    str[i++] = integer_number % 10 + '0';
    integer_number /= 10;
  } while (integer_number * 10 / 10 != 0);

  if (flag.plus && !flag.space && !negative_number) {
    str[i++] = '+';
  } else if (flag.space && !flag.plus && !negative_number) {
    str[i++] = ' ';
  } else if (negative_number) {
    str[i++] = '-';
  }
  str[i--] = '\0';

  char t;
  for (int j = 0; j < i;) {
    t = str[j];
    str[j++] = str[i];
    str[i--] = t;
  }
  implementation_flag_width(buffer, str, flag);
}

void specifier_d(char *buffer, long int number, flags flag) {
  number = short_long_int(number, flag);
  int negative_number = 0;
  if (number < 0) {
    number = -number;
    negative_number = 1;
  }

  char str[10000] = "";
  int i = 0;
  if (number == 0 && !flag.dot) {
    str[i++] = number + '0';
  }

  while (number * 10 / 10 != 0 || i < flag.accuracy) {
    str[i++] = number % 10 + '0';
    number /= 10;
  }

  if (flag.plus && !flag.space && !negative_number) {
    str[i++] = '+';
  } else if (flag.space && !flag.plus && !negative_number) {
    str[i++] = ' ';
  } else if (negative_number) {
    str[i++] = '-';
  }
  str[i--] = '\0';

  char t;
  for (int j = 0; j <= i;) {
    t = str[j];
    str[j++] = str[i];
    str[i--] = t;
  }
  implementation_flag_width(buffer, str, flag);
}

void implementation_flag_width(char *buffer, char *str, flags flag) {
  flag.width =
      (flag.width < (int)s21_strlen(str)) ? (int)s21_strlen(str) : flag.width;
  for (int i = 0; i < flag.width; i++) {
    buffer[i] = ' ';
  }

  if (flag.minus) {
    for (int i = 0; i < (int)s21_strlen(str); i++) {
      buffer[i] = str[i];
    }
  } else {
    for (int i = 0, j = flag.width - (int)s21_strlen(str); j < flag.width;
         i++, j++) {
      buffer[j] = str[i];
    }
  }
}

void specifier_u(char *buffer, unsigned long int number, flags flag) {
  number = unsigned_short_long_int(number, flag);
  char str[10000] = "";
  int i = 0;
  if (number == 0 && !flag.dot) {
    str[i++] = number + '0';
  }

  while (number * 10 / 10 != 0 || i < flag.accuracy) {
    str[i++] = number % 10 + '0';
    number /= 10;
  }

  if (flag.plus && !flag.space) {
    str[i++] = '+';
  } else if (flag.space && !flag.plus) {
    str[i++] = ' ';
  }
  str[i--] = '\0';

  char t;
  for (int j = 0; j <= i;) {
    t = str[j];
    str[j++] = str[i];
    str[i--] = t;
  }
  implementation_flag_width(buffer, str, flag);
}

long int short_long_int(long int number, flags flag) {
  int negative_number = 0;
  if (number < 0) {
    number = -number;
    negative_number = 1;
  }
  int number_of_bits = 0;
  if (flag.length_l) {
    number_of_bits = 64;
  } else if (flag.length_h) {
    number_of_bits = 16;
  } else
    number_of_bits = 32;
  char str[256] = "";
  for (int i = 0; i <= number_of_bits; i++) {
    str[i] = number % 2 + '0';
    number /= 2;
  }
  str[number_of_bits] = '\0';
  int reverse = 0;
  number = 0;
  if (str[number_of_bits - 1] % 48) {
    for (int i = 0; i < number_of_bits - 1; i++) {
      reverse = ((str[i] % 48 == 1) && i < 31) ? 0 : 1;
      number = reverse * pow_int(2, i) + number;
    }
  } else {
    for (int i = 0; i < number_of_bits - 1; i++) {
      number = (str[i] % 48) * pow_int(2, i) + number;
    }
  }
  number = (str[number_of_bits - 1] % 48) ? -(number + 1) : number;
  number = (negative_number) ? -number : number;
  return number;
}

unsigned long int unsigned_short_long_int(unsigned long int number,
                                          flags flag) {
  int minus = 0;
  int number_of_bits = 0;
  if (flag.length_l) {
    number_of_bits = 64;
  } else if (flag.length_h) {
    number_of_bits = 16;
  } else
    number_of_bits = 32;
  char str[256] = "";
  for (int i = 0; i <= number_of_bits; i++) {
    str[i] = number % 2 + '0';
    number /= 2;
  }
  str[number_of_bits] = '\0';
  int reverse = 0;
  number = 0;
  if (minus) {
    for (int i = 0; i < number_of_bits; i++) {
      reverse = ((str[i] % 48 == 1)) ? 0 : 1;
      number = reverse * pow_int(2, i) + number;
    }
  } else if (!minus) {
    for (int i = 0; i <= number_of_bits; i++) {
      number = (str[i] % 48) * pow_int(2, i) + number;
    }
  }
  return number;
}

long int pow_int(int x, int y) {
  long int result = 1;
  while (y > 0) {
    result *= x;
    y--;
  }
  return result;
}

int s21_sprintf(char *str, const char *format, ...) {
  s21_memset(str, 0, s21_strlen(str));
  char buffer[10000] = "";
  va_list args;
  va_start(args, format);
  int j = 0;
  int f = 1;
  for (s21_size_t i = 0; i < s21_strlen(format); i++) {
    if (format[i] == '%') {
      flags flag = {0};
      parcing(format, &i, &flag);
      f = transformation(buffer, args, flag);
      s21_strncat(str, buffer, s21_strlen(buffer));
      j = j + s21_strlen(buffer);
    } else if (f) {
      str[j] = format[i];
      j++;
    }
  }
  str[j] = '\0';
  va_end(args);
  return j;
}

int transformation(char *buffer, va_list args, flags flag) {
  int f = 0;
  s21_memset(buffer, 0, s21_strlen(buffer));
  if (flag.c) {
    char symbol[2];
    symbol[0] = (char)va_arg(args, int);
    symbol[1] = '\0';
    implementation_flag_width(buffer, symbol, flag);
    f = 1;
  }
  if (flag.d) {
    long number = va_arg(args, long);
    specifier_d(buffer, number, flag);
    f = 1;
  }
  if (flag.u) {
    unsigned long number = va_arg(args, unsigned long);
    specifier_u(buffer, number, flag);
    f = 1;
  }
  if (flag.s) {
    char *str = va_arg(args, char *);
    implementation_flag_width(buffer, str, flag);
    f = 1;
  }
  if (flag.f) {
    double number = va_arg(args, double);
    specifier_f(buffer, number, flag);
    f = 1;
  }
  return f;
}

void parcing(char const *format, s21_size_t *i, flags *flag) {
  do {
    if (flag->dot && format[*i] >= 48 && format[*i] <= 57) {
      flag->accuracy = flag->accuracy * 10 + (format[*i] % 48);
    } else if (format[*i] >= 48 && format[*i] <= 57) {
      flag->width = flag->width * 10 + (format[*i] % 48);
    }
    *i = *i + 1;
    switch (format[*i]) {
      case '%':
        flag->percent = 1;
        break;
      case 'c':
        flag->c = 1;
        break;
      case 'd':
        flag->d = 1;
        break;
      case 'f':
        flag->f = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 'u':
        flag->u = 1;
        break;
      case '+':
        flag->plus = 1;
        break;
      case ' ':
        flag->space = 1;
        break;
      case '-':
        flag->minus = 1;
        break;
      case '.':
        flag->dot = 1;
        break;
      case 'h':
        flag->length_h = 1;
        break;
      case 'l':
        flag->length_l = 1;
        break;
    }
  } while (format[*i] != 'c' && format[*i] != 'd' && format[*i] != 'f' &&
           format[*i] != 's' && format[*i] != 'u');
}
