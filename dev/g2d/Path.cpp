#include "stdafx.h"
#include "Path.h"

using namespace std;
using namespace osl;
using namespace g2d;

Path::Path(unique_ptr<Oriented> start_item)
	: Oriented(start_item->GetStartPoint())
{
	items = unique_ptr<vector<unique_ptr<Oriented>>>(new vector<unique_ptr<Oriented>>());
	items->push_back(move(start_item));
}

Path::Path(vector<unique_ptr<Oriented>>& items, unsigned int from, unsigned int to)
	: Oriented(items[from]->GetStartPoint())
{
	if (from >= items.size())
		from = 0;

	if (to <= from)
		to = items.size();

	to = min(to, items.size());

	this->items = unique_ptr<vector<unique_ptr<Oriented>>>(new vector<unique_ptr<Oriented>>());
	for (unsigned int i = from; i < to; ++i)
	{
		this->items->push_back(move(items[i]));
	}
}

Path::~Path() {}

bool Path::IsClosed() const
{
	return (*items->begin())->GetStartPoint() == (*items->back()).GetEndPoint();
}

const Point& Path::GetEndPoint() const
{
	return items->back()->GetEndPoint();
}

unique_ptr<Oriented> Path::Clone() const
{
	vector<unique_ptr<Oriented>> items_copy;
	for (auto i = items->begin(); i != items->end(); ++i)
	{
		items_copy.push_back(move((*i)->Clone()));
	}
	return unique_ptr<Path>(new Path(items_copy));
}

void Path::Move(double delta_x, double delta_y)
{
	this->Move(Point(delta_x, delta_y));
}

void Path::Move(const Point& delta)
{
	for (unsigned int i = 0; i < items->size(); ++i)
	{
		items->at(i).get()->Move(delta);
	}
}

void Path::Reverse()
{
	for (unsigned int i = 0; i < items->size(); ++i)
	{
		items->at(i).get()->Reverse();
	}

	reverse(items->begin(), items->end());
}

const unique_ptr<Oriented>& Path::at(unsigned int index) const
{
	return items->at(index);
}

void Path::push_back(unique_ptr<Oriented> item)
{
	items->push_back(move(item));
}

unique_ptr<Oriented> Path::erase(unsigned int index)
{
	unique_ptr<Oriented> item = move(items->operator[](index));
	items->erase(items->begin() + index);
	return move(item);
}

unsigned int Path::size() const
{
	return items->size();
}

const vector<unique_ptr<Oriented>>& Path::get_items() const
{
	return *items;
}