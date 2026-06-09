#include "password.h"
#include <stdio.h>
#include <stdlib.h>

int generate_password(char *buf, size_t size) {
  const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+[]{}|;:,.<>?/~";
  size_t charset_size = sizeof(charset) - 1;
  
  for (size_t n = 0; n < size; n++) {
      buf[n] = charset[arc4random_uniform(charset_size)]; 
  }

  buf[size] = '\0';
  return STATUS_OK;
}

void print_password(const char *buf) {
  printf("%s\n", buf);
}

int validate_length(int num) {
  if (num < MIN_PASSWORD_LENGTH || num > MAX_PASSWORD_LENGTH) {
    return STATUS_PASSWORD_LENGTH_ERROR;
  }
  
  return STATUS_OK;
}
