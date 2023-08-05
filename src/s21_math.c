#include "s21_math.h"

#include <limits.h>
#include <stdint.h>

#define CHECK_PRESICION 0.00000001

// DONE
int s21_abs(int x) { return (x < 0) ? -x : x; }

// DONE
long double s21_fabs(double x) { return (x < 0.0) ? -x : x; }

// DONE
long double s21_sqrt(double x) {
  long double startX = 0.0L;

  startX = x / 2.;
  if (startX < 0) {
    startX = S21_NAN;
  } else if (!(startX != startX) && (startX - startX != startX - startX)) {
    startX = S21_INFINITY;
  } else if (startX > 0) {
    for (int i = 1; i < 1000; i++) {
      startX = 1. / 2 * (startX + x / startX);
    }
  } else if (startX != startX) {
    startX = S21_NAN;
  } else {
    startX = 0;
  }

  return startX;
}

long double factorial(int n) {
  long double result = 1.0;
  for (int i = 1; i <= n; i++) result *= (long double)i;
  return result;
}

long double pow_whole(long double base, int power) {
  long double result = 1.0;
  for (int i = 1; i <= power; i++) result *= base;
  return result;
}

double cycle_range(double x, double max) {
  return s21_fmod(x + max, max * 2.0) - max;
}

#define PRESICION 32

// TODO
long double s21_sin(double x) {
  long double result = 0;
  x = cycle_range(x, S21_M_PI);

  for (int i = 0; i < PRESICION; i++) {
    int i_taylor_ser = i * 2 + 1;
    result += pow_whole(-1.0, i) * pow_whole(x, i_taylor_ser) /
              factorial(i_taylor_ser);
  }
  return result;
}

// TODO
long double s21_cos(double x) {
  long double result = 0;
  x = cycle_range(x, S21_M_PI);

  for (int i = 0; i < PRESICION; i++) {
    int i_taylor_ser = i * 2;
    result += pow_whole(-1.0, i) * pow_whole(x, i_taylor_ser) /
              factorial(i_taylor_ser);
  }
  return result;
}

#define TAN_MAX 1.633123935319537e+16;
// DONE
long double s21_tan(double x) {
  long double value;
  x = cycle_range(x, S21_M_PI);

  if (x == S21_PI_2) {
    value = TAN_MAX;
  } else if (x == -S21_PI_2) {
    value = -TAN_MAX;
  } else {
    value = s21_sin(x) / s21_cos(x);
  }

  return value;
}

long double s21_atan(double x) {
  long double sigh = 1;
  if (x < 0) {
    sigh = -1;
  }
  return sigh * s21_acos(1.0 / s21_sqrt(1 + x * x));
}

long double s21_asin(double x) {
  long double result;
  if (x > 1 || x < -1 || x != x) {
    result = S21_NAN;
  } else if (x == 1) {
    result = S21_PI_2;
  } else if (x == 0.0) {
    result = 0.0;
  } else if (x < 0) {
    result = -s21_asin(-x);
  } else if (x < 0.99) {
    result = 0.0;
    long double term = 100.0;

    long double factorial_2n = 1.0;
    long double factorial_n = 1.0;
    long double x_to_power = x;
    long double two_to_power = 1.0;

    for (int n = 0; term > CHECK_PRESICION * CHECK_PRESICION; n++) {
      term = factorial_2n / (two_to_power * factorial_n * factorial_n) *
             x_to_power / (2.0 * n + 1.0);
      result += term;

      if (n != 0) factorial_n *= n + 1;

      factorial_2n *= (long double)(2 * n + 1);
      factorial_2n *= (long double)(2 * n + 2);

      two_to_power *= 2.0 * 2.0;
      x_to_power *= x * x;
    }
  } else {
    x = 1.0 - x;
    long double sqrt_x = s21_sqrt(x);
    result = S21_PI_2 - S21_SQRT_2 * sqrt_x - S21_SQRT_2 / 12.0 * sqrt_x * x;
  }
  return result;
}

long double s21_acos(double x) { return (S21_PI_2 - s21_asin(x)); }

int get_double_exponent(double x) {
  // Evil pointer hack >:)
  int64_t *raw_ptr = (int64_t *)&x;
  int64_t raw_val = *raw_ptr;
  return (((raw_val >> 52) & 0x7FF) - 1023);
}

double get_double_mantissa(double x) {
  // Evil pointer hack >:)
  double y = x;
  int64_t *raw_ptr = (int64_t *)&y;
  *raw_ptr = ((*raw_ptr) & 0x000FFFFFFFFFFFFF) | 0x3FF0000000000000;
  return y;
}

long double inner_log(long double _x_0, double n) {
  long double x_0 = _x_0;

  // Newtonian method
  while (x_0 == x_0 && s21_fabs(s21_exp(x_0) - n) >= CHECK_PRESICION) {
    long double x_1 = x_0 - (s21_exp(x_0) - n) / s21_exp(x_0);
    x_0 = x_1;
  }

  return x_0;
}

long double s21_log(double n) {
  long double return_val;
  if (n < 0.0 || n != n) {
    return_val = S21_NAN;
  } else if (n == 0) {
    return_val = -S21_INFINITY;
  } else if (n > S21_DOUBLE_MAX) {
    return_val = S21_INFINITY;
  } else if (n <= S21_DOUBLE_MIN) {
    return_val = -7.0839642026636864e+02;
  } else {
    int exponent = (int)get_double_exponent(n);
    double mantissa = get_double_mantissa(n);

    while (mantissa < 1.0) {
      mantissa *= 2;
      exponent--;
    }

    long double x_0 =
        ((long double)exponent) * S21_LN_TWO + inner_log(mantissa, mantissa);

    return_val = x_0;
  }
  return return_val;
}

// DONE
long double s21_floor(double num) {
  long double result;
  if (num >= LLONG_MAX || num <= LLONG_MIN || num != num) {
    /* handle large values, infinities and nan */
    result = num;
  } else {
    long long n = (long long)num;
    long double d = (long double)n;

    if (d != num && num < 0) d -= 1;
    result = d;
  }
  return result;
}

// DONE
long double s21_ceil(double num) {
  long double num_floor = s21_floor(num);

  if (num_floor < num) num_floor += 1.0;

  return num_floor;
}

// DONE
long double s21_exp(double x) {
  const double threshold = 1e-15;
  long double return_val;

  if (x == 0.0) {
    return_val = 1.0;
  } else if (x == S21_INFINITY) {
    return_val = S21_INFINITY;
  } else if (x <= -20.0) {
    return_val = 0.0;  // In that case values are so small, it does not matter
  } else if (0 && x >= 1.0) {
    long double result = S21_EXP;
    long double power = 1.0;
    while (power < x) {
      result *= result;
      power *= 2.0;
    }
  } else {
    double result = 1.0;
    double term = 1.0;
    double relative_error = threshold + 1.0;
    int i = 1;
    while (relative_error > threshold) {
      term *= x / i;
      double prev_result = result;
      result += term;
      relative_error = s21_fabs((result - prev_result) / prev_result);
      i++;
    }
    return_val = result;
  }

  return return_val;
}

long double s21_zero_to_power(double exponent) {
  long double value;

  if (exponent == 0.0) {
    value = 1;
  } else if (exponent > 0) {
    value = 0;
  } else {
    value = S21_INFINITY;
  }

  return value;
}

long double s21_inf_to_power(double base, double exponent) {
  long double value;

  if (exponent < 0) {
    value = 0.0;
  } else if (exponent == 0) {
    value = 1.0;
  } else {
    value = base > 0 ? base
                     : ((int)exponent % 2 == 0 ? S21_INFINITY : -S21_INFINITY);
  }

  return value;
}

// DONE
long double s21_pow(double base, double exponent) {
  long double value;
  if (base == 1.0 || s21_fabs(exponent) == 0.0) {
    value = 1.0;
  } else if (base == -1.0 && s21_fabs(exponent) >= S21_INFINITY) {
    value = 1.0;
  } else if (base != base || exponent != exponent) {
    // NAN
    value = S21_NAN;
  } else if (base == 0.0 || base == -0.0) {
    value = s21_zero_to_power(exponent);
  } else if (s21_fabs(base) >= S21_INFINITY) {
    // infinity to the power
    value = s21_inf_to_power(base, exponent);
  } else if (base < 0) {
    // Negative value to the power
    if (s21_ceil(exponent) != exponent) {
      value = S21_NAN;
    } else {
      long double result = s21_exp(exponent * s21_log(-base));
      value = (int)exponent % 2 == 0 ? result : -result;
    }

  } else if (-exponent >= S21_INFINITY) {
    value = base > 1 ? 0 : (base < 1 ? S21_INFINITY : 1);
  } else if (exponent >= S21_INFINITY) {
    value = base > 1 ? S21_INFINITY : (base < 1 ? 0 : 1);
  } else if (exponent == 1) {
    value = base;
  } else {
    value = s21_exp(exponent * s21_log(base));
  }

  return value;
}

// DONE
long double s21_fmod(double x, double y) {
  long double result;
  y = s21_fabs(y);
  // x != x is NAN check
  if (y == 0.0 || x != x || y != y) {
    result = S21_NAN;
  } else if (s21_fabs(x) >= S21_INFINITY && s21_fabs(y) >= S21_INFINITY) {
    result = S21_NAN;
  } else if (x < 0.0) {
    result = -s21_fmod(-x, y);
  } else if (x >= (S21_DOUBLE_MAX / 2.0)) {
    result = 2.0 * s21_fmod(x / 2.0, y / 2.0);
  } else {
    result = x;

    while (result >= y) {
      long double sub = y;
      while ((sub * 2.0) <= result) sub *= 2.0;
      result -= sub;
    }
  }
  return result;
}
