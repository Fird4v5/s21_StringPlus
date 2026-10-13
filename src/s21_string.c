#include <stdio.h>
#include "s21_string.h"

// 1. *****STRLEN*****
s21_size s21_strlen(const char *str) {

    s21_size count = 0;

    while (*str != '\0') {
        count++; 
        str++; 
    }

    return count; 
}

// 2. *****STRCHR*****
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

// 3. *****STRRCHR*****
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

// 4. MEMSET
void *s21_memset(void *Dst, int Val, s21_size num) {

    unsigned char *dst = Dst; 
    unsigned char val = Val; 

    for (s21_size i = 0; i < num; i++) {
        dst[i] = val; 
    }

    return Dst; 
}

// 5. MEMCHR
void *s21_memchr(const void *Buff, int Val, s21_size num) {

    const unsigned char *buff = Buff; 
    unsigned char val = Val; 

    for (s21_size i = 0; i < num; i++) {
        if (buff[i] == val) {
            return (void *)&buff[i]; 
        }
    }

    return S21_NULL; 
}

// 6. MEMCMP 
int s21_memcmp(const void *Buff1, const void *Buff2, s21_size num) {

    const unsigned char *buff1 = Buff1; 
    const unsigned char *buff2 = Buff2; 

    for (s21_size i = 0; i < num; i++) {
        if (buff1[i] != buff2[i]) {
            return buff1[i] - buff2[i]; 
        }
    }

    return 0; 
    
}

// 7. MEMCPY
void *s21_memcpy(void *Dst, const void *Src, s21_size num) {

    unsigned char *dst = Dst; 
    const unsigned char *src = Src; 

    for (s21_size i = 0; i < num; i++) {
        dst[i] = src[i];
    }

    return Dst; 
}




