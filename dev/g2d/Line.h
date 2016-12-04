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

	//! Equals operator
	/*!
	Two lines are equals when they have the same:
	- start point (\ref Point::operator==)
	- end point
	*/
	bool operator==(const Line&) const;

	// Items methods (see Items.h)
	virtual ~Line();
	virtual const Point& GetEndPoint() const override;
	virtual std::unique_ptr<Oriented> Clone() const override;
	virtual void Move(double delta_x, double delta_y) override;
	virtual void Move(const Point& delta) override;
	virtual void Reverse() override;
};

}
}

#endif