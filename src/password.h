#ifndef PASSWORD_H
#define PASSWORD_H
#include <stddef.h>
#include "status.h"

#define MIN_PASSWORD_LENGTH 4
#define MAX_PASSWORD_LENGTH 100

int generate_password(char *buf, size_t size);

int validate_length(int val);

void print_password(const char *buf);

#endif
