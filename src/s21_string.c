// s21_string.c

#include <stdio.h>

#include "s21_string.h"


// ===== 1. STRLEN ===== 

s21_size s21_strlen(const char *str) {

  s21_size i = 0; 

  while (str[i] != '\0') {
    i++; 
  }

  return i; 

}

// ===== 2. STRCHR ===== 

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

// ===== 3. STRRCHR =====

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


// ===== 4. STRCMP =====

int s21_strcmp(const char *str1, const char *str2) {

  const unsigned char *ustr1 = (const unsigned char *)str1; 
  const unsigned char *ustr2 = (const unsigned char *)str2; 


  s21_size i = 0; 

  while (ustr1[i] != '\0' || ustr2[i] != '\0') {

    if (ustr1[i] != ustr2[i]) {
      return ustr1[i] - ustr2[i]; 
    }

    i++; 
  }

  return 0;  

}


// ===== 5. STRNCMP =====

int s21_strncmp(const char *str1, const char *str2, s21_size num) {

  const unsigned char *ustr1 = (const unsigned char *)str1; 
  const unsigned char *ustr2 = (const unsigned char *)str2; 

  s21_size i = 0;

  while (i < num) {

    if (ustr1[i] == '\0' || ustr2[i] == '\0') {
      return ustr1[i] - ustr2[i]; 
    }
    
    if (ustr1[i] != ustr2[i]) {
      return ustr1[i] - ustr2[i]; 
    }

    i++; 

  }

  return 0; 

}


// ===== 6. STRNCPY ===== 

char *s21_strncpy(char *dest, const char *src, s21_size num) {
  
  s21_size i = 0;

  while (i < num) {

      if (src[i] != '\0') {
        dest[i] = src[i]; 
      }

    i++;

  }

  if (src[i] == '\0') {
    while (i < num) {
      dest[i] = '\0'; 
      i++; 
    }
  }

  return dest; 

}

