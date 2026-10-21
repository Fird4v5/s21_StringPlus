#include <check.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

/*
 * Unit tests for the 15 required s21_string functions.
 * These tests compare the custom functions with the platform C library.
 */

START_TEST(test_memchr_basic) {
    char text[] = "hello world";
    ck_assert_ptr_eq(s21_memchr(text, 'w', 11), memchr(text, 'w', 11));
    ck_assert_ptr_eq(s21_memchr(text, 'z', 11), memchr(text, 'z', 11));
    ck_assert_ptr_eq(s21_memchr(text, 'l', 4), memchr(text, 'l', 4));
    ck_assert_ptr_eq(s21_memchr(text, '\0', sizeof(text)),
                     memchr(text, '\0', sizeof(text)));
}
END_TEST

START_TEST(test_memcmp_basic) {
    const char a[] = {1, 2, 3, 4};
    const char b[] = {1, 2, 3, 5};
    int actual = s21_memcmp(a, b, sizeof(a));
    int expected = memcmp(a, b, sizeof(a));
    ck_assert_int_eq((actual > 0) - (actual < 0),
                     (expected > 0) - (expected < 0));
    ck_assert_int_eq(s21_memcmp(a, b, 2), memcmp(a, b, 2));
    ck_assert_int_eq(s21_memcmp(a, a, sizeof(a)), 0);
    ck_assert_int_eq(s21_memcmp(a, b, 0), 0);
}
END_TEST

START_TEST(test_memcpy_basic) {
    const char source[] = "copy this";
    char actual[32] = {0};
    char expected[32] = {0};

    ck_assert_ptr_eq(s21_memcpy(actual, source, sizeof(source)), actual);
    ck_assert_ptr_eq(memcpy(expected, source, sizeof(source)), expected);
    ck_assert_int_eq(memcmp(actual, expected, sizeof(actual)), 0);

    char actual_zero[8] = "abc";
    char expected_zero[8] = "abc";
    s21_memcpy(actual_zero, "xyz", 0);
    memcpy(expected_zero, "xyz", 0);
    ck_assert_int_eq(memcmp(actual_zero, expected_zero, sizeof(actual_zero)), 0);
}
END_TEST

START_TEST(test_memset_basic) {
    char actual[10] = "abcdefghi";
    char expected[10] = "abcdefghi";

    ck_assert_ptr_eq(s21_memset(actual, 'x', 5), actual);
    ck_assert_ptr_eq(memset(expected, 'x', 5), expected);
    ck_assert_int_eq(memcmp(actual, expected, sizeof(actual)), 0);

    s21_memset(actual, 0, sizeof(actual));
    memset(expected, 0, sizeof(expected));
    ck_assert_int_eq(memcmp(actual, expected, sizeof(actual)), 0);
}
END_TEST

START_TEST(test_strncat_basic) {
    char actual[32] = "Hello ";
    char expected[32] = "Hello ";

    ck_assert_ptr_eq(s21_strncat(actual, "world!!!", 5), actual);
    ck_assert_ptr_eq(strncat(expected, "world!!!", 5), expected);
    ck_assert_str_eq(actual, expected);

    char actual_zero[16] = "abc";
    char expected_zero[16] = "abc";
    s21_strncat(actual_zero, "xyz", 0);
    strncat(expected_zero, "xyz", 0);
    ck_assert_str_eq(actual_zero, expected_zero);
}
END_TEST

START_TEST(test_strchr_basic) {
    const char text[] = "banana";
    ck_assert_ptr_eq(s21_strchr(text, 'a'), strchr(text, 'a'));
    ck_assert_ptr_eq(s21_strchr(text, 'n'), strchr(text, 'n'));
    ck_assert_ptr_eq(s21_strchr(text, 'z'), strchr(text, 'z'));
    ck_assert_ptr_eq(s21_strchr(text, '\0'), strchr(text, '\0'));
}
END_TEST

START_TEST(test_strncmp_basic) {
    const char *a = "abcdef";
    const char *b = "abcxyz";

    int actual = s21_strncmp(a, b, 6);
    int expected = strncmp(a, b, 6);
    ck_assert_int_eq((actual > 0) - (actual < 0),
                     (expected > 0) - (expected < 0));
    ck_assert_int_eq(s21_strncmp(a, b, 3), strncmp(a, b, 3));
    ck_assert_int_eq(s21_strncmp(a, a, 20), 0);
    ck_assert_int_eq(s21_strncmp(a, b, 0), 0);
}
END_TEST




START_TEST(test_strncpy_basic) {
    char actual[10] = {0};
    char expected[10] = {0};

    s21_strncpy(actual, "longer", 3);

    expected[0] = 'l';
    expected[1] = 'o';
    expected[2] = 'n';

    ck_assert_mem_eq(actual, expected, sizeof(actual));
}
END_TEST

START_TEST(test_strncpy_padding) {
    char actual[10] = "xxxxxxxxx";
    char expected[10] = "xxxxxxxxx";
    const char *src = "hi";

    s21_strncpy(actual, src, 5);
    strncpy(expected, src, 5);

    ck_assert_mem_eq(actual, expected, sizeof(actual));
}
END_TEST


START_TEST(test_strcspn_basic) {
    ck_assert_uint_eq(s21_strcspn("abcdef", "dx"), strcspn("abcdef", "dx"));
    ck_assert_uint_eq(s21_strcspn("abcdef", "xyz"), strcspn("abcdef", "xyz"));
    ck_assert_uint_eq(s21_strcspn("abcdef", "abc"), strcspn("abcdef", "abc"));
    ck_assert_uint_eq(s21_strcspn("abcdef", ""), strcspn("abcdef", ""));
}
END_TEST

START_TEST(test_strerror_basic) {
    int errors[] = {0, 1, 2, 5, 13, 22, 9999};
    for (size_t i = 0; i < sizeof(errors) / sizeof(errors[0]); i++) {
        char *actual = s21_strerror(errors[i]);
        char *expected = strerror(errors[i]);
        ck_assert_ptr_nonnull(actual);
        ck_assert_ptr_nonnull(expected);
        ck_assert_str_eq(actual, expected);
    }
}
END_TEST

START_TEST(test_strerror_edge_cases) {
    int errors[] = {-1, 41, 9999};

    for (size_t i = 0; i < sizeof(errors) / sizeof(errors[0]); i++) {
        char *actual = s21_strerror(errors[i]);
        char expected[64];

        snprintf(expected, sizeof(expected), "Unknown error %d", errors[i]);

        ck_assert_ptr_nonnull(actual);
        ck_assert_str_eq(actual, expected);
    }
}
END_TEST

START_TEST(test_strlen_basic) {
    ck_assert_uint_eq(s21_strlen("hello"), strlen("hello"));
    ck_assert_uint_eq(s21_strlen(""), strlen(""));
    ck_assert_uint_eq(s21_strlen("string library"), strlen("string library"));
}
END_TEST

START_TEST(test_strpbrk_basic) {
    const char *text = "hello world";
    ck_assert_ptr_eq(s21_strpbrk(text, "aeiou"), strpbrk(text, "aeiou"));
    ck_assert_ptr_eq(s21_strpbrk(text, "xyz"), strpbrk(text, "xyz"));
    ck_assert_ptr_eq(s21_strpbrk(text, "wod"), strpbrk(text, "wod"));
    ck_assert_ptr_eq(s21_strpbrk(text, ""), strpbrk(text, ""));
}
END_TEST

START_TEST(test_strrchr_basic) {
    const char text[] = "banana";
    ck_assert_ptr_eq(s21_strrchr(text, 'a'), strrchr(text, 'a'));
    ck_assert_ptr_eq(s21_strrchr(text, 'n'), strrchr(text, 'n'));
    ck_assert_ptr_eq(s21_strrchr(text, 'z'), strrchr(text, 'z'));
    ck_assert_ptr_eq(s21_strrchr(text, '\0'), strrchr(text, '\0'));
}
END_TEST

START_TEST(test_strstr_basic) {
    const char *text = "hello world";
    ck_assert_ptr_eq(s21_strstr(text, "world"), strstr(text, "world"));
    ck_assert_ptr_eq(s21_strstr(text, "hello"), strstr(text, "hello"));
    ck_assert_ptr_eq(s21_strstr(text, "xyz"), strstr(text, "xyz"));
    ck_assert_ptr_eq(s21_strstr(text, ""), strstr(text, ""));
}
END_TEST

START_TEST(test_strtok_basic) {
    char actual_text[] = ",one,,two,three,";
    char expected_text[] = ",one,,two,three,";
    const char *delimiters = ",";

    char *actual = s21_strtok(actual_text, delimiters);
    char *expected = strtok(expected_text, delimiters);

    while (actual != NULL && expected != NULL) {
        ck_assert_str_eq(actual, expected);
        actual = s21_strtok(NULL, delimiters);
        expected = strtok(NULL, delimiters);
    }

    ck_assert_ptr_null(actual);
    ck_assert_ptr_null(expected);
}
END_TEST


/* Helper: compare s21_sprintf with standard sprintf */
#define CHECK_SPRINTF(format, ...)                         \
    do {                                                   \
        char expected[1024];                               \
        char actual[1024];                                 \
        int expected_len = sprintf(expected, format,        \
                                   ##__VA_ARGS__);          \
        int actual_len = s21_sprintf(actual, format,        \
                                     ##__VA_ARGS__);        \
        ck_assert_int_eq(actual_len, expected_len);         \
        ck_assert_str_eq(actual, expected);                 \
    } while (0)

START_TEST(test_sprintf_plain_text) {
    CHECK_SPRINTF("Hello, world!");
    CHECK_SPRINTF("Hello %s", "Firdavs");
}
END_TEST

START_TEST(test_sprintf_percent) {
    CHECK_SPRINTF("100%%");
    CHECK_SPRINTF("%% %% %%");
}
END_TEST

START_TEST(test_sprintf_char) {
    CHECK_SPRINTF("%c", 'A');
    CHECK_SPRINTF("%5c", 'X');
    CHECK_SPRINTF("%-5c", 'X');
}
END_TEST

START_TEST(test_sprintf_string) {
    CHECK_SPRINTF("%s", "hello");
    CHECK_SPRINTF("%10s", "hello");
    CHECK_SPRINTF("%-10s", "hello");
    CHECK_SPRINTF("%.3s", "hello");
    CHECK_SPRINTF("%8.3s", "hello");
    CHECK_SPRINTF("%-8.3s", "hello");
}
END_TEST

START_TEST(test_sprintf_signed_integer) {
    CHECK_SPRINTF("%d", 123);
    CHECK_SPRINTF("%d", -123);
    CHECK_SPRINTF("%+d", 123);
    CHECK_SPRINTF("% d", 123);
    CHECK_SPRINTF("%8d", 123);
    CHECK_SPRINTF("%-8d", 123);
    CHECK_SPRINTF("%.5d", 123);
    CHECK_SPRINTF("%8.5d", 123);
    CHECK_SPRINTF("%hd", (short)123);
    CHECK_SPRINTF("%ld", 123456L);
}
END_TEST

START_TEST(test_sprintf_unsigned_integer) {
    CHECK_SPRINTF("%u", 123U);
    CHECK_SPRINTF("%u", 0U);
    CHECK_SPRINTF("%8u", 123U);
    CHECK_SPRINTF("%-8u", 123U);
    CHECK_SPRINTF("%.5u", 123U);
    CHECK_SPRINTF("%hu", (unsigned short)123);
    CHECK_SPRINTF("%lu", 123456UL);
}
END_TEST

START_TEST(test_sprintf_float) {
    CHECK_SPRINTF("%f", 3.14159);
    CHECK_SPRINTF("%.2f", 3.14159);
    CHECK_SPRINTF("%10.2f", 3.14159);
    CHECK_SPRINTF("%-10.2f", 3.14159);
    CHECK_SPRINTF("%+f", 3.14159);
    CHECK_SPRINTF("% f", 3.14159);
    CHECK_SPRINTF("%.0f", 3.6);
    CHECK_SPRINTF("%f", -3.14159);
}
END_TEST

START_TEST(test_sprintf_mixed_format) {
    CHECK_SPRINTF("%s: %d, %.2f, %c, %u",
                  "Values", -42, 3.14159, 'Z', 100U);
    CHECK_SPRINTF("Name=%-8s score=%+5d", "Alex", 42);
}
END_TEST

START_TEST(test_sprintf_zero_and_precision) {
    CHECK_SPRINTF("%d", 0);
    CHECK_SPRINTF("%.0d", 0);
    CHECK_SPRINTF("%.0u", 0U);
    CHECK_SPRINTF("%.3f", 0.0);
    CHECK_SPRINTF("%5.0f", 3.0);
}
END_TEST


int main(void) {
    Suite *suite = suite_create("s21_string");
    TCase *test_case = tcase_create("required_functions");

    tcase_add_test(test_case, test_memchr_basic);
    tcase_add_test(test_case, test_memcmp_basic);
    tcase_add_test(test_case, test_memcpy_basic);
    tcase_add_test(test_case, test_memset_basic);
    tcase_add_test(test_case, test_strncat_basic);
    tcase_add_test(test_case, test_strchr_basic);
    tcase_add_test(test_case, test_strncmp_basic);
    tcase_add_test(test_case, test_strncpy_basic);
    tcase_add_test(test_case, test_strncpy_padding);
    tcase_add_test(test_case, test_strcspn_basic);
    tcase_add_test(test_case, test_strerror_basic);
    tcase_add_test(test_case, test_strerror_edge_cases);
    tcase_add_test(test_case, test_strlen_basic);
    tcase_add_test(test_case, test_strpbrk_basic);
    tcase_add_test(test_case, test_strrchr_basic);
    tcase_add_test(test_case, test_strstr_basic);
    tcase_add_test(test_case, test_strtok_basic);
    tcase_add_test(test_case, test_sprintf_plain_text);
    tcase_add_test(test_case, test_sprintf_percent);
    tcase_add_test(test_case, test_sprintf_char);
    tcase_add_test(test_case, test_sprintf_string);
    tcase_add_test(test_case, test_sprintf_signed_integer);
    tcase_add_test(test_case, test_sprintf_unsigned_integer);
    tcase_add_test(test_case, test_sprintf_float);
    tcase_add_test(test_case, test_sprintf_mixed_format);
    tcase_add_test(test_case, test_sprintf_zero_and_precision);

    suite_add_tcase(suite, test_case);

    SRunner *runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);

    int failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}


