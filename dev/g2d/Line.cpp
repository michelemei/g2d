#include "stdafx.h"
#include "Line.h"
#include <vector>
#include "Path.h"

using namespace std;
using namespace osl::g2d;

Line::Line(const Point& start_point, const Point& end_point)
	: Oriented(start_point), end_point(end_point)
{
	if (start_point == end_point)
		throw exception("Line constructor: start point and end point are coincident. It's not a line, it's a point!");
}

Line::~Line() {}

bool Line::operator==(const Line& other) const
{
	return start_point == other.start_point && end_point == other.end_point;
}

const Point& Line::GetEndPoint() const
{
	return end_point;
}

unique_ptr<Oriented> Line::Clone() const
{
	return unique_ptr<Line>(new Line(start_point, end_point));
}

void Line::Move(double delta_x, double delta_y)
{
	this->Move(Point(delta_x, delta_y));
}

void Line::Move(const Point& delta)
{
	start_point += delta;
	end_point += delta;
}

void Line::Reverse()
{
	Point tmp(start_point);
	start_point = end_point;
	end_point = tmp;
}