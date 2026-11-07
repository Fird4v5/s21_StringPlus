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


// -----> STRCMP 

START_TEST(test_strcmp_equal) {
    ck_assert_int_eq(s21_strcmp("Hello", "Hello"), strcmp("Hello", "Hello")); 
}
END_TEST

START_TEST(test_strcmp_different) {
    ck_assert_int_lt(s21_strcmp("apple", "apply"), 0); 
    ck_assert_int_lt(strcmp("apple", "apply"), 0); 
}
END_TEST

START_TEST(test_strcmp_reverse) {
    ck_assert_int_gt(s21_strcmp("zebra", "apple"), 0); 
    ck_assert_int_gt(strcmp("zebra", "apple"), 0); 
}
END_TEST

START_TEST(test_strcmp_first_shorter) {
    ck_assert_int_lt(s21_strcmp("cat", "caterpillar"), 0); 
    ck_assert_int_lt(strcmp("cat", "caterpillar"), 0); 
}
END_TEST

START_TEST(test_strcmp_second_shorter) {
    ck_assert_int_gt(s21_strcmp("caterpillar", "cat"), 0);
    ck_assert_int_gt(strcmp("caterpillar", "cat"), 0);  
}
END_TEST

START_TEST(test_strcmp_empty) {
    ck_assert_int_eq(s21_strcmp("", ""), strcmp("", "")); 
}
END_TEST

START_TEST(test_strcmp_one_empty) {
    ck_assert_int_lt(s21_strcmp("", "Hello"), 0);
    ck_assert_int_lt(strcmp("", "Hello"), 0); 
}
END_TEST

START_TEST(test_strcmp_unsigned_char) {
    char str[] = {(char)0xFF, '\0'}; 

    ck_assert_int_gt(s21_strcmp(str, "A"), 0); 
    ck_assert_int_gt(strcmp(str, "A"), 0); 
}
END_TEST


// -----> strncmp 

START_TEST(test_strncmp_equal) {
    ck_assert_int_eq(s21_strncmp("Hello", "Hello", 5), strncmp("Hello", "Hello", 5)); 
}
END_TEST 

START_TEST(test_strncmp_different) {
    ck_assert_int_lt(s21_strncmp("apple", "apply", 5), 0);
    ck_assert_int_lt(strncmp("apple", "apply", 5), 0); 
}
END_TEST

START_TEST(test_strncmp_num_shorter) {
    ck_assert_int_eq(s21_strncmp("apple", "apply", 4), strncmp("apple", "apply", 4));
}
END_TEST

START_TEST(test_strncmp_first_shorter) {
    ck_assert_int_lt(s21_strncmp("cat", "caterpillar", 10), 0);
    ck_assert_int_lt(strncmp("cat", "caterpillar", 10), 0);  
}
END_TEST

START_TEST(test_strncmp_second_shorter) {
    ck_assert_int_gt(s21_strncmp("caterpillar", "cat", 10), 0); 
    ck_assert_int_gt(strncmp("caterpillar", "cat", 10), 0); 
}
END_TEST

START_TEST(test_strncmp_num_zero) {
    ck_assert_int_eq(s21_strncmp("apple", "apply", 0), strncmp("apple", "apply", 0)); 
}
END_TEST


START_TEST(test_strncmp_empty) {
    ck_assert_int_eq(s21_strncmp("", "", 5), strncmp("", "", 5));
}
END_TEST

START_TEST(test_strncmp_unsigned_char) {
    char str[] = {(char)0xFF, '\0'};
    ck_assert_int_gt(s21_strncmp(str, "A", 1), 0);
    ck_assert_int_gt(strncmp(str, "A", 1), 0); 
}
END_TEST


// -----> strncpy 

START_TEST(test_strncpy_equal_size) {

    char actual[10] = {0}; 
    char expected[10] = {0}; 

    s21_strncpy(actual, "Hello", 5); 
    memcpy(expected, "Hello", 5); 

    ck_assert_mem_eq(actual, expected, 10); 

}
END_TEST

START_TEST(test_strncpy_limited) {

    char actual[10] = {0}; 
    char expected[10] = {0}; 

    s21_strncpy(actual, "Hello", 3); 
    memcpy(expected, "Hello", 3); 

    ck_assert_mem_eq(actual, expected, 3);

}
END_TEST

START_TEST(test_strncpy_src_shorter) {

    char actual[10] = {0}; 
    char expected[10] = {0}; 

    s21_strncpy(actual, "Hi", 5); 
    strncpy(expected, "Hi", 5); 

    ck_assert_mem_eq(actual, expected, 5); 

}
END_TEST 


START_TEST(test_strncpy_zero_limit) {
    
    char actual[10] = "Original"; 
    char expected[10] = "Original"; 

    s21_strncpy(actual, "Hello", 0); 

    ck_assert_mem_eq(actual, expected, 10); 

}
END_TEST


START_TEST(test_strncpy_src_empty) {

    char actual[10] = {0}; 
    char expected[10] = {0}; 

    s21_strncpy(actual, "", 5); 
    strncpy(expected, "", 5); 

    ck_assert_mem_eq(actual, expected, 5); 

}
END_TEST

START_TEST(test_strncpy_no_extra_null) {

    char actual[10]; 
    char expected[10]; 

    memset(actual, 'X', 10); 
    memset(expected, 'X', 10); 

    s21_strncpy(actual, "Hello", 5); 
    memcpy(expected, "Hello", 5); 

    ck_assert_mem_eq(actual, expected, 10); 

}
END_TEST

// -----> strncat 

START_TEST(test_strncat_basic) {

    char actual[20] = "Hello"; 

    ck_assert_str_eq(s21_strncat(actual, " World", 6), "Hello World"); 

}
END_TEST

START_TEST(test_strncat_limited) {

    char actual[20] = "Hello"; 
    char expected[20] = "Hello";  

    ck_assert_str_eq(s21_strncat(actual, "World", 3), strncat(expected, "World", 3)); 

}
END_TEST 

START_TEST(test_strncat_src_shorter) {

    char actual[20] = "Hello"; 
    char expected[20] = "Hello";  

    ck_assert_str_eq(s21_strncat(actual, "Hi", 10), strncat(expected, "Hi", 10)); 

}
END_TEST

START_TEST(test_strncat_zero_limit) {

    char actual[20] = "Hello"; 
    char expected[20] = "Hello";  

    ck_assert_str_eq(s21_strncat(actual, "World", 0), strncat(expected, "World", 0)); 

}
END_TEST


START_TEST(test_strncat_src_empty) {

    char actual[20] = "Hello"; 
    char expected[20] = "Hello";
    
    ck_assert_str_eq(s21_strncat(actual, "", 5), strncat(expected, "", 5)); 

}
END_TEST

START_TEST(test_strncat_dest_empty) {

    char actual[20] = ""; 

    ck_assert_str_eq(s21_strncat(actual, "Hello", 5), "Hello"); 

}
END_TEST

// -----> strstr 

START_TEST(test_strstr_basic) {
    ck_assert_ptr_eq(s21_strstr("Hello World", "World"), strstr("Hello World", "World")); 
}
END_TEST

START_TEST(test_strstr_no_match) {
    ck_assert_ptr_null(s21_strstr("Hello World", "Java")); 
}
END_TEST

START_TEST(test_strstr_empty_needle) {
    ck_assert_ptr_eq(s21_strstr("Hello", ""), strstr("Hello", "")); 
}
END_TEST

START_TEST(test_strstr_empty_haystack) {
    ck_assert_ptr_null(s21_strstr("", "Hello")); 
}
END_TEST

START_TEST(test_strstr_index_start) {
    ck_assert_ptr_eq(s21_strstr("Hello World", "Hello"), strstr("Hello World", "Hello")); 
}
END_TEST

START_TEST(test_strstr_multiple_matches) {
    ck_assert_ptr_eq(s21_strstr("banana", "ana"), strstr("banana", "ana")); 
}
END_TEST

// -----> strtok

START_TEST(test_strtok_basic) {

    char actual[] = "apple,banana,grape"; 
    char expected[] = "apple,banana,grape"; 

    char *actual_token = s21_strtok(actual, ","); 
    char *expected_token = strtok(expected, ","); 

    ck_assert_str_eq(actual_token, expected_token); 

    actual_token = s21_strtok(S21_NULL, ","); 
    expected_token = strtok(S21_NULL, ","); 

    ck_assert_str_eq(actual_token, expected_token); 

    actual_token = s21_strtok(S21_NULL, ","); 
    expected_token = strtok(S21_NULL, ","); 

    ck_assert_str_eq(actual_token, expected_token); 

    actual_token = s21_strtok(S21_NULL, ","); 
    expected_token = strtok(S21_NULL, ","); 

    ck_assert_ptr_null(actual_token); 
    ck_assert_ptr_null(expected_token); 

}
END_TEST

START_TEST(test_strtok_multiple_delim) {

    char actual[] = "apple,banana:grape"; 
    char expected[] = "apple,banana:grape"; 

    char *actual_token = s21_strtok(actual, ",:"); 
    char *expected_token = strtok(expected, ",:"); 

    ck_assert_str_eq(actual_token, expected_token); 

    actual_token = s21_strtok(S21_NULL, ",:"); 
    expected_token = strtok(S21_NULL, ",:"); 

    ck_assert_str_eq(actual_token, expected_token); 

    actual_token = s21_strtok(S21_NULL, ",:"); 
    expected_token = strtok(S21_NULL, ",:"); 

    ck_assert_str_eq(actual_token, expected_token); 

    actual_token = s21_strtok(S21_NULL, ",:"); 
    expected_token = strtok(S21_NULL, ",:"); 

    ck_assert_ptr_null(actual_token); 
    ck_assert_ptr_null(expected_token); 

}
END_TEST

START_TEST(test_strtok_consecutive_delim) {

    char actual[] = ",:,:,apple,banana:grape"; 
    char expected[] = ",:,:,apple,banana:grape"; 

    char *actual_token = s21_strtok(actual, ",:"); 
    char *expected_token = strtok(expected, ",:"); 

    ck_assert_str_eq(actual_token, expected_token); 

    actual_token = s21_strtok(S21_NULL, ",:"); 
    expected_token = strtok(S21_NULL, ",:"); 

    ck_assert_str_eq(actual_token, expected_token); 

    actual_token = s21_strtok(S21_NULL, ",:"); 
    expected_token = strtok(S21_NULL, ",:"); 

    ck_assert_str_eq(actual_token, expected_token); 

    actual_token = s21_strtok(S21_NULL, ",:"); 
    expected_token = strtok(S21_NULL, ",:"); 

    ck_assert_ptr_null(actual_token); 
    ck_assert_ptr_null(expected_token); 

}
END_TEST

START_TEST(test_strtok_lead_trail_delim) {

    char actual[] = ",:,:,apple,banana:grape:,:,:"; 
    char expected[] = ",:,:,apple,banana:grape:,:,:"; 

    char *actual_token = s21_strtok(actual, ",:"); 
    char *expected_token = strtok(expected, ",:"); 

    ck_assert_str_eq(actual_token, expected_token); 

    actual_token = s21_strtok(S21_NULL, ",:"); 
    expected_token = strtok(S21_NULL, ",:"); 

    ck_assert_str_eq(actual_token, expected_token); 

    actual_token = s21_strtok(S21_NULL, ",:"); 
    expected_token = strtok(S21_NULL, ",:"); 

    ck_assert_str_eq(actual_token, expected_token); 

    actual_token = s21_strtok(S21_NULL, ",:"); 
    expected_token = strtok(S21_NULL, ",:"); 

    ck_assert_ptr_null(actual_token); 
    ck_assert_ptr_null(expected_token); 

}
END_TEST

START_TEST(test_strtok_str_empty) {

    char actual[] = ""; 
    char expected[] = ""; 

    char *actual_token = s21_strtok(actual, ",:"); 
    char *expected_token = strtok(expected, ",:"); 

    ck_assert_ptr_null(actual_token); 
    ck_assert_ptr_null(expected_token); 

}
END_TEST

START_TEST(test_strtok_delim_empty) {

    char actual[] = ",:,:,apple,banana:grape"; 
    char expected[] = ",:,:,apple,banana:grape"; 

    char *actual_token = s21_strtok(actual, ""); 
    char *expected_token = strtok(expected, ""); 

    ck_assert_str_eq(actual_token, expected_token); 

    actual_token = s21_strtok(S21_NULL, "");
    expected_token = strtok(S21_NULL, "");

    ck_assert_ptr_null(actual_token);
    ck_assert_ptr_null(expected_token);

}
END_TEST

START_TEST(test_strtok_only_delims) {

    char actual[] = ",:,:,:";
    char expected[] = ",:,:,:";

    char *actual_token = s21_strtok(actual, ",:");
    char *expected_token = strtok(expected, ",:");

    ck_assert_ptr_null(actual_token);
    ck_assert_ptr_null(expected_token);

}
END_TEST

START_TEST(test_strtok_restart) {

    char actual1[] = "apple,banana";
    char expected1[] = "apple,banana";

    char actual2[] = "red,blue";
    char expected2[] = "red,blue";

    char *actual_token = s21_strtok(actual1, ",");
    char *expected_token = strtok(expected1, ",");

    ck_assert_str_eq(actual_token, expected_token);

    actual_token = s21_strtok(actual2, ",");
    expected_token = strtok(expected2, ",");

    ck_assert_str_eq(actual_token, expected_token);

}
END_TEST



// ===== SUITE / TCASE ===== 

Suite *s21_string_suite(void) {

    Suite *suite = suite_create("s21_string"); 

    TCase *tc_strlen = tcase_create("strlen_tests"); 
    TCase *tc_strchr = tcase_create("strchr_tests"); 
    TCase *tc_strrchr = tcase_create("strrchr_tests"); 
    TCase *tc_strcmp = tcase_create("strcmp_tests"); 
    TCase *tc_strncmp = tcase_create("strncmp_tests"); 
    TCase *tc_strncpy = tcase_create("strncpy_tests"); 
    TCase *tc_strncat = tcase_create("strncat_tests"); 
    TCase *tc_strstr = tcase_create("strstr_tests"); 
    TCase *tc_strtok = tcase_create("strtok_tests"); 


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

    tcase_add_test(tc_strcmp, test_strcmp_equal); 
    tcase_add_test(tc_strcmp, test_strcmp_different); 
    tcase_add_test(tc_strcmp, test_strcmp_reverse); 
    tcase_add_test(tc_strcmp, test_strcmp_first_shorter); 
    tcase_add_test(tc_strcmp, test_strcmp_second_shorter); 
    tcase_add_test(tc_strcmp, test_strcmp_empty); 
    tcase_add_test(tc_strcmp, test_strcmp_one_empty); 
    tcase_add_test(tc_strcmp, test_strcmp_unsigned_char); 

    tcase_add_test(tc_strncmp, test_strncmp_equal); 
    tcase_add_test(tc_strncmp, test_strncmp_different); 
    tcase_add_test(tc_strncmp, test_strncmp_num_shorter); 
    tcase_add_test(tc_strncmp, test_strncmp_first_shorter); 
    tcase_add_test(tc_strncmp, test_strncmp_second_shorter); 
    tcase_add_test(tc_strncmp, test_strncmp_num_zero);
    tcase_add_test(tc_strncmp, test_strncmp_empty); 
    tcase_add_test(tc_strncmp, test_strncmp_unsigned_char);

    tcase_add_test(tc_strncpy, test_strncpy_equal_size); 
    tcase_add_test(tc_strncpy, test_strncpy_limited);
    tcase_add_test(tc_strncpy, test_strncpy_src_shorter);
    tcase_add_test(tc_strncpy, test_strncpy_zero_limit); 
    tcase_add_test(tc_strncpy, test_strncpy_src_empty);
    tcase_add_test(tc_strncpy, test_strncpy_no_extra_null);

    tcase_add_test(tc_strncat, test_strncat_basic); 
    tcase_add_test(tc_strncat, test_strncat_limited); 
    tcase_add_test(tc_strncat, test_strncat_src_shorter); 
    tcase_add_test(tc_strncat, test_strncat_zero_limit); 
    tcase_add_test(tc_strncat, test_strncat_src_empty); 
    tcase_add_test(tc_strncat, test_strncat_dest_empty); 

    tcase_add_test(tc_strstr, test_strstr_basic); 
    tcase_add_test(tc_strstr, test_strstr_no_match); 
    tcase_add_test(tc_strstr, test_strstr_empty_needle); 
    tcase_add_test(tc_strstr, test_strstr_empty_haystack); 
    tcase_add_test(tc_strstr, test_strstr_index_start); 
    tcase_add_test(tc_strstr, test_strstr_multiple_matches);

    tcase_add_test(tc_strtok, test_strtok_basic); 
    tcase_add_test(tc_strtok, test_strtok_multiple_delim); 
    tcase_add_test(tc_strtok, test_strtok_consecutive_delim); 
    tcase_add_test(tc_strtok, test_strtok_lead_trail_delim); 
    tcase_add_test(tc_strtok, test_strtok_str_empty);
    tcase_add_test(tc_strtok, test_strtok_delim_empty);  
    tcase_add_test(tc_strtok, test_strtok_only_delims); 
    tcase_add_test(tc_strtok, test_strtok_restart); 

    suite_add_tcase(suite, tc_strlen); 
    suite_add_tcase(suite, tc_strchr); 
    suite_add_tcase(suite, tc_strrchr);
    suite_add_tcase(suite, tc_strcmp); 
    suite_add_tcase(suite, tc_strncmp);  
    suite_add_tcase(suite, tc_strncpy); 
    suite_add_tcase(suite, tc_strncat); 
    suite_add_tcase(suite, tc_strstr);
    suite_add_tcase(suite, tc_strtok);  

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