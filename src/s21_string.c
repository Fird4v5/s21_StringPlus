#include <stdio.h>
#include "s21_string.h"

s21_size s21_strlen(const char *str) {

    s21_size count = 0;

    while (*str != '\0') {
        count++; 
        str++; 
    }

    return count; 
}

char *s21_strchr(const char *str, int value) {

    while (*str != '\0') {

        if (*str == (unsigned char)value) {
            return (char *)str; 
        }

        str++; 
    }

    if (value == '\0') {
        return (char *)str; 
    }

    return S21_NULL; 
}

char *s21_strrchr(const char *str, int value) {

    char *last_char = S21_NULL; 

    while (*str != '\0') {

        if (*str == (unsigned char)value) {
            last_char = (char *)str; 
        }

        str++; 
    }

    if (value == '\0') {
        return (char *)str; 
    }

    return last_char; 
}

