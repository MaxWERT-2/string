#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

#define STR_SIZE 100

/* sprintf_no_spec */
static const char* sprintf_str_no_spec[10] = {
    "abc", "123",   "",   "sd\0", "\\\\df\n",
    "\0",  "1//\\", "%%", "\\%%", "\t\\\n"};

/* sprintf_d_spec */
static const char* sprintf_str_d_spec[11] = {
    "%d",  "%20d", "%.20d", "%.d",   "%-10d",
    "%hd", "%+d",  "% d",   "%20hd", "asn%+-12.8hdas\n",
    "%.d"};
static const int sprintf_int_d_spec[11] = {
    0, 12, -2314, 0, -8, 10000000, 123, -14, 1121211212, 9, -123};

/* sprintf_u_spec */
static const char* sprintf_str_u_spec[10] = {
    "%u",  "%20u",  "%.20u",  "%.u",   "%-10u",
    "%hu", "as%1u", "as%u\n", "%20hu", "asn%-12.8huas\n"};
static const int sprintf_int_u_spec[10] = {123,      12,  2314, 0,        8,
                                           10000000, 123, 14,   12121212, 9};

/* sprintf_f_spec */
static const char* sprintf_str_f_spec[18] = {
    "%f",        "%20f",    "%.15f",  "%.f1",  "%-10f",
    "% f",       "as% 1f",  "as%f\n", "%20f",  "asn%-12.8fas\n",
    "\\%+12.f2", "%1.fas3", "% fa4",  "%+.f5", "asas%-.1fasas",
    "a%.f",      "%4.fas",  "%f"};
static const float sprintf_int_f_spec[18] = {
    123.23,        -12.232323, 0.003, 0,          8,    -100.0000,    1.23,
    0.14121212,    1212.1212,  9,     0.0000134,  -123, 0.0000000001, -0.001,
    1234567890123, 0.00000001, 0.1,   12345678934};

/* memchr */
static const void* memchr_str[8] = {"abc", "abcdef", "abcdef",  "aaaa",
                                    "abc", "abcdef", "abcdcef", "aaaa"};
static int memchr_c[8] = {'a', 'f', 'c', 'b', 'a', 'f', 'c', 'b'};
static const unsigned int memchr_n[8] = {3, 6, 6, 4, 2, 3, 10, 2};

/* memcmp strncmp*/
static const void* memcmp_str1[13] = {
    "abc",       "Abc",    "abCdef", "abc", "abc", "abcdef", "abcbef",
    "abcbefmmm", "ABCDEF", "abcbef", "abc", "abc", "abcd"};
static const void* memcmp_str2[13] = {
    "abc",    "abc",    "abc",    "Abcdef", "abC",  "abcdef", "abcdefmmm",
    "abcdef", "abcdef", "abcbef", "defgh",  "abcd", "abc"};
static const unsigned int memcmp_n[13] = {3, 3, 3,  3,  3,  3, 6,
                                          3, 6, 10, 11, 11, 11};

/* memcpy memmove */
static void** memcpy_memmove_dest1[9][10] = {{(void*){""}},
                                             {(void*){""}},
                                             {(void*){""}},
                                             {(void*){"mmmdsef"}},
                                             {(void*){"mmmdsefghjhds"}},
                                             {(void*){"mmmdsef"}},
                                             {(void*){"ab"}},
                                             {(void*){"ab"}},
                                             {(void*){"ab"}}};
static void** memcpy_memmove_dest2[9][10] = {{(void*){""}},
                                             {(void*){""}},
                                             {(void*){""}},
                                             {(void*){"mmmdsef"}},
                                             {(void*){"mmmdsefghjhds"}},
                                             {(void*){"mmmdsef"}},
                                             {(void*){"ab"}},
                                             {(void*){"ab"}},
                                             {(void*){"ab"}}};
static const void* memcpy_memmove_src = (void*)"abc";
static const unsigned int memcpy_memmove_n[9] = {3, 1, 10, 3, 1, 10, 3, 1, 10};

/* memset*/
static void* memset_str1[4][10] = {{}, {"mmmdsef"}, {"ab"}, {"12345678910"}};
static void* memset_str2[4][10] = {{}, {"mmmdsef"}, {"ab"}, {"12345678910"}};
static const int memset_c[3] = {'a', 'f', '\n'};
static const unsigned int memset_n[3] = {3, 1, 10};

/* strcat strncat */
static char strcat_dest1[1024] = "";
static char strcat_dest2[1024] = "";
static const char* strcat_src[7] = {
    "Techie ", "Delight ", "- ", "Ace ", "the ", "Technical ", "Interviews"};
static const unsigned int strncat_n[7] = {6, 1, 10, 5, 2, 1, 0};

/* strchr */
static const char* strchr_str[4] = {"abc", "abcdef", "aaaa", "affdef"};
static int strchr_c[4] = {'a', 'f', 'b', 'f'};

/* strcmp */
static const char* strcmp_str1[6] = {"abc", "Abc",    "abC",
                                     "abc", "abcdef", "abCdef"};
static const char* strcmp_str2[6] = {"abc",    "abc", "abc",
                                     "abcdef", "abc", "abcdef"};

/* strcpy */
static char strcpy_dest1[3][10] = {"", "mmmdsef", "ab"};
static char strcpy_dest2[3][10] = {"", "mmmdsef", "ab"};
static const char* strcpy_src = "abc";

/* strcpy */
static char strncpy_dest1[9][10] = {
    "", "", "", "mmmdsef", "mmmdsefghj", "mmmdsef", "ab", "ab", "ab"};
static char strncpy_dest2[9][10] = {
    "", "", "", "mmmdsef", "mmmdsefghj", "mmmdsef", "ab", "ab", "ab"};
static const char* strncpy_src = "abc";
static const unsigned int strncpy_n[9] = {3, 1, 10, 3, 1, 10, 3, 1, 10};

/* strlen*/
static char* strlen_str[8] = {"Hello world\0",
                              "Hello world\n\0",
                              "a\n\0",
                              " \n\0",
                              " \0",
                              "\n\0",
                              "\0",
                              ""};

/* strcspn */
static const char* strcspn_str1[7] = {"0123456789", "0123456789", "0123456789",
                                      "0123456789", "",           "",
                                      "0123456789"};
static const char* strcspn_str2[7] = {"9876", "0", "1", "", "abc", "", "0000"};

/* strpbrk */
static const char* strpbrk_str1[7] = {"0123456789", "0123456789", "0123456789",
                                      "0123456789", "",           "",
                                      "0123456789"};
static const char* strpbrk_str2[7] = {"369", "0", "1", "", "abc", "", "0000"};

/* strrchr */
static const char* strrchr_str[5] = {"abca", "abfcdeff", "aaaa", "affdef",
                                     "abeca"};
static int strrchr_c[5] = {'a', 'f', 'b', 'f', 'e'};

/* strspn */
static const char* strspn_str1[8] = {"0123456789", "0123456789", "0123456789",
                                     "0123456789", "",           "",
                                     "0123456789", "0123456789"};
static const char* strspn_str2[8] = {"210", "123", "abc",  "",
                                     "abc", "",    "0000", "1111"};

/* strstr */
static const char* strstr_str1[8] = {
    "0123456789", "0123456789",    "0123456789", "0123456789",
    "0123456789", "345          ", "1",          "0123456789"};
static const char* strstr_str2[8] = {"345", "012",        "0", "1",
                                     "",    "0123456789", "1", "0000"};

/* sprintf */
START_TEST(test_case_sprintf_1) {
  char s1[STR_SIZE];
  char s2[STR_SIZE];
  s21_sprintf(s1, "as%#*.*e", 10, 5, 0.0000001);
  sprintf(s2, "as%#*.*e", 10, 5, 0.0000001);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_case_sprintf_2) {
  char s1[STR_SIZE];
  char s2[STR_SIZE];
  ck_assert_int_eq(s21_sprintf(s1, "as%#*.*e", 10, 5, 0.0000001),
                   sprintf(s2, "as%#*.*e", 10, 5, 0.0000001));
}
END_TEST

START_TEST(test_case_sprintf_3) {
  char s1[STR_SIZE];
  char s2[STR_SIZE];
  s21_sprintf(s1, "as%015.*LE12", 5, (long double)1.234343);
  sprintf(s2, "as%015.*LE12", 5, (long double)1.234343);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_case_sprintf_4) {
  char s1[STR_SIZE];
  char s2[STR_SIZE];
  int n1 = 0, n2 = 0;
  s21_sprintf(s1, "as%-15.*lx12%n", 5, (long int)1203489, &n1);
  sprintf(s2, "as%-15.*lx12%n", 5, (long int)1203489, &n2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(test_case_sprintf_5) {
  char s1[STR_SIZE];
  char s2[STR_SIZE];
  s21_sprintf(s1, "as%15.*lX12%20g", 5, (long int)984398, 1.0000);
  sprintf(s2, "as%15.*lX12%20g", 5, (long int)984398, 1.0000);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_case_sprintf_6) {
  char s1[STR_SIZE];
  char s2[STR_SIZE];
  int a = 0;
  s21_sprintf(s1, "as%.*o%%%20p", 10, 984398, &a);
  sprintf(s2, "as%.*o%%%20p", 10, 984398, &a);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_case_sprintf_7) {
  char s1[STR_SIZE];
  char s2[STR_SIZE];
  s21_sprintf(s1, "as%.*o%%%20Lg", 10, 984398, (long double)0.00001);
  sprintf(s2, "as%.*o%%%20Lg", 10, 984398, (long double)0.00001);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_case_sprintf_8) {
  char s1[STR_SIZE];
  char s2[STR_SIZE];
  s21_sprintf(s1, "as%.*o%%%20g", 10, 984398, 0.00001);
  sprintf(s2, "as%.*o%%%20g", 10, 984398, 0.00001);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_case_sprintf_9) {
  char s1[STR_SIZE];
  char s2[STR_SIZE];
  s21_sprintf(s1, "as%15.*lX12%20Lg", 5, (long int)984398, (long double)1.0000);
  sprintf(s2, "as%15.*lX12%20Lg", 5, (long int)984398, (long double)1.0000);
  ck_assert_str_eq(s1, s2);
}
END_TEST

/* sprintf_no_spec */
START_TEST(test_case_sprintf_no_spec) {
  char s1[STR_SIZE];
  char s2[STR_SIZE];
  s21_sprintf(s1, sprintf_str_no_spec[_i]);
  sprintf(s2, sprintf_str_no_spec[_i]);
  ck_assert_str_eq(s1, s2);
}
END_TEST

/* sprintf_d_spec */
START_TEST(test_case_sprintf_d_spec) {
  char s1[STR_SIZE];
  char s2[STR_SIZE];
  s21_sprintf(s1, sprintf_str_d_spec[_i], sprintf_int_d_spec[_i]);
  sprintf(s2, sprintf_str_d_spec[_i], sprintf_int_d_spec[_i]);
  ck_assert_str_eq(s1, s2);
}
END_TEST

/* sprintf_u_spec */
START_TEST(test_case_sprintf_u_spec) {
  char s1[STR_SIZE];
  char s2[STR_SIZE];
  s21_sprintf(s1, sprintf_str_u_spec[_i], sprintf_int_u_spec[_i]);
  sprintf(s2, sprintf_str_u_spec[_i], sprintf_int_u_spec[_i]);
  ck_assert_str_eq(s1, s2);
}
END_TEST

/* sprintf_f_spec */
START_TEST(test_case_sprintf_f_spec) {
  char s1[STR_SIZE];
  char s2[STR_SIZE];
  s21_sprintf(s1, sprintf_str_f_spec[_i], sprintf_int_f_spec[_i]);
  sprintf(s2, sprintf_str_f_spec[_i], sprintf_int_f_spec[_i]);
  ck_assert_str_eq(s1, s2);
}
END_TEST

/* memchr */
START_TEST(test_case_memchr) {
  ck_assert_ptr_eq(s21_memchr(memchr_str[_i], memchr_c[_i], memchr_n[_i]),
                   memchr(memchr_str[_i], memchr_c[_i], memchr_n[_i]));
}
END_TEST

/* memcmp */
START_TEST(test_case_memcmp) {
  ck_assert_int_eq(s21_memcmp(memcmp_str1[_i], memcmp_str2[_i], memcmp_n[_i]),
                   memcmp(memcmp_str1[_i], memcmp_str2[_i], memcmp_n[_i]));
}
END_TEST

/* memcpy */
START_TEST(test_case_memcpy) {
  ck_assert_str_eq(s21_memcpy(memcpy_memmove_dest1[_i], memcpy_memmove_src,
                              memcpy_memmove_n[_i]),
                   memcpy(memcpy_memmove_dest2[_i], memcpy_memmove_src,
                          memcpy_memmove_n[_i]));
}
END_TEST

/* memmove */
START_TEST(test_case_memmove) {
  ck_assert_str_eq(s21_memmove(memcpy_memmove_dest1[_i], memcpy_memmove_src,
                               memcpy_memmove_n[_i]),
                   memmove(memcpy_memmove_dest2[_i], memcpy_memmove_src,
                           memcpy_memmove_n[_i]));
}
END_TEST

/* memset */
START_TEST(test_case_memset) {
  ck_assert_str_eq(s21_memset(memset_str1[0], memset_c[_i], memset_n[_i]),
                   memset(memset_str2[0], memset_c[_i], memset_n[_i]));
  ck_assert_str_eq(s21_memset(memset_str1[1], memset_c[_i], memset_n[_i]),
                   memset(memset_str2[1], memset_c[_i], memset_n[_i]));
  ck_assert_str_eq(s21_memset(memset_str1[2], memset_c[_i], memset_n[_i]),
                   memset(memset_str2[2], memset_c[_i], memset_n[_i]));
  ck_assert_str_eq(s21_memset(memset_str1[3], memset_c[_i], memset_n[_i]),
                   memset(memset_str2[3], memset_c[_i], memset_n[_i]));
}
END_TEST

/* strcat */
START_TEST(test_case_strcat) {
  ck_assert_str_eq(s21_strcat(strcat_dest1, strcat_src[_i]),
                   strcat(strcat_dest2, strcat_src[_i]));
}
END_TEST

/* strncat */
START_TEST(test_case_strncat) {
  ck_assert_str_eq(s21_strncat(strcat_dest1, strcat_src[_i], strncat_n[_i]),
                   strncat(strcat_dest2, strcat_src[_i], strncat_n[_i]));
}
END_TEST

/* strchr */
START_TEST(test_case_strchr) {
  ck_assert_ptr_eq(s21_strchr(strchr_str[_i], strchr_c[_i]),
                   strchr(strchr_str[_i], strchr_c[_i]));
}
END_TEST

/* strcmp */
START_TEST(test_case_strcmp) {
  ck_assert_int_eq(s21_strcmp(strcmp_str1[_i], strcmp_str2[_i]),
                   strcmp(strcmp_str1[_i], strcmp_str2[_i]));
}
END_TEST

/* strncmp */
START_TEST(test_case_strncmp) {
  ck_assert_int_eq(s21_strncmp(memcmp_str1[_i], memcmp_str2[_i], memcmp_n[_i]),
                   strncmp(memcmp_str1[_i], memcmp_str2[_i], memcmp_n[_i]));
}
END_TEST

/* strcpy */
START_TEST(test_case_strcpy) {
  ck_assert_str_eq(s21_strcpy(strcpy_dest1[_i], strcpy_src),
                   strcpy(strcpy_dest2[_i], strcpy_src));
}
END_TEST

/* strncpy */
START_TEST(test_case_strncpy) {
  ck_assert_str_eq(s21_strncpy(strncpy_dest1[_i], strncpy_src, strncpy_n[_i]),
                   strncpy(strncpy_dest2[_i], strncpy_src, strncpy_n[_i]));
}
END_TEST

/* strlen */
START_TEST(test_case_strlen) {
  ck_assert_int_eq(s21_strlen(strlen_str[_i]), strlen(strlen_str[_i]));
}
END_TEST

/* strcspn */
START_TEST(test_case_strcspn) {
  ck_assert_int_eq(s21_strcspn(strcspn_str1[_i], strcspn_str2[_i]),
                   strcspn(strcspn_str1[_i], strcspn_str2[_i]));
}
END_TEST

/* strpbrk */
START_TEST(test_case_strpbrk) {
  ck_assert_ptr_eq(s21_strpbrk(strpbrk_str1[_i], strpbrk_str2[_i]),
                   strpbrk(strpbrk_str1[_i], strpbrk_str2[_i]));
}
END_TEST

/* strrchr */
START_TEST(test_case_strrchr) {
  ck_assert_ptr_eq(s21_strrchr(strrchr_str[_i], strrchr_c[_i]),
                   strrchr(strrchr_str[_i], strrchr_c[_i]));
}
END_TEST

/* strspn */
START_TEST(test_case_strspn) {
  ck_assert_int_eq(s21_strspn(strspn_str1[_i], strspn_str2[_i]),
                   strspn(strspn_str1[_i], strspn_str2[_i]));
}
END_TEST

/* strstr */
START_TEST(test_case_strstr) {
  ck_assert_ptr_eq(s21_strstr(strstr_str1[_i], strstr_str2[_i]),
                   strstr(strstr_str1[_i], strstr_str2[_i]));
}
END_TEST

/* strtok */
START_TEST(test_case_strtok1) {
  char str[24] = " test1/test2/test3/test4";
  const char sep[10] = "/";
  ck_assert_ptr_eq(s21_strtok(str, sep), strtok(str, sep));
  ck_assert_ptr_eq(s21_strtok(str, sep), strtok(str, sep));
  ck_assert_ptr_eq(s21_strtok(str, sep), strtok(str, sep));
  ck_assert_ptr_eq(s21_strtok(str, sep), strtok(str, sep));
}
END_TEST

START_TEST(test_case_strtok2) {
  char str[24] = " test1/test2/test3/test4";
  const char sep[10] = "/";
  ck_assert_ptr_eq(s21_strtok(str, sep), strtok(str, sep));
  ck_assert_ptr_eq(s21_strtok(str, sep), strtok(str, sep));
  ck_assert_ptr_eq(s21_strtok(str, sep), strtok(str, sep));
  ck_assert_ptr_eq(s21_strtok(str, sep), strtok(str, sep));
  ck_assert_ptr_eq(s21_strtok(str, sep), strtok(str, sep));
  ck_assert_ptr_eq(s21_strtok(str, sep), strtok(str, sep));
  ck_assert_ptr_eq(s21_strtok(str, sep), strtok(str, sep));
  ck_assert_ptr_eq(s21_strtok(str, sep), strtok(str, sep));
}
END_TEST

START_TEST(test_case_strtok3) {
  char str[24] = " test1/test2/test3/test4";
  const char sep[10] = "/";
  ck_assert_ptr_eq(s21_strtok(str, sep), strtok(str, sep));
  ck_assert_ptr_eq(s21_strtok(str, sep), strtok(str, sep));
  ck_assert_ptr_eq(s21_strtok(str, sep), strtok(str, sep));
}
END_TEST

START_TEST(test_case_strtok4) {
  char str[] = "test1/test2/ test3/test4 ";
  const char sep[10] = "/ ";
  ck_assert_ptr_eq(s21_strtok(str, sep), strtok(str, sep));
  ck_assert_ptr_eq(s21_strtok(str, sep), strtok(str, sep));
  ck_assert_ptr_eq(s21_strtok(str, sep), strtok(str, sep));
  ck_assert_ptr_eq(s21_strtok(str, sep), strtok(str, sep));
  ck_assert_ptr_eq(s21_strtok(str, sep), strtok(str, sep));
  ck_assert_ptr_eq(s21_strtok(str, sep), strtok(str, sep));
}
END_TEST

START_TEST(test_case_strtok5) {
  char str[] = "";
  const char sep[10] = "";
  ck_assert_ptr_eq(s21_strtok(str, sep), strtok(str, sep));
}
END_TEST

START_TEST(test_case_strtok6) {
  // char str[] = s21_NULL;
  const char sep[10] = "";
  ck_assert_ptr_eq(s21_strtok(NULL, sep), strtok(NULL, sep));
}
END_TEST

/* strerror */
START_TEST(test_case_strerror) {
  for (int i = 1; i < N + 2; i++) {
    ck_assert_str_eq(strerror(i), s21_strerror(i));
  }
}
END_TEST

START_TEST(test_case_strerror_codes) {
#ifdef MAC
  ck_assert_str_eq(strerror(1), s21_strerror(EPERM));
  ck_assert_str_eq(strerror(11), s21_strerror(EDEADLK));
  ck_assert_str_eq(strerror(101), s21_strerror(ETIME));

#else
  ck_assert_str_eq(strerror(1), s21_strerror(EPERM));
  ck_assert_str_eq(strerror(42), s21_strerror(ENOMSG));
  ck_assert_str_eq(strerror(43), s21_strerror(EIDRM));

#endif  // MAC
}
END_TEST

/* to_upper */
START_TEST(test_case_to_upper_1) {
  const char* str = "HdfhddGGGGK123s";
  void* res = s21_to_upper(str);
  ck_assert_str_eq("HDFHDDGGGGK123S", res);
  free(res);
}
END_TEST

START_TEST(test_case_to_upper_2) {
  const char* str = "ABCD!!!!!123456";
  void* res = s21_to_upper(str);
  ck_assert_str_eq("ABCD!!!!!123456", res);
  free(res);
}
END_TEST

START_TEST(test_case_to_upper_3) {
  const char* str = "abcd";
  void* res = s21_to_upper(str);
  ck_assert_str_eq("ABCD", res);
  free(res);
}
END_TEST

/* to_lower */
START_TEST(test_case_to_lower_1) {
  const char* str = "HdfhddGGGGK123s";
  void* res = s21_to_lower(str);
  ck_assert_str_eq("hdfhddggggk123s", res);
  free(res);
}
END_TEST

START_TEST(test_case_to_lower_2) {
  const char* str = "ABCD!!!!!123456";
  void* res = s21_to_lower(str);
  ck_assert_str_eq("abcd!!!!!123456", res);
  free(res);
}
END_TEST

START_TEST(test_case_to_lower_3) {
  const char* str = "ABCD";
  void* res = s21_to_lower(str);
  ck_assert_str_eq("abcd", res);
  free(res);
}
END_TEST

/* insert */
START_TEST(test_case_insert_1) {
  const char* src = "aaabbb";
  const char* str = " ";
  s21_size_t start_index = 3;
  void* res = s21_insert(src, str, start_index);
  ck_assert_str_eq("aaa bbb", res);
  free(res);
}
END_TEST

START_TEST(test_case_insert_2) {
  const char* src = "aaabbb";
  const char* str = " fox ";
  s21_size_t start_index = 3;
  void* res = s21_insert(src, str, start_index);
  ck_assert_str_eq("aaa fox bbb", res);
  free(res);
}
END_TEST

START_TEST(test_case_insert_3) {
  const char* src = "aaabbb";
  const char* str = " fox ";
  s21_size_t start_index = 7;
  void* res = s21_insert(src, str, start_index);
  ck_assert_ptr_null(res);
  free(res);
}
END_TEST

START_TEST(test_case_insert_4) {
  const char* src = "aaabbb";
  const char* str = s21_NULL;
  s21_size_t start_index = 1;
  void* res = s21_insert(src, str, start_index);
  ck_assert_ptr_null(res);
  free(res);
}
END_TEST

START_TEST(test_case_trim) {
  char* str = (char*)s21_trim("****skat-riba*****", "*");
  char* str2 = "skat-riba";
  ck_assert_str_eq(str, str2);
  free(str);
  char* str3 = (char*)s21_trim("Sloniki", "iki");
  char* str4 = "Slon";
  ck_assert_str_eq(str3, str4);
  free(str3);

  char* str5 = (char*)s21_trim("", "999");
  char* str6 = "";
  ck_assert_str_eq(str5, str6);
  free(str5);

  char* str7 = (char*)s21_trim("1", "huli*5682");
  char* str8 = "1";
  ck_assert_str_eq(str7, str8);
  free(str7);

  char* str9 = (char*)s21_trim("66236934599", "69");
  char* str10 = "2369345";
  ck_assert_str_eq(str9, str10);
  free(str9);

  char* str11 = (char*)s21_trim("Sloniki", "Slosn");
  char* str12 = "iki";
  ck_assert_str_eq(str11, str12);
  free(str11);
}
END_TEST

Suite* example_suite_create(void) {
  Suite* suite = suite_create("s21_string+.h functions");

  /* sprintf */
  TCase* tcase_core_sprintf = tcase_create("sprintf");
  tcase_add_test(tcase_core_sprintf, test_case_sprintf_1);
  tcase_add_test(tcase_core_sprintf, test_case_sprintf_2);
  tcase_add_test(tcase_core_sprintf, test_case_sprintf_3);
  tcase_add_test(tcase_core_sprintf, test_case_sprintf_4);
  tcase_add_test(tcase_core_sprintf, test_case_sprintf_5);
  tcase_add_test(tcase_core_sprintf, test_case_sprintf_6);
  tcase_add_test(tcase_core_sprintf, test_case_sprintf_7);
  tcase_add_test(tcase_core_sprintf, test_case_sprintf_8);
  tcase_add_test(tcase_core_sprintf, test_case_sprintf_9);
  suite_add_tcase(suite, tcase_core_sprintf);

  /* sprintf_no_spec */
  TCase* tcase_core_sprintf_no_spec = tcase_create("sprintf_no_spec");
  tcase_add_loop_test(tcase_core_sprintf_no_spec, test_case_sprintf_no_spec, 0,
                      10);
  suite_add_tcase(suite, tcase_core_sprintf_no_spec);

  /* sprintf_d_spec */
  TCase* tcase_core_sprintf_d_spec = tcase_create("sprintf_d_spec");
  tcase_add_loop_test(tcase_core_sprintf_d_spec, test_case_sprintf_d_spec, 0,
                      11);
  suite_add_tcase(suite, tcase_core_sprintf_d_spec);

  /* sprintf_u_spec */
  TCase* tcase_core_sprintf_u_spec = tcase_create("sprintf_u_spec");
  tcase_add_loop_test(tcase_core_sprintf_u_spec, test_case_sprintf_u_spec, 0,
                      10);
  suite_add_tcase(suite, tcase_core_sprintf_u_spec);

  /* sprintf_f_spec */
  TCase* tcase_core_sprintf_f_spec = tcase_create("sprintf_f_spec");
  tcase_add_loop_test(tcase_core_sprintf_f_spec, test_case_sprintf_f_spec, 0,
                      18);
  suite_add_tcase(suite, tcase_core_sprintf_f_spec);

  /* memchr */
  TCase* tcase_core_memchr = tcase_create("memchr");
  tcase_add_loop_test(tcase_core_memchr, test_case_memchr, 0, 8);
  suite_add_tcase(suite, tcase_core_memchr);

  /* memcmp */
  TCase* tcase_core_memcmp = tcase_create("memcmp");
  tcase_add_loop_test(tcase_core_memcmp, test_case_memcmp, 0, 13);
  // tcase_add_loop_test(tcase_core_memcmp, test_case_memcmp, 0, 0);
  suite_add_tcase(suite, tcase_core_memcmp);

  /* memcpy */
  TCase* tcase_core_memcpy = tcase_create("memcpy");
  tcase_add_loop_test(tcase_core_memcpy, test_case_memcpy, 0, 9);
  suite_add_tcase(suite, tcase_core_memcpy);

  /* memmove */
  TCase* tcase_core_memmove = tcase_create("memmove");
  tcase_add_loop_test(tcase_core_memmove, test_case_memmove, 0, 9);
  suite_add_tcase(suite, tcase_core_memmove);

  /* memset */
  TCase* tcase_core_memset = tcase_create("memset");
  tcase_add_loop_test(tcase_core_memset, test_case_memset, 0, 3);
  suite_add_tcase(suite, tcase_core_memset);

  /* strcat*/
  TCase* tcase_core_strcat = tcase_create("strcat");
  tcase_add_loop_test(tcase_core_strcat, test_case_strcat, 0, 7);
  suite_add_tcase(suite, tcase_core_strcat);

  /* strncat*/
  TCase* tcase_core_strncat = tcase_create("strncat");
  tcase_add_loop_test(tcase_core_strncat, test_case_strncat, 0, 7);
  suite_add_tcase(suite, tcase_core_strncat);

  /* strchr */
  TCase* tcase_core_strchr = tcase_create("strchr");
  tcase_add_loop_test(tcase_core_strchr, test_case_strchr, 0, 4);
  suite_add_tcase(suite, tcase_core_strchr);

  /* strcmp */
  TCase* tcase_core_strcmp = tcase_create("strcmp");
  tcase_add_loop_test(tcase_core_strcmp, test_case_strcmp, 0, 6);

  // tcase_add_loop_test(tcase_core_strcmp, test_case_strcmp, 0, 0);
  suite_add_tcase(suite, tcase_core_strcmp);

  /* strncmp */
  TCase* tcase_core_strncmp = tcase_create("strncmp");
  tcase_add_loop_test(tcase_core_strncmp, test_case_strncmp, 0, 13);
  // tcase_add_loop_test(tcase_core_strncmp, test_case_strncmp, 0, 0);
  suite_add_tcase(suite, tcase_core_strncmp);

  /* strcpy */
  TCase* tcase_core_strcpy = tcase_create("strcpy");
  tcase_add_loop_test(tcase_core_strcpy, test_case_strcpy, 0, 3);
  suite_add_tcase(suite, tcase_core_strcpy);

  /* strncpy */
  TCase* tcase_core_strncpy = tcase_create("strncpy");
  tcase_add_loop_test(tcase_core_strncpy, test_case_strncpy, 0, 9);
  suite_add_tcase(suite, tcase_core_strncpy);

  /* strlen */
  TCase* tcase_core_strlen = tcase_create("strlen");
  tcase_add_loop_test(tcase_core_strlen, test_case_strlen, 0, 8);
  suite_add_tcase(suite, tcase_core_strlen);

  /* strcspn */
  TCase* tcase_core_strcspn = tcase_create("strcspn");
  tcase_add_loop_test(tcase_core_strcspn, test_case_strcspn, 0, 7);
  suite_add_tcase(suite, tcase_core_strcspn);

  /* strpbrk */
  TCase* tcase_core_strpbrk = tcase_create("strpbrk");
  tcase_add_loop_test(tcase_core_strpbrk, test_case_strpbrk, 0, 7);
  suite_add_tcase(suite, tcase_core_strpbrk);

  /* strrchr */
  TCase* tcase_core_strrchr = tcase_create("strrchr");
  tcase_add_loop_test(tcase_core_strrchr, test_case_strrchr, 0, 5);
  suite_add_tcase(suite, tcase_core_strrchr);

  /* strspn */
  TCase* tcase_core_strspn = tcase_create("strspn");
  tcase_add_loop_test(tcase_core_strspn, test_case_strspn, 0, 8);
  suite_add_tcase(suite, tcase_core_strspn);

  /* strstr */
  TCase* tcase_core_strstr = tcase_create("strstr");
  tcase_add_loop_test(tcase_core_strstr, test_case_strstr, 0, 8);
  suite_add_tcase(suite, tcase_core_strstr);

  /* strtok */
  TCase* tcase_core_strtok = tcase_create("strtok");
  tcase_add_test(tcase_core_strtok, test_case_strtok1);
  tcase_add_test(tcase_core_strtok, test_case_strtok2);
  tcase_add_test(tcase_core_strtok, test_case_strtok3);
  tcase_add_test(tcase_core_strtok, test_case_strtok4);
  tcase_add_test(tcase_core_strtok, test_case_strtok5);
  tcase_add_test(tcase_core_strtok, test_case_strtok6);
  suite_add_tcase(suite, tcase_core_strtok);

  /* strerror */
  TCase* tcase_core_strerror = tcase_create("strerror");
  tcase_add_test(tcase_core_strerror, test_case_strerror);
  tcase_add_test(tcase_core_strerror, test_case_strerror_codes);
  suite_add_tcase(suite, tcase_core_strerror);

  /* to_upper */
  TCase* tcase_core_to_upper = tcase_create("to_upper");
  tcase_add_test(tcase_core_to_upper, test_case_to_upper_1);
  tcase_add_test(tcase_core_to_upper, test_case_to_upper_2);
  tcase_add_test(tcase_core_to_upper, test_case_to_upper_3);
  // tcase_add_test(tcase_core_to_upper, test_case_to_upper_4);
  suite_add_tcase(suite, tcase_core_to_upper);

  /* to_lower */
  TCase* tcase_core_to_lower = tcase_create("to_lower");
  tcase_add_test(tcase_core_to_lower, test_case_to_lower_1);
  tcase_add_test(tcase_core_to_lower, test_case_to_lower_2);
  tcase_add_test(tcase_core_to_lower, test_case_to_lower_3);
  // tcase_add_test(tcase_core_to_lower, test_case_to_upper_4);
  suite_add_tcase(suite, tcase_core_to_lower);

  /* insert */
  TCase* tcase_core_insert = tcase_create("insert");
  tcase_add_test(tcase_core_insert, test_case_insert_1);
  tcase_add_test(tcase_core_insert, test_case_insert_2);
  tcase_add_test(tcase_core_insert, test_case_insert_3);
  tcase_add_test(tcase_core_insert, test_case_insert_4);
  // tcase_add_test(tcase_core_insert, test_case_insert_5);
  suite_add_tcase(suite, tcase_core_insert);

  /* trim */
  TCase* tcase_core_trim = tcase_create("trim");
  tcase_add_test(tcase_core_trim, test_case_trim);
  suite_add_tcase(suite, tcase_core_trim);

  return suite;
}

int main(void) {
  Suite* suite = example_suite_create();
  SRunner* suite_runner = srunner_create(suite);
  int nf;

  srunner_run_all(suite_runner, CK_ENV);
  nf = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  return nf == 0 ? 0 : 1;
}