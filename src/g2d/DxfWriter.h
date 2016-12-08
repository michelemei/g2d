#pragma once
#include "g2d_exports.h"
#include <string>
#include <map>
#include <vector>
#include <memory>

namespace osl {
namespace g2d {
	class Item;
	class Path;
	class Arc;
	class Line;
}

class G2D_API DxfWriter
{
	std::wstring filename;
	std::unique_ptr<std::vector<std::unique_ptr<g2d::Item>>> items;
	std::map<const g2d::Item*, std::wstring> layers;
	std::map<const g2d::Item*, int> colors;

public:
	explicit DxfWriter(const wchar_t* filename);

	~DxfWriter();

	void append(const g2d::Item& item, const wchar_t* id = L"0",
	            int color = 0);

private:
	void write_line(std::wofstream& dxf, const std::wstring& layer, int color,
	                const g2d::Line& line) const;

	void write_line(std::wofstream& dxf, const std::wstring& layer, int color,
	                double x1, double y1, double x2, double y2) const;

	void write_arc(std::wofstream& dxf, const std::wstring& layer, int color,
	               const g2d::Arc& arc) const;

	void write_arc(std::wofstream& dxf, const std::wstring& layer, int color,
	               double cx, double cy, double radius,
	               double start, double end) const;

	void write_path(std::wofstream& dxf, const std::wstring& layer, int color,
	                const g2d::Path& path) const;

	void header(std::wofstream& dxf) const;

	void tables(std::wofstream& dxf) const;

	void blocks(std::wofstream& dxf) const;

	void entities(std::wofstream& dxf) const;

	void end(std::wofstream& dxf) const;

	void flush() const;
};
}