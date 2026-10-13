#ifndef S21_STRING_H
#define S21_STRING_H

#include <stddef.h>
#include <string.h>

typedef size_t s21_size; 
#define S21_NULL ((void *)0)

s21_size s21_strlen(const char *str); 
char *s21_strchr(const char *str, int value);
char *s21_strrchr(const char *str, int value); 
void *s21_memset(void *Dst, int val, s21_size num); 
void *s21_memchr(const void *Buff, int Val, s21_size num);
int s21_memcmp(const void *Buff1, const void *Buff2, s21_size num); 
void *s21_memcpy(void *Dst, const void *Src, s21_size num);

#endif