#pragma once
#ifdef OFFSET_EXPORTS
#define OFFSET_API __declspec(dllexport)
#else
#define OFFSET_API __declspec(dllimport)
#endif

#include <memory>
#include <vector>

namespace osl {
namespace g2d {
	class Shape;

	enum buffer_extreme
{
	be_none,
	be_round
};

class Path;
class Line;
class Arc;

extern OFFSET_API std::vector<std::unique_ptr<Path>> offset_line(const Line& line, double offset, bool reverse = false);
extern OFFSET_API std::vector<std::unique_ptr<Path>> offset_arc(const Arc& source, double offset, bool reverse = false);
extern OFFSET_API std::vector<std::unique_ptr<Path>> offset_path(const Path& path, double offset, bool reverse = false);

extern OFFSET_API std::unique_ptr<Shape> buffer_line(const Line& line, double offset, buffer_extreme start, buffer_extreme end);
extern OFFSET_API std::unique_ptr<Shape> buffer_arc(const Arc& arc, double offset, buffer_extreme start, buffer_extreme end);
extern OFFSET_API std::unique_ptr<Shape> buffer_path(const Path& path, double offset, buffer_extreme start, buffer_extreme end);
extern OFFSET_API std::unique_ptr<Shape> buffer_paths(const std::vector<const Path*>& source, double offset, buffer_extreme start, buffer_extreme end);

}
}
