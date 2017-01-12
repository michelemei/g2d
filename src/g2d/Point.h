/*******************************************************************************

This file is part of G2D.

G2D is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

G2D is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You can get a copy of of the GNU General Public License
at<http://www.gnu.org/licenses/>.

Author: Michele Mei
E-Mail: michele.mei@gmail.com

*******************************************************************************/
#ifndef __osl_g2d_point_h
#define __osl_g2d_point_h

#include "g2d_exports.h"

namespace osl {
namespace g2d {

class Line;

/*! \class Point
\brief A point in two-dimension
*/
class G2D_API Point
{
public:
	//! X coordinate of the point
	double X;

	//! Y coordinate of the point
	double Y;

	//! Base constructor
	/*!
	\param[in] x X coordinate
	\param[in] y Y coordinate
	*/
	explicit Point(double x = 0.0, double y = 0.0);

	//! Copy constructor
	/*!
	\param[in] copy Source point for the copy
	*/
	Point(const Point& copy);

	//! Assignment operator
	/*!
	\param[in] other Point for which take values
	*/
	Point& operator=(const Point& other);

	//! Equal operator
	/*!
	\brief Two points are equals when the distance is less than dbl_tollerance
	\param[in] other The other point to make the comparison
	*/
	bool operator==(const Point& other) const;

	//! Inequality operator
	/*!
	\brief Inequality operator (not of equal operator)
	\param[in] other The other point to make the comparison
	*/
	bool operator!=(const Point& other) const;

	//! Addition operator between points
	Point operator+(const Point&) const;

	//! Add a point to this
	/*!
	me.X = me.X + other.X \n
	me.Y = me.Y + other.Y
	*/
	Point& operator+=(const Point&);

	//! Subtraction operator between points
	Point operator-(const Point&) const;

	//! Subtrack a point to this
	/*!
	me.X = me.X - other.X \n
	me.Y = me.Y - other.Y
	*/
	Point& operator-=(const Point&);

	Point operator*(double) const;
	Point& operator*=(double);

	void Rotate(const Point& center, double radians);

	//! Distance from another \ref Point
	double Distance(const Point& other) const;

	//! Returns the distance between this point and a \ref Line
	double Distance(const Line& line) const;
};

}}

#endif