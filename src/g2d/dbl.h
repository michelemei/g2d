#pragma once
#include "g2d_precision.h"

#define dbl_is_zero(v) (-dbl_precision < v && v < dbl_precision)
#define dbl_equal(a, b) dbl_is_zero(a - b)
#define dbl_not_equal(a, b) (!dbl_is_zero(a - b))
#define dbl_greater(a, b) (a > b && !dbl_equal(a, b))
#define dbl_less(a, b) (a < b && !dbl_equal(a, b))
#define dbl_greater_or_equal(a, b) (a > b || dbl_equal(a, b))
#define dbl_less_or_equal(a, b) (a < b || dbl_equal(a, b))
#define dbl_abs(a) ((a) > 0.0 ? (a) : -(a))
