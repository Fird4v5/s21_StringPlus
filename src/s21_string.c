// s21_string.c

#include <stdio.h>

#include "s21_string.h"


// ===== STRLEN ===== 

s21_size s21_strlen(const char *str) {

  s21_size i = 0; 

  while (str[i] != '\0') {
    i++; 
  }

  return i; 

}

// ===== STRCHR ===== 

char *s21_strchr(const char *str, int c) {

  const unsigned char *ustr = (const unsigned char *)str; 
  unsigned char uc = c; 

  while (*ustr != '\0') {
    if (*ustr == uc) {
      return (char *)ustr; 
    }

    ustr++; 
  }

  if (uc == '\0') {
    return (char *)ustr; 
  }

  return S21_NULL; 


}

// ===== STRRCHR =====

char *s21_strrchr(const char *str, int c) {

  const unsigned char *ustr = (const unsigned char *)str; 
  unsigned char uc = c; 

  char *found = S21_NULL; 

  while (*ustr != '\0') {
    if (*ustr == uc) {
      found = (char *)ustr; 
    }
    ustr++; 
  }

  if (uc == '\0') {
    found = (char *)ustr; 
  }

  return found; 

}