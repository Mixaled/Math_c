#ifndef SRC_TEST_DATA_H_
#define SRC_TEST_DATA_H_

#include <math.h>

#define TEST_S21_ONE_ARG_FUNCTIONS_NAMES                                      \
  {                                                                           \
    "s21_sqrt", "s21_sin", "s21_cos", "s21_tan", "s21_asin", "s21_acos",      \
        "s21_atan", "s21_log", "s21_floor", "s21_ceil", "s21_exp", "s21_fabs" \
  }

#define TEST_MATH_ONE_ARG_FUNCTION_NAMES                                 \
  {                                                                      \
    "sqrt", "sin", "cos", "tan", "asin", "acos", "atan", "log", "floor", \
        "ceil", "exp", "fabs"                                            \
  }

#define TEST_MATH_ONE_ARG_FUNCTIONS \
  { sqrt, sin, cos, tan, asin, acos, atan, log, floor, ceil, exp, fabs }

#define TEST_S21_TWO_ARG_FUNCTIONS_NAMES \
  { "s21_pow", "s21_fmod", }

#define TEST_MATH_TWO_ARG_FUNCTION_NAMES \
  { "pow", "fmod" }

#define TEST_MATH_TWO_ARG_FUNCTIONS \
  { pow, fmod }

#define TEST_DOUBLE_VALUES                                                     \
  {                                                                            \
    0.0, -0.0, 1.0, -1.0, 0.5, -0.5, 1000.0, 2000.0, 42352.0, -35363.0,        \
        0.6666666, -0.3333333, 57434.574554256, 1000.1000, 1000.100011, 0.1,   \
        0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 0.999, -0.1, -0.2, -0.3, -0.4, \
        -0.5, -0.6, -0.7, -0.8, -0.9, -0.999, 0.1111, S21_M_PI / 2.0,          \
        -S21_M_PI / 2.0, 10e-6, 10e-7, 10e-8, 10e-9, S21_NAN, S21_INFINITY,    \
        -S21_INFINITY, S21_DOUBLE_MIN, -S21_DOUBLE_MIN                         \
  }
#define TEST_TWO_ARGS_VALUES                                           \
  {                                                                    \
    -2.0, -1.0, -0.5, -0.0, 0.0, 0.5, 1.0, 2.0, S21_NAN, S21_INFINITY, \
        -S21_INFINITY                                                  \
  }

#define TEST_INT_VALUES \
  { 0, -1, -22, 5, -0, -0101010, 64386876, -1234, INT_MAX, INT_MIN }

#endif
