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
#ifndef __osl_line_h_
#define __osl_line_h_

#include "Oriented.h"

namespace osl {
namespace g2d {

/*! \class Line
\brief A line in two-dimension
*/
class G2D_API Line : public Oriented
{
	//! Line's end point
	Point end_point;

public:
	//! Line's constructor by start and end points.
	/*!
	\param start_point Line's start point
	\param end_point Line's end point
	*/
	Line(const Point& start_point, const Point& end_point);

	bool operator==(const Item& other) const override;

	/* Items.h */
	virtual ~Line();
	void Move(double delta_x, double delta_y) override;
	void Move(const Point& delta) override;

	/* Oriented.h */
	const Point& GetEndPoint() const override;
	std::unique_ptr<Item> Clone() const override;
	void Reverse() override;
};

}
}

#endif