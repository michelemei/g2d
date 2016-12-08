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
#ifndef __osl_g2d_oriented_h
#define __osl_g2d_oriented_h

#include "Item.h"
#include "Point.h"
#include "g2d_enum.h"

namespace osl {
namespace g2d {

class Path;
/*! \class Oriented
\brief A generic oriented two-dimensional geometric element
*/
class G2D_API Oriented : public Item
{
protected:
	//! Start point
	Point start_point;

public:
	/*!
	\param start_point Item's start point
	*/
	explicit Oriented(const Point& start_point);
	virtual ~Oriented();

	//! Gets the starting point
	/*!
	\return Starting point
	*/
	const Point& GetStartPoint() const;

	//! Gets the ending point
	/*!
	\return Ending point
	*/
	virtual const Point& GetEndPoint() const = 0;

	//! Reverse the oriented item
	virtual void Reverse() = 0;

	/*!
	\deprecated Currently it is used only by offset module
	*/
	OffsetTag OffsetTag;
};

}
}

#endif