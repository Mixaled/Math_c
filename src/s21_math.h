#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#include <stddef.h>
#include <stdio.h>

#define S21_M_PI 3.14159265358979323846264338327950288
#define S21_PI_2 3.14159265358979323846264338327950288 / 2.0
#define S21_INFINITY __builtin_huge_valf()
#define S21_NAN __builtin_nanf("0x7fc00000")
#define S21_DOUBLE_MIN 2.22507e-308L
#define S21_DOUBLE_MAX 1.79769e+308L
#define S21_EPS 1e-10
#define S21_EXP 2.7182818284590452353602874713527
#define S21_LN_TEN 2.3025850929940459010936137929093092679977
#define S21_LN_TWO 0.693147180559945309417232121458176568075500
#define S21_SQRT_2 1.414213562373095048801688724209698078569671

int s21_abs(int x);              // +
long double s21_sqrt(double x);  // +

long double s21_sin(double x);  //+
long double s21_cos(double x);  //+
long double s21_tan(double x);  //+

long double s21_asin(double x);
long double s21_acos(double x);
long double s21_atan(double x);

long double s21_log(double x);                      // +
long double s21_floor(double x);                    // +
long double s21_ceil(double x);                     // +
long double s21_exp(double x);                      // +
long double s21_pow(double base, double exponent);  // +
long double s21_fmod(double x, double y);           // +
long double s21_fabs(double x);                     // +

#endif
