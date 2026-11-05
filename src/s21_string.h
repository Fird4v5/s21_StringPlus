// s21_string.h 

#ifndef S21_STRING_H 
#define S21_STRING_H

// Header contents 

#include <stddef.h>

typedef size_t s21_size; 
#define S21_NULL ((void*)0)


s21_size s21_strlen(const char *str); 
char *s21_strchr(const char *str, int c); 
char *s21_strrchr(const char *str, int c); 
int s21_strcmp(const char *str1, const char *str2); 
int s21_strncmp(const char *str1, const char *str2, s21_size num); 
char *s21_strncpy(char *dest, const char *src, s21_size num);
char *s21_strncat(char *dest, const char *src , s21_size num); 


#endif