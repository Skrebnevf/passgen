#include "password.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void generate_password(char *buf, long size) {
  assert(buf != NULL);
  const char charset[] =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+[]{}|;:,.<>?/~";
  size_t charset_size = sizeof(charset) - 1;

  for (long n = 0; n < size; n++) {
    buf[n] = charset[arc4random_uniform((uint32_t)charset_size)];
  }

  buf[size] = '\0';
}

void print_password(const char *buf) {
  printf("%s\n", buf);
}

int validate_length(long num) {
  if (num < MIN_PASSWORD_LENGTH || num > MAX_PASSWORD_LENGTH) {
    return STATUS_PASSWORD_LENGTH_ERROR;
  }

  return STATUS_OK;
}
