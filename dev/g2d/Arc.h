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
#ifndef __osl_g2d_arc_h
#define __osl_g2d_arc_h

#include "Oriented.h"
#include <vector>

namespace osl {
namespace g2d {

/*! \class Arc
\brief An arc in two-dimension

All angles are in radians.
*/
class G2D_API Arc : public Oriented
{
	//! Arc's center
	Point center;

	//! Arc's radius
	double radius;

	//! Arc's starting angle
	double start_angle;

	//! Arc's subtended angle
	double subtended_angle;

	//! Arc's end point
	Point end_point;

public:
	//! Arc's constructor by: start, center and end points.
	/*!
	\param start_point Arc's start point
	\param end_point Arc's end point
	\param center Arc's center
	\param counter_clockwise Circulare motion: true for counterclockwise (CCW),
	                         false for clockwise (CW)
	*/
	Arc(const Point& start_point, const Point& end_point, const Point& center,
	    bool counter_clockwise);

	/*!
	\param center Arc's center
	\param radius Arc's radius
	\param start_angle Arc's start angle (positive)
	\param end_angle Arc's end angle (positive)
	\param counter_clockwise Circular motion: true for counterclockwise (CCW),
	                         false for clockwise (CW)
	*/
	Arc(const Point& center, double radius, double start_angle,
	    double end_angle, bool counter_clockwise);

	//! Arc's constructor by: center, radius, start angle and subtended angle.
	/*!
	\param center Arc's center
	\param radius Arc's radius
	\param start_angle Arc's start angle (positive)
	\param subtended_angle Arc's subtended angle
	*/
	Arc(const Point& center, double radius, double start_angle,
	    double subtended_angle);

	//! Arc's constructor by: start, center and subtended angle
	/*!
	\param start_point Arc's start point
	\param center Arc's center point
	\param subtended_angle Arc's subtended angle
	*/
	Arc(const Point& start_point, const Point& center, double subtended_angle);

	//! Equals operator
	/*!
	Two arcs are equals when they have the same:
	- center (\ref Point::operator==)
	- radius (dbl tollerance)
	- starting angle (dbl tollerance)
	- subtended angle (dbl tollerance)
	*/
	bool operator==(const Arc&) const;

	//! Gets the arc's center
	const Point& GetCenter() const;

	//! Gets the arc's radius
	double GetRadius() const;

	//! Gets the arc's starting angle
	double GetStartAngle() const;

	//! Gets the arc's subtended angle
	double GetSubtendedAngle() const;

	/* Item.h */
	virtual ~Arc();
	virtual std::unique_ptr<Oriented> Clone() const override;
	virtual const Point& GetEndPoint() const override;
	virtual void Move(double delta_x, double delta_y) override;
	virtual void Move(const Point& delta) override;
	virtual void Reverse() override;
};

}
}

#endif
