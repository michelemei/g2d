#include "stdafx.h"
#include "Path.h"

using namespace std;
using namespace osl;
using namespace g2d;

Path::Path(unique_ptr<Oriented> start_item)
	: Oriented(start_item->GetStartPoint())
{
	oriented_items = unique_ptr<vector<unique_ptr<Oriented>>>(new vector<unique_ptr<Oriented>>());
	oriented_items->push_back(move(start_item));
}

Path::Path(vector<unique_ptr<Oriented>>& oriented_items, unsigned int from,
           unsigned int to) : Oriented(oriented_items[from]->GetStartPoint())
{
	if (from >= oriented_items.size())
		from = 0;

	if (to <= from)
		to = oriented_items.size();

	to = min(to, oriented_items.size());

	this->oriented_items = unique_ptr<vector<unique_ptr<Oriented>>>(new vector<unique_ptr<Oriented>>());
	for (unsigned int i = from; i < to; ++i)
	{
		this->oriented_items->push_back(move(oriented_items[i]));
	}
}

Path::~Path() {}

bool Path::IsClosed() const
{
	return (*oriented_items->begin())->GetStartPoint() == (*oriented_items->back()).GetEndPoint();
}

const Point& Path::GetEndPoint() const
{
	return oriented_items->back()->GetEndPoint();
}

unique_ptr<Item> Path::Clone() const
{
	vector<unique_ptr<Oriented>> items_copy;
	for (auto i = oriented_items->begin(); i != oriented_items->end(); ++i)
	{
		Item* clone = (*i)->Clone().release();
		Oriented* oriented = dynamic_cast<Oriented*>(clone);
		if (oriented != nullptr)
		{
			items_copy.push_back(move(unique_ptr<Oriented>(oriented)));
		}
	}
	return unique_ptr<Path>(new Path(items_copy));
}

void Path::Move(double delta_x, double delta_y)
{
	this->Move(Point(delta_x, delta_y));
}

void Path::Move(const Point& delta)
{
	for (unsigned int i = 0; i < oriented_items->size(); ++i)
	{
		oriented_items->at(i).get()->Move(delta);
	}
}

void Path::Reverse()
{
	for (unsigned int i = 0; i < oriented_items->size(); ++i)
	{
		oriented_items->at(i).get()->Reverse();
	}

	reverse(oriented_items->begin(), oriented_items->end());
}

const unique_ptr<Oriented>& Path::at(unsigned int index) const
{
	return oriented_items->at(index);
}

void Path::push_back(unique_ptr<Oriented> oriented_item)
{
	oriented_items->push_back(move(oriented_item));
}

unique_ptr<Oriented> Path::erase(unsigned int index)
{
	unique_ptr<Oriented> item = move(oriented_items->operator[](index));
	oriented_items->erase(oriented_items->begin() + index);
	return move(item);
}

unsigned int Path::size() const
{
	return oriented_items->size();
}

const vector<unique_ptr<Oriented>>& Path::get_items() const
{
	return *oriented_items;
}