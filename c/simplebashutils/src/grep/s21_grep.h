#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PATTERN_SIZE 4096

typedef struct {
  int e, i, v, c, l, n, h, s, f, o;
} flags;

typedef struct {
  int argc;
  char** argv;
  flags flag;
  char* pattern;
} grep;

void s21_grep(int argc, char* argv[]);
void open_file(grep* gr);
void parcing(grep* gr);
void open_file_pattern(char** argv, char* pattern);
void validate_flags(flags* flag);
void print_flag_o(regex_t* re, char* buffer, grep* ge, int count_n, int i);
void print_flags(grep* gr);
void compile_regex(regex_t* re, grep* gr);
void pattern_definition(grep* gr);
void all_processes(grep* gr, regex_t* re);
void print_flag_v(regex_t* re, char* buffer, grep* gr, int count_n, int i,
                  int* count_cl);
void print_flag_lc(grep* gr, int count_cl, int i);
#endif