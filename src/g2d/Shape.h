#pragma once
#include <vector>
#include <memory>
#include "Item.h"

namespace osl {
namespace g2d {

class Oriented;
class Line;
class Point;
class Path;

class G2D_API Shape : public Item
{
	std::unique_ptr<std::vector<std::unique_ptr<Path>>> paths;
public:
	explicit Shape(std::unique_ptr<Path> single);
	explicit Shape(std::vector<std::unique_ptr<Path>>& paths);

	const std::unique_ptr<std::vector<std::unique_ptr<Path>>>& GetPaths() const;

	void Move(double delta_x, double delta_y) override;
	void Move(const Point& delta) override;
	std::unique_ptr<Item> Clone() const override;
};

}
}