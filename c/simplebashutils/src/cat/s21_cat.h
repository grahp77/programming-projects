#ifndef S21_CAT_H
#define S21_CAT_H

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>

typedef struct {
  bool b, e, n, s, t, v;
} flags;

void app_false();
void parsing(int argc, char **argv, flags *flag);
void open_file(char *v, flags *flag);

#endif