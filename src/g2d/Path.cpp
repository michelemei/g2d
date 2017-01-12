#include "stdafx.h"
#include "Path.h"

using namespace std;
using namespace osl;
using namespace g2d;

struct Path::PathAttributes
{
	//! List of oriented items
	unique_ptr<vector<unique_ptr<Oriented>>> oriented_items;
};

Path::Path(unique_ptr<Oriented> start_item)
	: Oriented(start_item->GetStartPoint()), attributes(new PathAttributes())
{
	attributes->oriented_items = unique_ptr<vector<unique_ptr<Oriented>>>(new vector<unique_ptr<Oriented>>());
	attributes->oriented_items->push_back(move(start_item));
}

Path::Path(vector<unique_ptr<Oriented>>& oriented_items, unsigned int from,
           unsigned int to) : Oriented(oriented_items[from]->GetStartPoint()), attributes(new PathAttributes())
{
	if (from >= oriented_items.size())
	{
		from = 0;
	}

	if (to <= from)
	{
		to = oriented_items.size();
	}
	to = min(to, oriented_items.size());

	attributes->oriented_items = unique_ptr<vector<unique_ptr<Oriented>>>(new vector<unique_ptr<Oriented>>());
	for (unsigned int i = from; i < to; ++i)
	{
		attributes->oriented_items->push_back(move(oriented_items[i]));
	}
}

bool Path::operator==(const Item& other) const
{
	const Path* other_path = dynamic_cast<const Path*>(&other);
	if (other_path == nullptr)
		return false;

	if (attributes->oriented_items->size() != other_path->attributes->oriented_items->size())
		return false;

	for (unsigned int i = 0; i < attributes->oriented_items->size(); ++i)
	{
		if (*attributes->oriented_items->at(i) != *other_path->attributes->oriented_items->at(i))
			return false;
	}
	return true;
}

Path::~Path()
{
	delete attributes;
}

bool Path::IsClosed() const
{
	return (*attributes->oriented_items->begin())->GetStartPoint() ==
	       (*attributes->oriented_items->back()).GetEndPoint();
}

bool Path::IsConsecutive(vector<unique_ptr<Oriented>>& items)
{
	if (items.size() <= 1)
		return true;

	/*
	Come prima cosa sistemo il primo elemento: potrebbe essere infatti
	necessario fare il suo reverse.
	Il primo elemento deve subire un Reverse se:
	il suo EndPoint() e' diverso sia da StartPoint() che da EndPoint() del
	secondo, in tal caso verificare che StartPoint() sia uguale ad uno dei due
	*/

	if (items[0]->GetEndPoint() != items[1]->GetStartPoint() &&
		items[0]->GetEndPoint() != items[1]->GetEndPoint())
	{
		items[0]->Reverse();
	}

	const Point* current = &items.front()->GetEndPoint();
	// printf("[S] (%f, %f)\n", items.front()->GetStartPoint().X, items.front()->GetStartPoint().Y);
	// printf("[E] (%f, %f)\n\n", items.front()->GetEndPoint().X, items.front()->GetEndPoint().Y);

	for (auto i = items.begin() + 1; i != items.end(); ++i)
	{
		if (*current != (*i)->GetStartPoint())
		{
			if (*current == (*i)->GetEndPoint())
			{
				(*i)->Reverse();
			}
			else
			{
				return false;
			}
		}
		current = &(*i)->GetEndPoint();
		// printf("[S] (%f, %f)\n", (*i)->GetStartPoint().X, (*i)->GetStartPoint().Y);
		// printf("[E] (%f, %f)\n\n", (*i)->GetEndPoint().X, (*i)->GetEndPoint().Y);
	}
	return true;
}

const Point& Path::GetEndPoint() const
{
	return attributes->oriented_items->back()->GetEndPoint();
}

unique_ptr<Item> Path::Clone() const
{
	vector<unique_ptr<Oriented>> items_copy;
	for (auto i = attributes->oriented_items->begin(); i != attributes->oriented_items->end(); ++i)
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
	for (unsigned int i = 0; i < attributes->oriented_items->size(); ++i)
	{
		attributes->oriented_items->at(i).get()->Move(delta);
	}
}

void Path::Reverse()
{
	for (unsigned int i = 0; i < attributes->oriented_items->size(); ++i)
	{
		attributes->oriented_items->at(i).get()->Reverse();
	}

	reverse(attributes->oriented_items->begin(), attributes->oriented_items->end());
}

const unique_ptr<Oriented>& Path::at(unsigned int index) const
{
	return attributes->oriented_items->at(index);
}

void Path::push_back(unique_ptr<Oriented> oriented_item)
{
	attributes->oriented_items->push_back(move(oriented_item));
}

unique_ptr<Oriented> Path::erase(unsigned int index)
{
	unique_ptr<Oriented> item = move(attributes->oriented_items->operator[](index));
	attributes->oriented_items->erase(attributes->oriented_items->begin() + index);
	return move(item);
}

unsigned int Path::size() const
{
	return attributes->oriented_items->size();
}

const vector<unique_ptr<Oriented>>& Path::get_items() const
{
	return *attributes->oriented_items;
}