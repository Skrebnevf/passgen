#include <check.h>
#include "../src/helpers.h"

START_TEST(test_copy_to_clipboard) {
  ck_assert_int_eq(copy_to_clipboard(DISPLAY_WAYLAND, "test"), 0);
}
END_TEST

static Suite *helpers_suite(void) {
  Suite *s  = suite_create("Helpers");
  TCase *tc = tcase_create("Core");
  tcase_add_test(tc, test_copy_to_clipboard);
  suite_add_tcase(s, tc);
  return s;
}

int main(void) {
  SRunner *sr = srunner_create(helpers_suite());
  srunner_run_all(sr, CK_NORMAL);
  int failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return failed;
}
