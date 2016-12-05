#include "stdafx.h"
#include "Arc.h"
#include "dbl.h"
#include <assert.h>
#include "g2d_math.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
using namespace osl::g2d;

double get_angle_by_center_and_point(const Point& center, const Point& point)
{
	return __get_phi(point.X - center.X, point.Y - center.Y);
}

Arc::Arc(const Point& start_point, const Point& end_point, const Point& center, bool counter_clockwise)
	: Oriented(start_point),
	center(center), radius(center.Distance(start_point)), end_point(end_point)
{
	if (dbl_less_or_equal(radius, 0.0))
	{
		throw exception("radius can not be less or equals than zero");
	}

	if (dbl_not_equal(center.Distance(start_point), center.Distance(end_point)))
	{
		throw exception("distance among center point and start/end points are not equals");
	}

	start_angle = get_angle_by_center_and_point(center, start_point);
	assert(dbl_greater_or_equal(start_angle, 0.0) && dbl_less(start_angle, 2 * M_PI));

	subtended_angle = __normalize_angle_sign(get_angle_by_center_and_point(center, end_point) - start_angle, counter_clockwise);
	if (dbl_is_zero(subtended_angle))
	{
		if (counter_clockwise)
			subtended_angle = 2 * M_PI;
		else
			subtended_angle = -2 * M_PI;
	}
	assert(dbl_greater(abs(subtended_angle), 0.0) && dbl_less_or_equal(abs(subtended_angle), 2 * M_PI));
}

Arc::Arc(const Point& center, double radius, double start_angle, double end_angle, bool counter_clockwise)
	: Oriented(Point(center.X + cos(start_angle) * radius, center.Y + sin(start_angle) * radius)),
	center(center), radius(radius), start_angle(start_angle)
{
	if (dbl_less_or_equal(radius, 0.0))
	{
		throw exception("radius can not be less or equals than zero");
	}

	if (dbl_less(start_angle, 0.0))
	{
		throw exception("start angle can not be less than zero");
	}

	if (dbl_greater_or_equal(start_angle, 2 * M_PI))
	{
		throw exception("start angle can not be greater or equals than zero");
	}

	subtended_angle = __normalize_angle_sign(end_angle - start_angle, counter_clockwise);
	if (dbl_is_zero(subtended_angle))
	{
		if (counter_clockwise)
			subtended_angle = 2 * M_PI;
		else
			subtended_angle = -2 * M_PI;
	}
	assert(dbl_greater(abs(subtended_angle), 0.0) && dbl_less_or_equal(abs(subtended_angle), 2 * M_PI));

	end_point.X = center.X + cos(start_angle + subtended_angle) * radius;
	end_point.Y = center.Y + sin(start_angle + subtended_angle) * radius;
}

Arc::Arc(const Point& center, double radius, double start_angle, double subtended_angle)
	: Oriented(Point(center.X + cos(start_angle) * radius, center.Y + sin(start_angle) * radius)),
	center(center), radius(radius), start_angle(start_angle), subtended_angle(subtended_angle)
{
	if (dbl_less_or_equal(radius, 0.0))
	{
		throw exception("radius can not be less or equals than zero");
	}

	if (dbl_less(start_angle, 0.0))
	{
		throw exception("start angle can not be less than zero");
	}

	if (dbl_greater_or_equal(start_angle, 2 * M_PI))
	{
		throw exception("start angle can not be greater or equals than zero");
	}

	if (dbl_is_zero(dbl_abs(subtended_angle)))
	{
		throw exception("subtended angle can not be zero");
	}

	if (dbl_greater(dbl_abs(subtended_angle), 2 * M_PI))
	{
		throw exception("subtended angle can not be greater than 2PI or less than -2PI");
	}

	end_point.X = center.X + cos(start_angle + subtended_angle) * radius;
	end_point.Y = center.Y + sin(start_angle + subtended_angle) * radius;
}

Arc::Arc(const Point& start_point, const Point& center, double subtended_angle)
	: Oriented(start_point),
	center(center), radius(center.Distance(start_point)), subtended_angle(subtended_angle)
{
	if (dbl_less_or_equal(radius, 0.0))
	{
		throw exception("radius can not be less or equals than zero");
	}

	if (dbl_is_zero(dbl_abs(subtended_angle)))
	{
		throw exception("subtended angle can not be zero");
	}

	if (dbl_greater(dbl_abs(subtended_angle), 2 * M_PI))
	{
		throw exception("subtended angle can not be greater than 2PI or less than -2PI");
	}

	start_angle = get_angle_by_center_and_point(center, start_point);
	assert(dbl_greater_or_equal(start_angle, 0.0) && dbl_less(start_angle, 2 * M_PI));

	end_point.X = center.X + cos(start_angle + subtended_angle) * radius;
	end_point.Y = center.Y + sin(start_angle + subtended_angle) * radius;
}

Arc::~Arc() {}

bool Arc::operator==(const Arc& other) const
{
	return center == other.center &&
	       dbl_equal(radius, other.radius) &&
	       dbl_equal(start_angle, other.start_angle) &&
	       dbl_equal(subtended_angle, other.subtended_angle);
}

unique_ptr<Item> Arc::Clone() const
{
	return unique_ptr<Arc>(new Arc(center, radius, start_angle, subtended_angle));
}

const Point& Arc::GetCenter()const
{
	return center;
}

double Arc::GetRadius() const
{
	return radius;
}

double Arc::GetStartAngle() const
{
	return start_angle;
}

double Arc::GetSubtendedAngle() const
{
	return subtended_angle;
}

const Point& Arc::GetEndPoint() const
{
	return end_point;
}

void Arc::Move(double delta_x, double delta_y)
{
	this->Move(Point(delta_x, delta_y));
}

void Arc::Move(const Point& delta)
{
	start_point += delta;
	center += delta;
	end_point += delta;
}

void Arc::Reverse()
{
	Point tmp(start_point);
	start_point = end_point;
	end_point = tmp;

	// update start_angle
	start_angle = get_angle_by_center_and_point(center, start_point);
	assert(dbl_greater_or_equal(start_angle, 0.0) && dbl_less(start_angle, 2 * M_PI));

#ifdef _DEBUG
	bool previous_ccw = subtended_angle > 0;
	double new_subtended_angle = __normalize_angle_sign(get_angle_by_center_and_point(center, end_point) - start_angle, !previous_ccw);
	if (dbl_is_zero(new_subtended_angle))
	{
		if (!previous_ccw)
			new_subtended_angle = 2 * M_PI;
		else
			new_subtended_angle = -2 * M_PI;
	}

	assert(dbl_equal(subtended_angle * -1, new_subtended_angle));
#endif

	subtended_angle *= -1;
}

#undef _USE_MATH_DEFINES
