#ifndef __osl_g2d_oriented_h
#define __osl_g2d_oriented_h

#include "Point.h"
#include "g2d_enum.h"
#include <vector>
#include <memory>
#include "Item.h"

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

	//! Gets start point
	const Point& GetStartPoint() const;

	//! Gets end point
	virtual const Point& GetEndPoint() const = 0;

	virtual std::unique_ptr<Oriented> Clone() const = 0;

	virtual void Reverse() = 0;

	OffsetTag OffsetTag;
};

}
}

#endif