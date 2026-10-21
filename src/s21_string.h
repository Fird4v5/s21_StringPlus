#ifndef S21_STRING_H
#define S21_STRING_H

#include <stddef.h>
#include <string.h>
#include <stdarg.h>

typedef size_t s21_size; 
#define S21_NULL ((void *)0)

s21_size s21_strlen(const char *str); 
char *s21_strchr(const char *str, int value);
char *s21_strrchr(const char *str, int value); 
void *s21_memset(void *Dst, int val, s21_size num); 
void *s21_memchr(const void *Buff, int Val, s21_size num);
int s21_memcmp(const void *Buff1, const void *Buff2, s21_size num); 
void *s21_memcpy(void *Dst, const void *Src, s21_size num);
char *s21_strncpy(char *dst, const char *src, s21_size num);
char *s21_strncat(char *dst, const char *src, s21_size num); 
int s21_strncmp(const char *str1, const char *str2, s21_size num); 
s21_size s21_strcspn(const char *str, const char *set);
char *s21_strpbrk(const char *str, const char *set);  
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delimiter);
char *s21_strerror(int errnum); 
int s21_sprintf(char *str, const char *format, ...); 


#endif