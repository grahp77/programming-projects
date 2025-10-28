#include "s21_grep.h"

int main(int argc, char* argv[]) {
  s21_grep(argc, argv);
  return 0;
}

void s21_grep(int argc, char* argv[]) {
  char pattern[MAX_PATTERN_SIZE] = {0};
  grep gr = {.argc = argc, .argv = argv, .flag = {0}, .pattern = pattern};
  parcing(&gr);
  open_file(&gr);
}

void parcing(grep* gr) {
  int flag_options;
  while ((flag_options = getopt(gr->argc, gr->argv, "e:ivclnhsfo")) != -1) {
    switch (flag_options) {
      case 'e':
        gr->flag.e += 1;
        if (gr->flag.e > 1) {
          strcat(gr->pattern, "|");
        }
        strcat(gr->pattern, gr->argv[optind - 1]);
        break;
      case 'i':
        gr->flag.i = 1;
        break;
      case 'v':
        gr->flag.v = 1;
        break;
      case 'c':
        gr->flag.c = 1;
        break;
      case 'l':
        gr->flag.l = 1;
        break;
      case 'n':
        gr->flag.n = 1;
        break;
      case 'h':
        gr->flag.h = 1;
        break;
      case 's':
        gr->flag.s = 1;
        break;
      case 'f':
        gr->flag.f = 1;
        strcat(gr->pattern, "|");
        open_file_pattern(gr->argv, gr->pattern);
        break;
      case 'o':
        gr->flag.o = 1;
        break;
      default:
        printf("cat: illegal option usage: cat [-beEnstT] [file ...]");
    }
  }
  validate_flags(&gr->flag);
}

void validate_flags(flags* flag) {
  if (flag->l) {
    flag->n = 0;
    flag->o = 0;
    flag->c = 0;
  }

  if (flag->c) {
    flag->n = 0;
    flag->o = 0;
  }

  if (flag->o && flag->v) {
    flag->o = 0;
  }
}

void open_file_pattern(char** argv, char* pattern) {
  char temp[1024] = "";
  FILE* fp = fopen(argv[optind], "r");
  if (fp == NULL) {
    printf("grep: %s: Error opening file\n", argv[optind]);
  }
  while (fgets(temp, sizeof(temp), fp) != NULL) {
    size_t temp_len = strlen(temp);
    size_t pattern_len = strlen(pattern);
    if (temp_len > 0 && temp[temp_len - 1] == '\n') {
      temp[temp_len - 1] = '|';
    }
    if (temp_len + pattern_len > MAX_PATTERN_SIZE) {
      printf("grep: %s: pattern buffer full\n", argv[optind]);
      break;
    }
    strcat(pattern, temp);
  }

  fclose(fp);
}

void open_file(grep* gr) {
  pattern_definition(gr);
  regex_t re;

  compile_regex(&re, gr);
  all_processes(gr, &re);

  regfree(&re);
}

void pattern_definition(grep* gr) {
  if (!gr->flag.e && !gr->flag.f) {
    gr->pattern = gr->argv[optind];
    optind++;
  }
  if (gr->flag.f) {
    optind++;
  }
}

void compile_regex(regex_t* re, grep* gr) {
  char b = (gr->flag.i) ? REG_ICASE : 0;
  regcomp(re, gr->pattern, REG_EXTENDED | b);
}

void all_processes(grep* gr, regex_t* re) {
  for (int i = optind; i < gr->argc; i++) {
    FILE* fp = fopen(gr->argv[i], "r");
    if (fp == NULL) {
      if (!gr->flag.s) {
        printf("grep: %s: No such file or directory\n", gr->argv[i]);
      }
      continue;
    }
    char buffer[MAX_PATTERN_SIZE];
    int count_n = 1;
    int count_cl = 0;

    while (fgets(buffer, MAX_PATTERN_SIZE, fp) != NULL) {
      print_flag_o(re, buffer, gr, count_n, i);
      print_flag_v(re, buffer, gr, count_n, i, &count_cl);
      count_n++;
    }
    print_flag_lc(gr, count_cl, i);

    fclose(fp);
  }
}

void print_flag_o(regex_t* re, char* buffer, grep* gr, int count_n, int i) {
  regmatch_t match;
  while (regexec(re, buffer, 1, &match, 0) == 0 && gr->flag.o) {
    if ((gr->argc - optind) > 1) {
      printf("%s:", gr->argv[i]);
    }
    if (gr->flag.n && !gr->flag.l && !gr->flag.c) {
      printf("%d:", count_n);
    }
    printf("%s\n", gr->pattern);
    buffer += match.rm_eo;
  }
}

void print_flag_v(regex_t* re, char* buffer, grep* gr, int count_n, int i,
                  int* count_cl) {
  int search = regexec(re, buffer, 0, NULL, 0);
  search = (gr->flag.v) ? !search : search;
  if (search == 0) {
    (*count_cl)++;
    if ((gr->argc - optind) > 1 && !gr->flag.l && !gr->flag.c && !gr->flag.h &&
        !gr->flag.o) {
      printf("%s:", gr->argv[i]);
    }
    if (gr->flag.n && !gr->flag.l && !gr->flag.c && !gr->flag.o) {
      printf("%d:", count_n);
    }
    if (((!gr->flag.c && !gr->flag.l) || gr->flag.e) && !gr->flag.o) {
      (buffer[strlen(buffer) - 1] == '\n') ? fputs(buffer, stdout)
                                           : printf("%s\n", buffer);
    }
  }
}

void print_flag_lc(grep* gr, int count_cl, int i) {
  if (gr->flag.l && count_cl > 0) {
    printf("%s\n", gr->argv[i]);
  } else if (gr->flag.c) {
    if ((gr->argc - optind) > 1) {
      printf("%s:", gr->argv[i]);
    }
    printf("%d\n", count_cl);
  }
}