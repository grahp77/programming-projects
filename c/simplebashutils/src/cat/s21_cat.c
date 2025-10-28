#include "s21_cat.h"

int main(int argc, char *argv[]) {
  flags flag = {0};
  parsing(argc, argv, &flag);
  for (int i = optind; i < argc; i++) {
    open_file(argv[i], &flag);
  }
  return 0;
}

void open_file(char *v, flags *flag) {
  FILE *fp = fopen(v, "r");
  if (fp == NULL) {
    printf("cat: %s: No such file or directory\n", v);
    return;
  }
  int c;
  int x = 1;
  int count_squeeze = 1;
  int start_line = 1;
  int previous_ch = '\n';
  while ((c = fgetc(fp)) != EOF) {
    count_squeeze = ((flag->s) && (c == '\n')) ? count_squeeze + 1 : 0;
    if (flag->n && start_line && flag->b == 0) {
      printf("%6d\t", x);
      x++;
      start_line = 0;
    }
    if (flag->b && previous_ch == '\n' && c != '\n') {
      printf("%6d\t", x);
      previous_ch = 'N';
      x++;
    }
    if (c == '\n') {
      previous_ch = c;
      start_line = 1;
    }
    if (flag->e && c == '\n') {
      printf("$");
    }
    if (flag->t && c == '\t') {
      printf("^I");
      continue;
    }
    if (flag->v) {
      if (c >= 0 && c <= 32 && c != '\n' && c != '\t' && c != ' ') {
        c += 64;
        printf("^");
      }
      if (c >= 127) {
        c -= 64;
        printf("^");
      }
    }
    if (count_squeeze < 3) {
      printf("%c", c);
    }
  }
  fclose(fp);
}

void parsing(int argc, char **argv, flags *flag) {
  struct option long_flags[] = {{"number-nonblank", 0, NULL, 'b'},
                                {"number", 0, NULL, 'n'},
                                {"squeeze-blank", 0, NULL, 's'},
                                {0, 0, 0, 0}};
  int flag_options;
  while ((flag_options =
              getopt_long(argc, argv, "beEnstT", long_flags, NULL)) != -1) {
    switch (flag_options) {
      case 'b':
        flag->b = 1;
        break;
      case 'e':
        flag->e = 1;
        flag->v = 1;
        break;
      case 'E':
        flag->e = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 't':
        flag->t = 1;
        flag->v = 1;
        break;
      case 'T':
        flag->t = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      default:
        printf("cat: illegal option usage: cat [-beEnstT] [file ...]");
    }
  }
}