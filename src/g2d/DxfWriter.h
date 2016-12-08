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
#ifndef __osl_g2d_dxfwriter_h
#define __osl_g2d_dxfwriter_h

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

#endif