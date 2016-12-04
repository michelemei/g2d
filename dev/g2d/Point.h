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
	\param x X coordinate
	\param y Y coordinate
	*/
	Point(double x = 0.0, double y = 0.0);

	//! Copy constructor
	/*!
	\param copy Source point for the copy
	*/
	Point(const Point& copy);

	//! Assignment operator
	/*!
	\param other Point for which take values
	*/
	const Point& operator=(const Point& other);

	//! Equals operator
	/*!
	Two points are equals when the distance is less than dbl_tollerance
	*/
	bool operator==(const Point&) const;

	//! Not equals operator
	/*!
	The not of equals operator
	*/
	bool operator!=(const Point&) const;

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

	//! Distance from another \ref Point
	double Distance(const Point& other) const;

	//! Returns the distance between this point and a \ref Line
	double Distance(const Line& line) const;
};

}}

#endif