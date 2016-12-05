/*******************************************************************************

This file is part of G2D.

G2D is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

G2D is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You can get a copy of of the GNU General Public License
at<http://www.gnu.org/licenses/>.

Author: Michele Mei
E-Mail: michele.mei@gmail.com

*******************************************************************************/
#ifndef __osl_g2d_path_h
#define __osl_g2d_path_h

#include "Oriented.h"
#include <vector>

namespace osl {
namespace g2d {

/*! \class Path
\brief A path in two-dimension
A path can be "open" or "closed", if the starting and end points coincides
(\ref Point::operator==) then it is a closed path. A path can be self
intersecting.
*/
class G2D_API Path : public Oriented
{
	//! List of oriented items
	std::unique_ptr<std::vector<std::unique_ptr<Oriented>>> oriented_items;

public:
	/*!
	One item constructor
	\param start_item First item
	*/
	explicit Path(std::unique_ptr<Oriented> start_item);
	
	/*!
	Create a path from a vector of oriented items.
	\param items First item
	\param from Optional. Initial item, if 0 taken the first
	\param to Optional. Final item, if 0 taken the the last
	*/
	explicit Path(std::vector<std::unique_ptr<Oriented>>& oriented_items,
	              unsigned int from = 0, unsigned int to = 0);

	//! Check if path is close
	/*!
	\return True if the first and end points of path are equals.
	        Using \ref Point::operator==.
	*/
	bool IsClosed() const;

	//! Get oriented item at the specified index
	/*!
	\param[in] index Item's index
	\return A const reference to unique_ptr of oriented item
	*/
	const std::unique_ptr<Oriented>& at(unsigned int index) const;
	
	//! Push back an oriented item in the path
	/*!
	\param[in] oriented_item Oriented item
	*/
	void push_back(std::unique_ptr<Oriented> oriented_item);

	//! Erase the oriented item at the specified index
	/*!
	\param[in] index Item's index
	\return A unique_ptr with the element eliminated on which the move was made
	        and can be taken over by the caller
	*/
	std::unique_ptr<Oriented> erase(unsigned int index);

	//! Gets the number of oriented items in the path
	unsigned int size() const;

	//! Get all the items in the path
	/*!
	\return A const vector with the item's oriented items.
	*/
	const std::vector<std::unique_ptr<Oriented>>& get_items() const;

	/* from Item.h */
	virtual ~Path();
	virtual std::unique_ptr<Item> Clone() const override;
	virtual void Move(double delta_x, double delta_y) override;
	virtual void Move(const Point& delta) override;

	/* from Oriented.h */
	virtual const Point& GetEndPoint() const override;
	virtual void Reverse() override;
};

}
}

#endif