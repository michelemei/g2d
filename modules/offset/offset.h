#ifndef __osl_g2d_offset_h
#define __osl_g2d_offset_h

#include "offset_exports.h"
#include "offset_enum.h"
#include <memory>
#include <vector>

namespace osl {
namespace g2d {

class Arc;
class Line;
class Path;
class Shape;

extern OFFSET_API std::unique_ptr<Line> offset_line(const Line& line,
	double offset, bool reverse = false);
extern OFFSET_API std::unique_ptr<Arc> offset_arc(const Arc& source, double offset, bool reverse = false);
extern OFFSET_API std::vector<std::unique_ptr<Path>> offset_path(const Path& path, double offset, bool reverse = false);
extern OFFSET_API std::unique_ptr<Path> offset_path_normal(const Path& path, double offset, bool reverse = false);

extern OFFSET_API std::unique_ptr<Shape> buffer_line(const Line& line, double offset, buffer_extreme start, buffer_extreme end);
extern OFFSET_API std::unique_ptr<Shape> buffer_arc(const Arc& arc, double offset, buffer_extreme start, buffer_extreme end);
extern OFFSET_API std::unique_ptr<Shape> buffer_path(const Path& path, double offset, buffer_extreme start, buffer_extreme end);
extern OFFSET_API std::unique_ptr<Shape> buffer_paths(const std::vector<const Path*>& source, double offset, buffer_extreme start, buffer_extreme end);

}
}
#endif