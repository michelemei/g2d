#include "stdafx.h"
#include "Shape.h"
#include "Path.h"

using namespace std;
using namespace osl::g2d;

struct Shape::ShapeAttributes
{
	unique_ptr<vector<unique_ptr<Path>>> paths;
};

Shape::Shape(unique_ptr<Path> single)
	: attributes(new ShapeAttributes())
{
	attributes->paths = unique_ptr<vector<unique_ptr<Path>>>(new vector<unique_ptr<Path>>());
	attributes->paths->push_back(move(single));
}

Shape::Shape(vector<unique_ptr<Path>>& _paths)
	: attributes(new ShapeAttributes())
{
	attributes->paths = unique_ptr<vector<unique_ptr<Path>>>(new vector<unique_ptr<Path>>());
	for (auto p = _paths.begin(); p != _paths.end(); ++p)
	{
		attributes->paths->push_back(move(*p));
	}
}

bool Shape::operator==(const Item& other) const
{
	const Shape* other_shape = dynamic_cast<const Shape*>(&other);
	if (other_shape == nullptr)
		return false;

	if (attributes->paths->size() != other_shape->attributes->paths->size())
		return false;

	for (unsigned int i = 0; i < attributes->paths->size(); ++i)
	{
		if (*attributes->paths->at(i) != *other_shape->attributes->paths->at(i))
			return false;
	}
	return true;
}

const unique_ptr<vector<unique_ptr<Path>>>& Shape::GetPaths() const
{
	return attributes->paths;
}

Shape::~Shape()
{
	delete attributes;
}

void Shape::Move(double /*delta_x*/, double /*delta_y*/)
{
	throw exception("Not yet implemented");
}

void Shape::Move(const Point& /*delta*/)
{
	throw exception("Not yet implemented");
}

unique_ptr<Item> Shape::Clone() const
{
	vector<unique_ptr<Path>> paths_copy;
	for (auto i = attributes->paths->begin(); i != attributes->paths->end(); ++i)
	{
		Item* clone = (*i)->Clone().release();
		Path* path_copy = dynamic_cast<Path*>(clone);
		if (path_copy != nullptr)
		{
			paths_copy.push_back(move(unique_ptr<Path>(path_copy)));
		}
	}
	return unique_ptr<Shape>(new Shape(paths_copy));
}
