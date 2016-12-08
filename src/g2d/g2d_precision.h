#ifndef __g2d_precision_h
#define __g2d_precision_h

#include "g2d_exports.h"

static double dbl_precision = 0.0001;
static double dbl_precision_sqrt = 0.00000001;

inline G2D_API void set_dbl_precision(double value)
{
	dbl_precision = value;
	dbl_precision_sqrt = dbl_precision * dbl_precision;
}

inline G2D_API double get_dbl_precision(void)
{
	return dbl_precision;
}

#endif