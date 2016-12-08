#include "stdafx.h"
#include "Shape.h"
#include "Path.h"

using namespace std;
using namespace osl::g2d;

Shape::Shape(unique_ptr<Path> single)
{
	paths = unique_ptr<vector<unique_ptr<Path>>>(new vector<unique_ptr<Path>>());
	paths->push_back(move(single));
}

Shape::Shape(vector<unique_ptr<Path>>& _paths)
{
	paths = unique_ptr<vector<unique_ptr<Path>>>(new vector<unique_ptr<Path>>());
	for (auto p = _paths.begin(); p != _paths.end(); ++p)
	{
		paths->push_back(move(*p));
	}
}

const unique_ptr<vector<unique_ptr<Path>>>& Shape::GetPaths() const
{
	return paths;
}

void Shape::Move(double /*delta_x*/, double /*delta_y*/)
{
	throw exception("Not yet implemented");
}

void Shape::Move(const Point& /*delta*/)
{
	throw exception("Not yet implemented");
}

std::unique_ptr<Item> Shape::Clone() const
{
	throw exception("Not yet implemented");
}
