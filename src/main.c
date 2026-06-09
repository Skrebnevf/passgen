#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "password.h"
#include "helpers.h"
#include "status.h"

const int MAX_OPTIONS = 3;
const int MIN_OPTIONS = 1;

int main(int argc, char **argv) {
  if (argc == MIN_OPTIONS || argc > MAX_OPTIONS) {
    fprintf(stderr, "Usage: -g <len>, -h for help\n");
    exit(STATUS_USAGE_ERROR);
  }

  DisplayServer display_server = detect_display_server();

  int opt;
  while ((opt = getopt(argc, argv, "hg:")) != -1) {
    switch (opt) {
      case 'g': {
        char *endptr;
        errno = 0;

        long arg = strtol(optarg, &endptr, 10);

        if (errno == ERANGE) {
          if (arg == LONG_MAX) {
            fprintf(stderr, "Password length exceeds the maximum of %d\n", MAX_PASSWORD_LENGTH);
            exit(STATUS_PASSWORD_LENGTH_ERROR);
          }
          if (arg == LONG_MIN) {
            fprintf(stderr, "Password length is below the minimum of %d\n", MIN_PASSWORD_LENGTH);
            exit(STATUS_PASSWORD_LENGTH_ERROR);
          }
        }

        if (*endptr != '\0') {
          fprintf(stderr, "Trailing characters after the number\n");
          exit(STATUS_NOT_A_NUMBER);
        }

        if (optarg == endptr) {
          fprintf(stderr, "Not a valid number\n");
          exit(STATUS_NOT_A_NUMBER);
        }

        if (validate_length(arg) != STATUS_OK) {
          fprintf(stderr, "Length must be between %d and %d\n", MIN_PASSWORD_LENGTH,
                  MAX_PASSWORD_LENGTH);
          exit(STATUS_PASSWORD_LENGTH_ERROR);
        }

        char *password = malloc(arg + 1);
        if (!password) {
          perror("malloc");
          exit(STATUS_ALLOCATION_ERROR);
        }

        if (generate_password(password, arg) != STATUS_OK) {
          explicit_bzero(password, arg + 1);
          free(password);
          exit(STATUS_GENERATE_PASSWORD_ERROR);
        }

        print_password(password);
        if (copy_to_clipboard(display_server, password) != STATUS_OK) {
          fprintf(stderr, "warning: could not copy password to clipboard\n");
        }

        explicit_bzero(password, arg + 1);
        free(password);

        return STATUS_OK;
      }
      case 'h':
        printf("Use -g <len> for password generation\n");
        return STATUS_OK;
      case '?':
        if (optopt == 'g') {
          fprintf(stderr, "-g requires a number argument\n");
        } else if (optopt != 0) {
          fprintf(stderr, "Unknown option: -%c\n", optopt);
        } else {
          fprintf(stderr, "Unknown option\n");
        }
        exit(STATUS_UNKNOWN_OPTIONS);
    }
  }
  if (optind < argc) {
    fprintf(stderr, "Unknown argument: %s. Use -g <len> or -h\n", argv[optind]);
    exit(STATUS_UNKNOWN_OPTIONS);
  }
  return STATUS_OK;
}
