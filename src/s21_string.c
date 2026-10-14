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

// 8. STRNCPY
char *s21_strncpy(char *dst, const char *src, s21_size num) {


    s21_size i = 0; 

    while (i < num && src[i] != '\0') {

        dst[i] = src[i]; 
        i++; 

    }

    while (i < num) {
        dst[i] = '\0'; 
        i++; 
    }

    return dst; 

}

// 9. STRNCAT 
char *s21_strncat(char *dst, const char *src, s21_size num) {

    s21_size i = 0; 
    while (dst[i] != '\0') {
        i++; 
    }

    s21_size a = 0; 
    while (a < num && src[a] != '\0') {
        dst[i] = src[a]; 
        i++; 
        a++; 
    }

    dst[i] = '\0'; 

    return dst; 

}

// 10. STRNCMP
int s21_strncmp(const char *str1, const char *str2, s21_size num) {

    s21_size i = 0; 

    while (i < num) {

        if (str1[i] != str2[i]) {
            return str1[i] - str2[i]; 
        }

        if (str1[i] == '\0') {
            return 0; 
        }

        i++; 
    }

    return 0; 

}



