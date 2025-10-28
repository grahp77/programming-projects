#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"
#define SIZE 100

START_TEST(test_memchr_1) {
  char s1[10] = "qqqrrrt";
  char *dest1 = memchr(s1, 'q', 3);
  char *dest2 = s21_memchr(s1, 'q', 3);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_memchr_null_terminator) {
  char s1[10] = "qqq\0rrrr";
  char *dest1 = memchr(s1, 'r', 5);
  char *dest2 = s21_memchr(s1, 'r', 5);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_memchr_not_found_in_n) {
  char s1[10] = "mmmbbbr";
  char *dest1 = memchr(s1, 'z', 5);
  char *dest2 = s21_memchr(s1, 'z', 5);
  ck_assert_ptr_eq(dest1, dest2);
}
END_TEST

START_TEST(test_memchr_n_less_str) {
  char s1[10] = "qqq";
  char *dest1 = memchr(s1, 'q', 5);
  char *dest2 = s21_memchr(s1, 'q', 5);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_memchr_empty_str) {
  char s1[10] = "";
  char *dest1 = memchr(s1, 'q', 5);
  char *dest2 = s21_memchr(s1, 'q', 5);
  ck_assert_ptr_eq(dest1, dest2);
}
END_TEST

START_TEST(test_memcmp_n_less_str) {
  char s1[10] = "qqq";
  char s2[10] = "qqq";
  int result1 = memcmp(s1, s2, 5);
  int result2 = s21_memcmp(s1, s2, 5);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_memcmp) {
  char s1[10] = "qwea";
  char s2[10] = "qwer";
  int result1 = memcmp(s1, s2, 2);
  int result2 = s21_memcmp(s1, s2, 2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_memcmp_first_less_second) {
  char s1[10] = "qweaaaa";
  char s2[10] = "qwezzzz";
  int result1 = memcmp(s1, s2, 3);
  int result2 = s21_memcmp(s1, s2, 3);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_memcmp_first_more_second) {
  char s1[10] = "zzzzyyyy";
  char s2[10] = "zzzaaaaa";
  int result1 = memcmp(s1, s2, 7);
  int result2 = s21_memcmp(s1, s2, 7);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_memcmp_eq_n) {
  char s1[10] = "abcd";
  char s2[10] = "abcd";
  int result1 = memcmp(s1, s2, 4);
  int result2 = s21_memcmp(s1, s2, 4);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_memcmp_n_large) {
  char s1[10] = "abcd";
  char s2[10] = "abcd";
  int result1 = memcmp(s1, s2, 5);
  int result2 = s21_memcmp(s1, s2, 5);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_memcpy_second_less) {
  char s1[] = "Salut, Earth?";
  char s2[] = "Salut, Earth?";
  char s3[] = "\0";
  char *dest1 = memcpy(s1, s3, 1);
  char *dest2 = s21_memcpy(s2, s3, 1);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_memcpy_second_more) {
  char s1[] = "abcDEF";
  char s2[] = "abcDEF";
  char s3[] = "ZZZZZZZZ";
  char *dest1 = memcpy(s1, s3, 3);
  char *dest2 = s21_memcpy(s2, s3, 3);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_memcpy_eq_str) {
  char s1[100] = "Planet!";
  char s2[100] = "Planet!";
  char str[10] = "zzzzz";
  int n = 3;
  ck_assert_str_eq(memcpy(s1, str, n), s21_memcpy(s2, str, n));
}
END_TEST

START_TEST(test_memcpy_big_n) {
  char s1[100] = "Salut, Earth?";
  char s2[100] = "Salut, Earth?";
  char str[10] = "zxcvbn";
  int n = 7;
  ck_assert_str_eq(memcpy(s1, str, n), s21_memcpy(s2, str, n));
}
END_TEST

START_TEST(test_memcpy_second_str_null_term) {
  char s1[100] = "qwe";
  char s2[100] = "qwe";
  char str[10] = "\0";
  int n = 1;
  ck_assert_str_eq(memcpy(s1, str, n), s21_memcpy(s2, str, n));
}
END_TEST

START_TEST(test_memcpy_second_str_zero_n) {
  char s1[100] = "abcd";
  char s2[100] = "abcd";
  char str[10] = "z";
  int n = 0;
  ck_assert_str_eq(memcpy(s1, str, n), s21_memcpy(s2, str, n));
}
END_TEST

START_TEST(test_memcpy_second_str_term_null) {
  char s1[100] = "abcd\02ef";
  char s2[100] = "abcd\02ef";
  char str[10] = "some";
  int n = 3;
  ck_assert_str_eq(memcpy(s1, str, n), s21_memcpy(s2, str, n));
}
END_TEST

START_TEST(test_memcpy_second_str_term_null_num) {
  char s1[100] = "1111\032222";
  char s2[100] = "1111\032222";
  char str[10] = "zzz\0123";
  int n = 7;
  ck_assert_str_eq(memcpy(s1, str, n), s21_memcpy(s2, str, n));
}
END_TEST

START_TEST(test_memset_null_terminator) {
  char s1[10] = {'\0'};
  char s2[10] = {'\0'};
  char *dest1 = memset(s1, 64, 3);
  char *dest2 = s21_memset(s2, 64, 3);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_memset_str_eq) {
  char s1[10] = "999999999\0";
  char s2[10] = "999999999\0";
  char *dest1 = memset(s1, 12, 3);
  char *dest2 = s21_memset(s2, 12, 3);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncat) {
  char s1[20] = "abcabc";
  char s2[10] = "xxxzzz";
  char *result1 = strncat(s1, s2, 3);
  char *result2 = s21_strncat(s1, s2, 3);
  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strncat_first_empty_str) {
  char s1[20] = "";
  char s2[10] = "xyz";
  char *result1 = strncat(s1, s2, 4);
  char *result2 = s21_strncat(s1, s2, 4);
  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strncat_two_empty_str) {
  char s1[20] = "";
  char s2[10] = "";
  char *result1 = strncat(s1, s2, 4);
  char *result2 = s21_strncat(s1, s2, 4);
  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strchr) {
  char s1[10] = "zzzxxxr";
  char *dest1 = strchr(s1, 'z');
  char *dest2 = s21_strchr(s1, 'z');
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strchr_null_terminator) {
  char s1[10] = "aaa\0bbb";
  char *dest1 = strchr(s1, 'b');
  char *dest2 = s21_strchr(s1, 'b');
  ck_assert_ptr_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strchr_find_null_terminator) {
  char s1[10] = "mmmbbbr";
  char *dest1 = strchr(s1, '\0');
  char *dest2 = s21_strchr(s1, '\0');
  ck_assert_ptr_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strchr_not_found) {
  char s1[10] = "mmmbbbr";
  char *dest1 = strchr(s1, 'z');
  char *dest2 = s21_strchr(s1, 'z');
  ck_assert_ptr_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strchr_found_end) {
  char s1[10] = "xyzq";
  char *dest1 = strchr(s1, 'q');
  char *dest2 = s21_strchr(s1, 'q');
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strchr_empty_str) {
  char s1[20] = "";
  char *result1 = strchr(s1, 'z');
  char *result2 = s21_strchr(s1, 'z');
  ck_assert_ptr_eq(result1, result2);
}
END_TEST

START_TEST(test_strncmp_null_terminator) {
  char s1[20] = "abcq\0x";
  char s2[20] = "abcq\0x";
  int result1 = strncmp(s1, s2, 6);
  int result2 = s21_strncmp(s1, s2, 6);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_strncmp_str_eq) {
  char s1[20] = "qqqqaaa";
  char s2[20] = "qqqqaaa";
  int result1 = strncmp(s1, s2, 6);
  int result2 = s21_strncmp(s1, s2, 6);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_strncmp_first_str_big) {
  char s1[20] = "zzzzzzzz";
  char s2[20] = "zaaa";
  int result1 = strncmp(s1, s2, 6);
  int result2 = s21_strncmp(s1, s2, 6);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_strncmp_second_str_big) {
  char s2[20] = "zzzzzzzz";
  char s1[20] = "zaaa";
  int result1 = strncmp(s1, s2, 6);
  int result2 = s21_strncmp(s1, s2, 6);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_strncpy_src_less_n) {
  char s1[20] = "zzzzzzzz";
  char s2[20] = "zzzzzzzz";
  char s3[5] = "xyq";
  char *result1 = strncpy(s1, s3, 6);
  char *result2 = s21_strncpy(s2, s3, 6);
  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strncpy_overwrite_null_terminator) {
  char s1[20] = "zxc\0bbbb";
  char s2[20] = "zxc\0bbbb";
  char s3[20] = "abc";
  char *result1 = strncpy(s1, s3, 6);
  char *result2 = s21_strncpy(s2, s3, 6);
  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strncpy) {
  char s1[20] = "zzzzzzzz";
  char s2[20] = "zzzzzzzz";
  char s3[5] = "abc";
  char *result1 = strncpy(s1, s3, 3);
  char *result2 = s21_strncpy(s2, s3, 3);
  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strcspn_zero) {
  char *s1 = "aaaafd";
  char *s2 = "aab";
  int result1 = strcspn(s1, s2);
  int result2 = s21_strcspn(s1, s2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_strcspn_one_symbol) {
  char *s1 = "xyzzzbbbfd";
  char *s2 = "b";
  int result1 = strcspn(s1, s2);
  int result2 = s21_strcspn(s1, s2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_strcspn_two_symbol) {
  char *s1 = "xyzzzbbbfd";
  char *s2 = "xb";
  int result1 = strcspn(s1, s2);
  int result2 = s21_strcspn(s1, s2);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_strerror_negative) {
  char *s1 = s21_strerror(-10);
  char *s2 = strerror(-10);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_strerror_zero) {
  char *s1 = s21_strerror(0);
  char *s2 = strerror(0);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_strerror_positive) {
  char *s1 = s21_strerror(20);
  char *s2 = strerror(20);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_strerror_offside) {
  char *s1 = s21_strerror(200);
  char *s2 = strerror(200);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_strlen_empty_str) {
  char *s1 = "";
  int result1 = strlen(s1);
  int result2 = s21_strlen(s1);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_strlen) {
  char *s1 = "12344567890";
  int result1 = strlen(s1);
  int result2 = s21_strlen(s1);
  ck_assert_int_eq(result1, result2);
}
END_TEST

START_TEST(test_strpbrk_two_empty_str) {
  char *s1 = "";
  char *s2 = "";
  char *result1 = strpbrk(s1, s2);
  char *result2 = s21_strpbrk(s1, s2);
  ck_assert_ptr_eq(result1, result2);
}
END_TEST

START_TEST(test_strpbrk_first_empty_str) {
  char *s1 = "";
  char *s2 = "xy";
  char *result1 = strpbrk(s1, s2);
  char *result2 = s21_strpbrk(s1, s2);
  ck_assert_ptr_eq(result1, result2);
}
END_TEST

START_TEST(test_strpbrk) {
  char *s1 = "abcxyz";
  char *s2 = "zy";
  char *result1 = strpbrk(s1, s2);
  char *result2 = s21_strpbrk(s1, s2);
  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strpbrk_not_found) {
  char *s1 = "abcxyz";
  char *s2 = "pqr";
  char *result1 = strpbrk(s1, s2);
  char *result2 = s21_strpbrk(s1, s2);
  ck_assert_ptr_eq(result1, result2);
}
END_TEST

START_TEST(test_strstr_second_empty_str) {
  char *s1 = "xyzbcd";
  char *s2 = "";
  char *result1 = strstr(s1, s2);
  char *result2 = s21_strstr(s1, s2);
  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strstr) {
  char *s1 = "aabbcc";
  char *s2 = "bb";
  char *result1 = strstr(s1, s2);
  char *result2 = s21_strstr(s1, s2);
  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strstr_not_found) {
  char *s1 = "mmnnoo";
  char *s2 = "abc";
  char *result1 = strstr(s1, s2);
  char *result2 = s21_strstr(s1, s2);
  ck_assert_ptr_eq(result1, result2);
}
END_TEST

START_TEST(test_strstr_two_empty_str_full) {
  char *s1 = "Some text here!";
  char *s2 = "Some text here!";
  char *result1 = strstr(s1, s2);
  char *result2 = s21_strstr(s1, s2);
  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strstr_two_empty_str_one_word) {
  char *s1 = "One random test data";
  char *s2 = "test";
  char *result1 = strstr(s1, s2);
  char *result2 = s21_strstr(s1, s2);
  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strstr_two_empty_str_specify) {
  char *s1 = "Check, please!";
  char *s2 = "!";
  char *result1 = strstr(s1, s2);
  char *result2 = s21_strstr(s1, s2);
  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strstr_two_empty_str_testing_word) {
  char *s1 = "This is a nice string";
  char *s2 = "nice";
  char *result1 = strstr(s1, s2);
  char *result2 = s21_strstr(s1, s2);
  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strstr_two_empty_str_susping_work) {
  char *s1 = "bub";
  char *s2 = "susp";
  char *result1 = strstr(s1, s2);
  char *result2 = s21_strstr(s1, s2);
  ck_assert_ptr_eq(result1, result2);
}
END_TEST

START_TEST(test_strtok_empty_delim) {
  char s1[30] = "12, 34; 56| 78. 90/ 12; 34";
  char s2[30] = "12, 34; 56| 78. 90/ 12; 34";
  char *delim = "";
  char *result1 = strtok(s1, delim);
  char *result2 = s21_strtok(s2, delim);
  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strtok_not_found_delim) {
  char s1[30] = "12, 34; 56| 78. 90/ 12; 34";
  char s2[30] = "12, 34; 56| 78. 90/ 12; 34";
  char *delim = "-";
  char *result1 = strtok(s1, delim);
  char *result2 = s21_strtok(s2, delim);
  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strtok_null) {
  char s1[30] = "12, 34; 56| 78. 90/ 12; 34";
  char s2[30] = "12, 34; 56| 78. 90/ 12; 34";
  char *delim = ";";
  char *result1 = strtok(s1, delim);
  char *result2 = s21_strtok(s2, delim);
  result1 = strtok(NULL, delim);
  result2 = s21_strtok(s21_NULL, delim);
  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strtok) {
  char s1[30] = "12, 34; 56| 78. 90/ 12; 34";
  char *delim = ";";
  char *result1 = strtok(s1, delim);
  char *result2 = s21_strtok(s1, delim);
  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_to_upper) {
  char str[16] = "HeLlo wOrlD";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, "HELLO WORLD");
  free(result);
}
END_TEST

START_TEST(test_to_upper_empty_str) {
  char str[16] = "";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_to_upper_not_char_str) {
  char str[16] = "3/";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, "3/");
  free(result);
}
END_TEST

START_TEST(test_to_lower) {
  char *result = s21_to_lower("HeLlo wOrlD");
  ck_assert_str_eq(result, "hello world");
  free(result);
}
END_TEST

START_TEST(test_to_lower_empty_str) {
  char *result = s21_to_lower("");
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_to_lower_not_char_str) {
  char *result = s21_to_lower("3/");
  ck_assert_str_eq(result, "3/");
  free(result);
}
END_TEST

START_TEST(test_insert) {
  char *result = s21_insert("greetings buddy", "my brave ", 9);
  ck_assert_str_eq(result, "greetingsmy brave  buddy");
  free(result);
}
END_TEST

START_TEST(test_insert_in_start) {
  char *result = s21_insert("greetings buddy", "ABC ", 0);
  ck_assert_str_eq(result, "ABC greetings buddy");
  free(result);
}
END_TEST

START_TEST(test_insert_return_null) {
  char *result = s21_insert("", "my brave ", 0);
  ck_assert_str_eq(result, "my brave ");
  free(result);
}
END_TEST

START_TEST(test_insert_substring_empty) {
  char *result = s21_insert("xyz", "", 1);
  ck_assert_str_eq(result, "xyz");
  free(result);
}
END_TEST

START_TEST(test_insert_empty_str) {
  char *result = s21_insert("", "", 1);
  ck_assert_ptr_eq(result, s21_NULL);
  free(result);
}
END_TEST

START_TEST(test_insert_second_null) {
  char *result = s21_insert("zxc", s21_NULL, 0);
  ck_assert_ptr_eq(result, s21_NULL);
  free(result);
}
END_TEST

START_TEST(test_insert_two_null) {
  char *result = s21_insert(s21_NULL, s21_NULL, 0);
  ck_assert_ptr_eq(result, s21_NULL);
  free(result);
}
END_TEST

START_TEST(test_insert_zero) {
  char *result = s21_insert("some-data", "ins", 20);
  ck_assert_ptr_eq(result, s21_NULL);
  free(result);
}
END_TEST

START_TEST(test_trim) {
  char *result = s21_trim("  xyzabc opq  ", "xyc ");
  ck_assert_str_eq(result, "zabc opq");
  free(result);
}
END_TEST

START_TEST(test_trim_empty_str) {
  char *result = s21_trim("", "wer");
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_trim_all_delete) {
  char *result = s21_trim("fffgg", "fg");
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_trim_empty_all_str) {
  char *result = s21_trim("", "");
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_trim_empty_null_str) {
  char *result = s21_trim(s21_NULL, "");
  ck_assert_ptr_eq(result, s21_NULL);
  free(result);
}
END_TEST

START_TEST(test_trim_empty_str_secnod_empty) {
  char *result = s21_trim(" abc ", "");
  ck_assert_str_eq(result, " abc ");
  free(result);
}
END_TEST

START_TEST(test_specifier_c) {
  char c = 'z';
  char result1[200] = "\0";
  char result2[200] = "\0";
  char *format = "Check:%csd";
  int len1 = sprintf(result1, format, c, 1);
  int len2 = s21_sprintf(result2, format, c, 1);
  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_specifier_d) {
  int d = 10;
  char result1[200] = "\0";
  char result2[200] = "\0";
  char *format = "Check:%dsd";
  int len1 = sprintf(result1, format, d);
  int len2 = s21_sprintf(result2, format, d);
  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_specifier_d_zero) {
  int d = 0;
  char result1[200] = "\0";
  char result2[200] = "\0";
  char *format = "Check:%dsd";
  int len1 = sprintf(result1, format, d);
  int len2 = s21_sprintf(result2, format, d);
  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_specifier_f) {
  float f = 10.999;
  char result1[200] = "\0";
  char result2[200] = "\0";
  char *format = "Check:%fsd";
  int len1 = sprintf(result1, format, f);
  int len2 = s21_sprintf(result2, format, f);
  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_specifier_s) {
  char s[20] = "corrre12!";
  char result1[200] = "\0";
  char result2[200] = "\0";
  char *format = "Check:%s";
  int len1 = sprintf(result1, format, s);
  int len2 = s21_sprintf(result2, format, s);
  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_specifier_u) {
  unsigned int u = 102;
  char result1[200] = "\0";
  char result2[200] = "\0";
  char *format = "Check:%u";
  int len1 = sprintf(result1, format, u);
  int len2 = s21_sprintf(result2, format, u);
  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_flag_minus_d) {
  int number = 120;
  char result1[200] = "\0";
  char result2[200] = "\0";
  char *format = "Check:%-das";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);
  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_flag_plus_f) {
  float number = 99.9999;
  char result1[200] = "\0";
  char result2[200] = "\0";
  char *format = "Check:%+fas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);
  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_flag_plus_d) {
  int number = 99;
  char result1[200] = "\0";
  char result2[200] = "\0";
  char *format = "Check:%+das";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);
  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_h_d) {
  short number = 120;
  char result1[200] = "\0";
  char result2[200] = "\0";
  char *format = "Check:%hdas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);
  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_h_u) {
  unsigned short number = 120;
  char result1[200] = "\0";
  char result2[200] = "\0";
  char *format = "Check:%huas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);
  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_l_d) {
  long number = 120;
  char result1[200] = "\0";
  char result2[200] = "\0";
  char *format = "Check:%ldas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);
  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_length_l_u) {
  unsigned long number = 120;
  char result1[200] = "\0";
  char result2[200] = "\0";
  char *format = "Check:%luas";
  int len1 = sprintf(result1, format, number);
  int len2 = s21_sprintf(result2, format, number);
  ck_assert_str_eq(result1, result2);
  ck_assert_int_eq(len1, len2);
}
END_TEST

START_TEST(test_strrchr_empty_str) {
  char s1[20] = "";
  char *result1 = strrchr(s1, 'a');
  char *result2 = s21_strrchr(s1, 'a');
  ck_assert_ptr_eq(result1, result2);
}
END_TEST

START_TEST(test_strrchr_one_char_match) {
  char s1[20] = "b";
  char *result1 = strrchr(s1, 'b');
  char *result2 = s21_strrchr(s1, 'b');
  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strrchr_one_char_no_match) {
  char s1[20] = "b";
  char *result1 = strrchr(s1, 'z');
  char *result2 = s21_strrchr(s1, 'z');
  ck_assert_ptr_eq(result1, result2);
}
END_TEST

START_TEST(test_strrchr_multiple_occurrences) {
  char s1[20] = "banana";
  char *result1 = strrchr(s1, 'a');
  char *result2 = s21_strrchr(s1, 'a');
  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strrchr_not_found) {
  char s1[20] = "banana";
  char *result1 = strrchr(s1, 'z');
  char *result2 = s21_strrchr(s1, 'z');
  ck_assert_ptr_eq(result1, result2);
}
END_TEST

START_TEST(test_strrchr_find_null_terminator) {
  char s1[20] = "abc\0def";
  char *result1 = strrchr(s1, '\0');
  char *result2 = s21_strrchr(s1, '\0');
  ck_assert_ptr_eq(result1, result2);
}
END_TEST

Suite *create_test_suite() {
  Suite *suite = suite_create("String+ tests");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_memchr_1);
  tcase_add_test(tc_core, test_memchr_empty_str);
  tcase_add_test(tc_core, test_memchr_n_less_str);
  tcase_add_test(tc_core, test_memchr_not_found_in_n);
  tcase_add_test(tc_core, test_memchr_null_terminator);
  tcase_add_test(tc_core, test_memcpy_second_less);
  tcase_add_test(tc_core, test_memcpy_second_more);
  tcase_add_test(tc_core, test_memcpy_eq_str);
  tcase_add_test(tc_core, test_memcpy_big_n);
  tcase_add_test(tc_core, test_strrchr_empty_str);
  tcase_add_test(tc_core, test_strrchr_one_char_match);
  tcase_add_test(tc_core, test_strrchr_one_char_no_match);
  tcase_add_test(tc_core, test_strrchr_multiple_occurrences);
  tcase_add_test(tc_core, test_strrchr_not_found);
  tcase_add_test(tc_core, test_strrchr_find_null_terminator);
  tcase_add_test(tc_core, test_memcpy_second_str_null_term);
  tcase_add_test(tc_core, test_memcpy_second_str_zero_n);
  tcase_add_test(tc_core, test_memcpy_second_str_term_null);
  tcase_add_test(tc_core, test_memcpy_second_str_term_null_num);
  tcase_add_test(tc_core, test_memset_null_terminator);
  tcase_add_test(tc_core, test_memset_str_eq);
  tcase_add_test(tc_core, test_memcmp);
  tcase_add_test(tc_core, test_memcmp_first_less_second);
  tcase_add_test(tc_core, test_memcmp_first_more_second);
  tcase_add_test(tc_core, test_memcmp_eq_n);
  tcase_add_test(tc_core, test_memcmp_n_large);
  tcase_add_test(tc_core, test_memcmp_n_less_str);
  tcase_add_test(tc_core, test_strncat);
  tcase_add_test(tc_core, test_strncat_first_empty_str);
  tcase_add_test(tc_core, test_strncat_two_empty_str);
  tcase_add_test(tc_core, test_strchr_empty_str);
  tcase_add_test(tc_core, test_strchr_found_end);
  tcase_add_test(tc_core, test_strchr);
  tcase_add_test(tc_core, test_strchr_not_found);
  tcase_add_test(tc_core, test_strchr_null_terminator);
  tcase_add_test(tc_core, test_strchr_find_null_terminator);
  tcase_add_test(tc_core, test_strncmp_first_str_big);
  tcase_add_test(tc_core, test_strncmp_second_str_big);
  tcase_add_test(tc_core, test_strncmp_null_terminator);
  tcase_add_test(tc_core, test_strncmp_str_eq);
  tcase_add_test(tc_core, test_strncpy_overwrite_null_terminator);
  tcase_add_test(tc_core, test_strncpy_src_less_n);
  tcase_add_test(tc_core, test_strncpy);
  tcase_add_test(tc_core, test_strcspn_one_symbol);
  tcase_add_test(tc_core, test_strcspn_two_symbol);
  tcase_add_test(tc_core, test_strcspn_zero);
  tcase_add_test(tc_core, test_strerror_negative);
  tcase_add_test(tc_core, test_strerror_positive);
  tcase_add_test(tc_core, test_strerror_zero);
  tcase_add_test(tc_core, test_strerror_offside);
  tcase_add_test(tc_core, test_strlen);
  tcase_add_test(tc_core, test_strlen_empty_str);
  tcase_add_test(tc_core, test_strpbrk_first_empty_str);
  tcase_add_test(tc_core, test_strpbrk_two_empty_str);
  tcase_add_test(tc_core, test_strpbrk);
  tcase_add_test(tc_core, test_strpbrk_not_found);
  tcase_add_test(tc_core, test_strstr);
  tcase_add_test(tc_core, test_strstr_not_found);
  tcase_add_test(tc_core, test_strstr_second_empty_str);
  tcase_add_test(tc_core, test_strstr_two_empty_str_full);
  tcase_add_test(tc_core, test_strstr_two_empty_str_one_word);
  tcase_add_test(tc_core, test_strstr_two_empty_str_specify);
  tcase_add_test(tc_core, test_strstr_two_empty_str_testing_word);
  tcase_add_test(tc_core, test_strstr_two_empty_str_susping_work);
  tcase_add_test(tc_core, test_strtok_empty_delim);
  tcase_add_test(tc_core, test_strtok_not_found_delim);
  tcase_add_test(tc_core, test_strtok_null);
  tcase_add_test(tc_core, test_strtok);
  tcase_add_test(tc_core, test_to_upper);
  tcase_add_test(tc_core, test_to_upper_empty_str);
  tcase_add_test(tc_core, test_to_upper_not_char_str);
  tcase_add_test(tc_core, test_to_lower);
  tcase_add_test(tc_core, test_to_lower_empty_str);
  tcase_add_test(tc_core, test_to_lower_not_char_str);
  tcase_add_test(tc_core, test_insert);
  tcase_add_test(tc_core, test_insert_zero);
  tcase_add_test(tc_core, test_insert_two_null);
  tcase_add_test(tc_core, test_insert_second_null);
  tcase_add_test(tc_core, test_insert_empty_str);
  tcase_add_test(tc_core, test_insert_in_start);
  tcase_add_test(tc_core, test_insert_return_null);
  tcase_add_test(tc_core, test_insert_substring_empty);
  tcase_add_test(tc_core, test_trim);
  tcase_add_test(tc_core, test_trim_empty_str);
  tcase_add_test(tc_core, test_trim_all_delete);
  tcase_add_test(tc_core, test_trim_empty_all_str);
  tcase_add_test(tc_core, test_trim_empty_null_str);
  tcase_add_test(tc_core, test_trim_empty_str_secnod_empty);

  tcase_add_test(tc_core, test_specifier_c);
  tcase_add_test(tc_core, test_specifier_d);
  tcase_add_test(tc_core, test_specifier_d_zero);
  tcase_add_test(tc_core, test_specifier_f);
  tcase_add_test(tc_core, test_specifier_s);
  tcase_add_test(tc_core, test_specifier_u);

  tcase_add_test(tc_core, test_flag_minus_d);
  tcase_add_test(tc_core, test_flag_plus_f);
  tcase_add_test(tc_core, test_flag_plus_d);

  tcase_add_test(tc_core, test_length_h_d);
  tcase_add_test(tc_core, test_length_h_u);
  tcase_add_test(tc_core, test_length_l_d);
  tcase_add_test(tc_core, test_length_l_u);

  suite_add_tcase(suite, tc_core);
  return suite;
}

int main() {
  int number_failed;
  SRunner *sr;
  Suite *suite = create_test_suite();
  sr = srunner_create(suite);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}
