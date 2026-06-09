#ifndef PASSWORD_H
#define PASSWORD_H
#include "status.h"

#define MIN_PASSWORD_LENGTH 4
#define MAX_PASSWORD_LENGTH 100

void generate_password(char *buf, long size);

int validate_length(long val);

void print_password(const char *buf);

#endif
