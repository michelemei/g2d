#include "stdafx.h"
#include "Line.h"
#include "dbl.h"

using namespace std;
using namespace osl::g2d;

Line::Line(const Point& start_point, const Point& end_point)
	: Oriented(start_point), end_point(end_point)
{
	if (start_point == end_point)
	{
		throw exception("Line constructor: start point and end point are coincident. It's not a line, it's a point!");
	}
}

Line::~Line() {}

bool Line::operator==(const Item& other) const
{
	const Line* other_line = dynamic_cast<const Line*>(&other);
	if (other_line == nullptr)
		return false;

	return start_point == other_line->start_point &&
		end_point == other_line->end_point;
}

const Point& Line::GetEndPoint() const
{
	return end_point;
}

unique_ptr<Item> Line::Clone() const
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