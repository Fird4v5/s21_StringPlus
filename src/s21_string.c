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

  while (i < num && src[i] != '\0') { 
    dest[i] = src[i]; 
    i++;
  }


  while (i < num) {
    dest[i] = '\0'; 
    i++; 
  }

  return dest; 

}

// ===== 7. STRNCAT =====

char *s21_strncat(char *dest, const char *src , s21_size num) {

  s21_size i = 0; 

  while (dest[i] != '\0') {
    i++; 
  }

  s21_size j = 0; 

  while (j < num && src[j] != '\0') {
    dest[i] = src[j]; 
    i++; 
    j++; 
  }

  dest[i] = '\0'; 

  return dest; 

}

// ===== 8. STRSTR =====

char *s21_strstr(const char *haystack, const char *needle) {

  if (*needle == '\0') {
    return (char *)haystack; 
  }

  s21_size i = 0; 
  while (haystack[i] != '\0') {

    s21_size j = 0; 
    while (needle[j] != '\0' && haystack[i + j] == needle[j]) {
      j++; 
    }
    
    if (needle[j] == '\0') {
      return (char *)&haystack[i]; 
    }
    
    i++;
  }

  return S21_NULL; 

}

// ===== 9. STRTOK ===== 

char *s21_strtok(char *str, const char *delim) {

  static char *next_position = S21_NULL; 

  if (str != S21_NULL) {
    next_position = str; 
  } else if (next_position == S21_NULL) {
    return S21_NULL; 
  }

  while (*next_position != '\0' && s21_strchr(delim, *next_position) != S21_NULL) {
    next_position++; 
  }

  if (*next_position == '\0') {
    next_position = S21_NULL; 
    return S21_NULL; 
  }

  char *token = next_position; 

  while (*next_position != '\0' && s21_strchr(delim, *next_position) == S21_NULL) {
    next_position++; 
  }

  if (*next_position == '\0') {
    next_position = S21_NULL; 
  } else {
    *next_position = '\0'; 
    next_position++; 
  }

  return token; 

}