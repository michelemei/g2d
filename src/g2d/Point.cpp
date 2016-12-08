#include "stdafx.h"
#include "Point.h"
#include "dbl.h"
#include "Line.h"

using namespace osl::g2d;

Point::Point(double x, double y)
	: X(x), Y(y)
{
}

Point::Point(const Point& copy)
	: X(copy.X), Y(copy.Y)
{
}

const Point& Point::operator=(const Point& other)
{
	X = other.X;
	Y = other.Y;
	return *this;
}

Point Point::operator+(const Point& other) const
{
	return Point(X + other.X, Y + other.Y);
}

Point& Point::operator+=(const Point& other)
{
	X += other.X;
	Y += other.Y;
	return *this;
}

Point Point::operator-(const Point& other) const
{
	return Point(X - other.X, Y - other.Y);
}

Point& Point::operator-=(const Point& other)
{
	X -= other.X;
	Y -= other.Y;
	return *this;
}

Point Point::operator*(double value) const
{
	return Point(X * value, Y * value);
}

Point& Point::operator*=(double value)
{
	X *= value;
	Y *= value;
	return *this;
}

double Point::Distance(const Point& other) const
{
	return sqrt(pow(other.X - X, 2) + pow(other.Y - Y, 2));
}

double Point::Distance(const Line& line) const
{
	if (dbl_equal(line.GetStartPoint().X, line.GetEndPoint().X))
	{
		return dbl_abs(X - line.GetStartPoint().X);
	}

	// determinazione dei coefficienti m e q (sarebbe bello che siano gia' propri della linea)
	double num = line.GetEndPoint().X - line.GetStartPoint().X;
	double m = (line.GetEndPoint().Y - line.GetStartPoint().Y) / num;
	double q = (line.GetEndPoint().X * line.GetStartPoint().Y - line.GetStartPoint().X * line.GetEndPoint().Y) / num;
	return dbl_abs(Y - m * X - q) / sqrt(1 + m * m);
}

bool Point::operator==(const Point& other) const
{
	return pow(other.X - X, 2) + pow(other.Y - Y, 2) < dbl_precision_sqrt;
}

bool Point::operator!=(const Point& other) const
{
	return !operator==(other);
}
