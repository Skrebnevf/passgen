#include <check.h>
#include <string.h>
#include "../src/password.h"

START_TEST(test_generate_length) {
  char buf[101];
  for (int i = 0; i <= 100; i++) {
    memset(buf, 0, sizeof(buf));
    generate_password(buf, i);
    ck_assert_int_eq(strlen(buf), i);
  }
}
END_TEST

START_TEST(test_generate_full_length) {
  char buf[1001];
  generate_password(buf, 100);
  ck_assert_int_eq(strlen(buf), 100);
}
END_TEST

START_TEST(test_validate_bounds) {
  ck_assert_int_ne(validate_length(3), 0);
  ck_assert_int_eq(validate_length(4), 0);
  ck_assert_int_eq(validate_length(100), 0);
  ck_assert_int_ne(validate_length(101), 0);
}
END_TEST

static Suite *password_suite(void) {
  Suite *s  = suite_create("Password");
  TCase *tc = tcase_create("Core");
  tcase_add_test(tc, test_generate_length);
  tcase_add_test(tc, test_generate_full_length);
  tcase_add_test(tc, test_validate_bounds);
  suite_add_tcase(s, tc);
  return s;
}

int main(void) {
  SRunner *sr = srunner_create(password_suite());
  srunner_run_all(sr, CK_NORMAL);
  int failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return failed;
}
