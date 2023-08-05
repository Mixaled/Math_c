#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "s21_math.h"
#include "test_data.h"

#define eps 0.0000001

#define TEST_C_INCLUDES \
  "#include <check.h> \n \
#include <ctype.h> \n \
#include <limits.h> \n \
#include <math.h> \n \
#include <stdbool.h> \n \
#include <stddef.h> \n \
#include <stdio.h> \n \
#include <stdlib.h> \n \
#include \"s21_math.h\"\n "

void print_value(long double value);
void print_one_arg_function(const char* name, double x);
void print_two_arg_function(const char* name, double x, double y);
void gen_ldouble_test(const char* func_name, const char* s21_func_name,
                      long double arg, int test_id, long double target_val);
void gen_int_test(const char* func_name, const char* s21_func_name, int arg,
                  int test_id);

void gen_ldouble_two_arg_test(const char* func_name, const char* s21_func_name,
                              long double arg_x, long double arg_y, int test_id,
                              long double target_val);

void gen_all_ldouble_one_arg_tests();
void gen_all_ldouble_test_cases(const char* s21_names[], int names_count,
                                int tests_count);
void gen_all_int_tests();
void gen_all_int_test_cases();
void gen_all_ldouble_two_arg_tests();

int main() {
  printf(TEST_C_INCLUDES);

  gen_all_int_tests();
  gen_all_ldouble_one_arg_tests();

  int tests_count[2] = {0};
  gen_all_ldouble_two_arg_tests(tests_count);

  printf("int main() {\n");
  printf("Suite* suite = suite_create(\"S21_MATH_SLEEPYKA_VERDAQUI\");\n");
  printf("SRunner* srunner = srunner_create(suite);\n");

  gen_all_int_test_cases();

  double double_values[] = TEST_DOUBLE_VALUES;
  int double_values_count = sizeof(double_values) / sizeof(double_values[0]);

  const char* one_arg_names[] = TEST_S21_ONE_ARG_FUNCTIONS_NAMES;
  int one_arg_count = sizeof(one_arg_names) / sizeof(one_arg_names[0]);
  gen_all_ldouble_test_cases(one_arg_names, one_arg_count, double_values_count);

  const char* two_arg_names[] = TEST_S21_TWO_ARG_FUNCTIONS_NAMES;
  int two_arg_count = sizeof(two_arg_names) / sizeof(two_arg_names[0]);

  for (int i = 0; i < two_arg_count; i++) {
    gen_all_ldouble_test_cases(&two_arg_names[i], 1, tests_count[i]);
  }

  printf("srunner_run_all(srunner, CK_VERBOSE);\n");
  printf("int number_failed = srunner_ntests_failed(srunner);\n");
  printf("srunner_free(srunner);\n");
  printf("return number_failed == 0 ? 0 : 1;\n");

  printf("}\n");

  return 0;
}

void print_value(long double value) {
  if (isnan(value)) {
    printf("NAN");
  } else if (isinf(value)) {
    if (value > 0)
      printf("INFINITY");
    else
      printf("-INFINITY");
  } else {
    printf("%.16LE", value);
  }
}

void gen_ldouble_test(const char* func_name, const char* s21_func_name,
                      long double arg, int test_id, long double target_val) {
  printf("START_TEST(%s_test_%d) {\n", s21_func_name, test_id);
  if (isnan(target_val)) {
    printf("ck_assert_ldouble_nan(");
    print_one_arg_function(s21_func_name, arg);
    printf(");\n");
  } else if (isinf(target_val)) {
    printf("ck_assert_ldouble_infinite(");
    print_one_arg_function(s21_func_name, arg);
    printf(");\n");
  } else {
    printf("ck_assert_ldouble_eq_tol(");
    print_one_arg_function(s21_func_name, arg);
    printf(", ");
    print_one_arg_function(func_name, arg);
    printf(", ");
    print_value(eps);
    printf(");\n");
  }
  printf("}\n END_TEST\n\n");
}

void gen_ldouble_two_arg_test(const char* func_name, const char* s21_func_name,
                              long double arg_x, long double arg_y, int test_id,
                              long double target_val) {
  printf("START_TEST(%s_test_%d) {\n", s21_func_name, test_id);
  if (isnan(target_val)) {
    printf("ck_assert_ldouble_nan(");
    print_two_arg_function(s21_func_name, arg_x, arg_y);
    printf(");\n");
  } else if (isinf(target_val)) {
    printf("ck_assert_ldouble_infinite(");
    print_two_arg_function(s21_func_name, arg_x, arg_y);
    printf(");\n");
  } else {
    printf("ck_assert_ldouble_eq_tol(");
    print_two_arg_function(s21_func_name, arg_x, arg_y);
    printf(", ");
    print_two_arg_function(func_name, arg_x, arg_y);
    printf(", ");
    print_value(eps);
    printf(");\n");
  }
  printf("}\n END_TEST\n\n");
}

void gen_int_test(const char* func_name, const char* s21_func_name, int arg,
                  int test_id) {
  printf("START_TEST(%s_test_%d) {\n", s21_func_name, test_id);
  printf("ck_assert_int_eq(%s ((int) %d), %s ((int) %d));\n", s21_func_name,
         arg, func_name, arg);
  printf("}\n END_TEST\n\n");
}

void gen_all_ldouble_one_arg_tests() {
  const char* s21_names[] = TEST_S21_ONE_ARG_FUNCTIONS_NAMES;
  const char* math_names[] = TEST_MATH_ONE_ARG_FUNCTION_NAMES;
  double (*math_functions[])(double) = TEST_MATH_ONE_ARG_FUNCTIONS;
  int funcs_count = sizeof(math_functions) / sizeof(math_functions[0]);

  double test_double_values[] = TEST_DOUBLE_VALUES;
  int double_values_count =
      sizeof(test_double_values) / sizeof(test_double_values[0]);

  for (int func_id = 0; func_id < funcs_count; func_id++) {
    for (int test_id = 0; test_id < double_values_count; test_id++) {
      double arg = test_double_values[test_id];
      double value = math_functions[func_id](arg);
      printf("//args[%d]: %.16e\n", test_id, arg);
      gen_ldouble_test(math_names[func_id], s21_names[func_id], arg, test_id,
                       value);
    }
  }
}

void gen_all_ldouble_test_cases(const char* s21_names[], int names_count,
                                int tests_count) {
  for (int func_id = 0; func_id < names_count; func_id++) {
    const char* func_name = s21_names[func_id];
    printf("TCase* test_case_%s = tcase_create(\"%s_test\");\n", func_name,
           func_name);
    printf("suite_add_tcase(suite, test_case_%s);\n", func_name);

    for (int test_id = 0; test_id < tests_count; test_id++) {
      printf("tcase_add_test(test_case_%s, %s_test_%d);\n", func_name,
             func_name, test_id);
    }
  }
}

void gen_all_ldouble_two_arg_tests(int* tests_count) {
  const char* s21_names[] = TEST_S21_TWO_ARG_FUNCTIONS_NAMES;
  const char* math_names[] = TEST_MATH_TWO_ARG_FUNCTION_NAMES;
  double (*math_functions[])(double, double) = TEST_MATH_TWO_ARG_FUNCTIONS;
  int funcs_count = sizeof(math_functions) / sizeof(math_functions[0]);

  double test_double_values[] = TEST_TWO_ARGS_VALUES;
  int double_values_count =
      sizeof(test_double_values) / sizeof(test_double_values[0]);

  for (int func_id = 0; func_id < funcs_count; func_id++) {
    int test_id = 0;

    for (int x_id = 0; x_id < double_values_count; x_id++) {
      for (int y_id = 0; y_id < double_values_count; y_id++) {
        double arg_x = test_double_values[x_id];
        double arg_y = test_double_values[y_id];
        double value = math_functions[func_id](arg_x, arg_y);
        printf("//args[%d] - x: %.16e, args[%d] - y: %.16e\n", x_id, arg_x,
               y_id, arg_y);
        gen_ldouble_two_arg_test(math_names[func_id], s21_names[func_id], arg_x,
                                 arg_y, test_id, value);

        test_id++;
      }
    }

    tests_count[func_id] = test_id;
  }
}

void gen_all_int_tests() {
  const char* s21_name = "s21_abs";
  const char* name = "abs";

  int test_values[] = TEST_INT_VALUES;
  int values_count = sizeof(test_values) / sizeof(test_values[0]);

  for (int test_id = 0; test_id < values_count; test_id++) {
    int arg = test_values[test_id];
    gen_int_test(name, s21_name, arg, test_id);
  }
}

void gen_all_int_test_cases() {
  const char* s21_name = "s21_abs";

  int test_values[] = TEST_INT_VALUES;
  int values_count = sizeof(test_values) / sizeof(test_values[0]);

  printf("TCase* test_case_%s = tcase_create(\"%s_test\");\n", s21_name,
         s21_name);
  printf("suite_add_tcase(suite, test_case_%s);\n", s21_name);
  for (int test_id = 0; test_id < values_count; test_id++) {
    printf("tcase_add_test(test_case_%s, %s_test_%d);\n", s21_name, s21_name,
           test_id);
  }
}

void print_one_arg_function(const char* name, double x) {
  printf("%s (", name);
  print_value(x);
  printf(")");
}

void print_two_arg_function(const char* name, double x, double y) {
  printf("%s (", name);
  print_value(x);
  printf(", ");
  print_value(y);
  printf(")");
}
