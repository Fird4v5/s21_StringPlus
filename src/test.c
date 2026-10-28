// test.c 

#include <check.h>
#include <string.h>

#include "s21_string.h"


// ===== TEST FUNCTIONS =====

// -----> strlen 

START_TEST(test_strlen_basic){
    ck_assert_uint_eq(s21_strlen("Hello"), strlen("Hello")); 
}
END_TEST

START_TEST(test_strlen_empty) {
    ck_assert_uint_eq(s21_strlen(""), strlen("")); 
}
END_TEST

START_TEST(test_strlen_embedded_null) {
    ck_assert_uint_eq(s21_strlen("abc\0lol"), strlen("abc\0lol")); 
}
END_TEST

START_TEST(test_strlen_spaces) {
    ck_assert_uint_eq(s21_strlen("   "), strlen("   ")); 
    ck_assert_uint_eq(s21_strlen("Hello World"), strlen("Hello World")); 
    ck_assert_uint_eq(s21_strlen(" Hello "), strlen(" Hello ")); 
}
END_TEST

// -----> strchr 

static const char *strchr_str = "Hello"; 

START_TEST(test_strchr_basic) {
    ck_assert_ptr_eq(s21_strchr(strchr_str, 'l'), strchr(strchr_str, 'l')); 
}
END_TEST 

START_TEST(test_strchr_c_not_found) {
    ck_assert_ptr_null(s21_strchr(strchr_str, 'z')); 
}
END_TEST

START_TEST(test_strchr_null_terminator) {
    ck_assert_ptr_eq(s21_strchr(strchr_str, '\0'), strchr(strchr_str, '\0')); 
}
END_TEST

START_TEST(test_strchr_unsigned_char) {
    char str[] = {(char)0xFF, '\0'}; 
    ck_assert_ptr_eq(s21_strchr(str, 255), strchr(str, 255)); 
}
END_TEST

// -----> strrchr

START_TEST(test_strrchr_basic) {
    ck_assert_ptr_eq(s21_strrchr(strchr_str, 'l'), strrchr(strchr_str, 'l')); 
}
END_TEST

START_TEST(test_strrchr_c_not_found) {
    ck_assert_ptr_null(s21_strrchr(strchr_str, 'z')); 
}
END_TEST

START_TEST(test_strrchr_null_terminator) {
    ck_assert_ptr_eq(s21_strrchr(strchr_str, '\0'), strrchr(strchr_str, '\0')); 
}
END_TEST

START_TEST(test_strrchr_c_found_once) {
    ck_assert_ptr_eq(s21_strchr(strchr_str, 'e'), strrchr(strchr_str, 'e')); 
}
END_TEST

START_TEST(test_strrchr_unsigned_char) {
    char str[] = {(char)0xFF, '\0'}; 
    ck_assert_ptr_eq(s21_strrchr(str, 255), strrchr(str, 255)); 
}
END_TEST



// ===== SUITE / TCASE ===== 

Suite *s21_string_suite(void) {

    Suite *suite = suite_create("s21_string"); 

    TCase *tc_strlen = tcase_create("strlen_tests"); 
    TCase *tc_strchr = tcase_create("strchr_tests"); 
    TCase *tc_strrchr = tcase_create("strrchr_tests"); 

    tcase_add_test(tc_strlen, test_strlen_basic); 
    tcase_add_test(tc_strlen, test_strlen_empty);
    tcase_add_test(tc_strlen, test_strlen_embedded_null); 
    tcase_add_test(tc_strlen, test_strlen_spaces); 

    tcase_add_test(tc_strchr, test_strchr_basic); 
    tcase_add_test(tc_strchr, test_strchr_c_not_found); 
    tcase_add_test(tc_strchr, test_strchr_null_terminator); 
    tcase_add_test(tc_strchr, test_strchr_unsigned_char); 

    tcase_add_test(tc_strrchr, test_strrchr_basic); 
    tcase_add_test(tc_strrchr, test_strrchr_c_not_found); 
    tcase_add_test(tc_strrchr, test_strrchr_null_terminator); 
    tcase_add_test(tc_strrchr, test_strrchr_c_found_once); 
    tcase_add_test(tc_strrchr, test_strrchr_unsigned_char); 


    suite_add_tcase(suite, tc_strlen); 
    suite_add_tcase(suite, tc_strchr); 
    suite_add_tcase(suite, tc_strrchr); 

    return suite; 
}

// ===== SRUNNER =====

int main(void) {

    SRunner *runner = srunner_create(s21_string_suite()); 

    srunner_run_all(runner, CK_NORMAL); 
    int failed = srunner_ntests_failed(runner); 

    srunner_free(runner); 

    return (failed == 0) ? 0 : 1; 

}