#include "stdafx.h"
#include "Oriented.h"

using namespace osl::g2d;
using namespace std;

Oriented::~Oriented() {}

Oriented::Oriented(const Point& startPoint)
	: start_point(startPoint), OffsetTag(NotSet)
{
}

const Point& Oriented::GetStartPoint() const
{
	return start_point;
}
