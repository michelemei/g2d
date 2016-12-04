#ifndef __osl_g2d_path_h
#define __osl_g2d_path_h

#include "Oriented.h"

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
	std::unique_ptr<std::vector<std::unique_ptr<Oriented>>> items;

public:
	explicit Path(std::unique_ptr<Oriented> start_item);
	explicit Path(std::vector<std::unique_ptr<Oriented>>& items, unsigned int from = 0, unsigned int to = 0);

	//! Check if path is close
	/*!
	\return True if the first, and end points of path are equals
	*/
	bool IsClosed() const;

	const std::unique_ptr<Oriented>& at(unsigned int index) const;
	void push_back(std::unique_ptr<Oriented> item);
	std::unique_ptr<Oriented> erase(unsigned int index);
	unsigned int size() const;
	const std::vector<std::unique_ptr<Oriented>>& get_items() const;

	/* Item.h */
	virtual ~Path();
	virtual const Point& GetEndPoint() const override;
	virtual std::unique_ptr<Oriented> Clone() const override;
	virtual void Move(double delta_x, double delta_y) override;
	virtual void Move(const Point& delta) override;
	virtual void Reverse() override;
};
typedef std::unique_ptr<Path> PathPtr;

}
}

#endif