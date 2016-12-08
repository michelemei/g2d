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

Author:  Michele Mei
E-Mail:  michele.mei@gmail.com

*******************************************************************************/
#ifndef __osl_g2d_item_h
#define __osl_g2d_item_h

#include "g2d_exports.h"
#include <memory>

namespace osl {
namespace g2d {

class Point;
/*! \class Item
\brief A generic item in two-dimension
*/
class G2D_API Item
{
public:
	virtual ~Item() { }

	//! Clone the item
	/*!
	\return A clone of item
	*/
	virtual std::unique_ptr<Item> Clone() const = 0;

	/*!
	Move the item (translation on the plane).
	\param delta_x X component of translation
	\param delta_y Y component of translation
	*/
	virtual void Move(double delta_x, double delta_y) = 0;

	/*!
	Move the item (translation on the plane).
	\param delta Translation
	*/
	virtual void Move(const Point& delta) = 0;
};

}
}

#endif