#ifndef __osl_g2d_item_h
#define __osl_g2d_item_h

#include "g2d_exports.h"

namespace osl {
	namespace g2d {

		class Point;
		class G2D_API Item
		{
		public:
			virtual ~Item() { }

			virtual void Move(double delta_x, double delta_y) = 0;
			virtual void Move(const Point& delta) = 0;
		};

	}
}

#endif