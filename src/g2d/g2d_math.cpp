#include "stdafx.h"
#include "g2d_math.h"
#include "dbl.h"

#define _USE_MATH_DEFINES
#include <math.h>

double __get_phi(double x, double y)
{
	if (dbl_greater(x, 0.0))
	{
		return dbl_greater_or_equal(y, 0.0) ? atan2(y, x) : atan2(y, x) + 2 * M_PI;
	}
	if (dbl_less(x, 0.0))
	{
		return M_PI - atan2(y, abs(x));
	}
	return dbl_greater_or_equal(y, 0.0) ? M_PI_2 : 3 * M_PI_2;
}

double __normalize_angle(double angle)
{
	angle = fmod(angle, M_PI * 2);
	if (angle < 0.0)
		angle += M_PI * 2;
	return angle;
}

double  __normalize_angle_sign(double angle, bool positive)
{
	angle = __normalize_angle(angle);
	if (!positive)
		angle -= 2 * M_PI;
	return angle;
}

#undef _USE_MATH_DEFINES