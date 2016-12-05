#include "stdafx.h"
#include "DxfWriter.h"
#include "Arc.h"
#include "Line.h"
#include "Path.h"
#include <set>
#include <fstream>
#include <map>
#include "g2d_math.h"

using namespace std;
using namespace osl;
using namespace g2d;

double toGrd(double angle)
{
	return angle * 57.295779513082320;
}

DxfWriter::DxfWriter(const wchar_t* filename)
	: filename(filename)
{
	items = unique_ptr<vector<unique_ptr<Item>>>(new vector<unique_ptr<Item>>());
}

DxfWriter::~DxfWriter()
{
	flush();
}

void DxfWriter::append(const Item& item, const wchar_t* id, int color)
{
	unique_ptr<Item> clone = item.Clone();
	layers[clone.get()] = wstring(id);
	colors[clone.get()] = color;
	items->push_back(move(clone));
}

void DxfWriter::header(wofstream& dxf) const
{
	dxf << 999 << endl;
	dxf << "DXF created from G2D" << endl;
	dxf << 0 << endl;
	dxf << "SECTION" << endl;
	dxf << 2 << endl;
	dxf << "HEADER" << endl;
	dxf << 9 << endl;
	dxf << "$ACADVER" << endl;
	dxf << 1 << endl;
	dxf << "AC1006" << endl;
	dxf << 9 << endl;
	dxf << "$INSBASE" << endl;
	dxf << 10 << endl;
	dxf << 0.0 << endl;
	dxf << 20 << endl;
	dxf << 0.0 << endl;
	dxf << 30 << endl;
	dxf << 0.0 << endl;
	dxf << 9 << endl;
	dxf << "$EXTMIN" << endl;
	dxf << 10 << endl;
	dxf << 0.0 << endl;
	dxf << 20 << endl;
	dxf << 0.0 << endl;
	dxf << 9 << endl;
	dxf << "$EXTMAX" << endl;
	dxf << 10 << endl;
	dxf << 1000.0 << endl;
	dxf << 20 << endl;
	dxf << 1000.0 << endl;
	dxf << 0 << endl;
	dxf << "ENDSEC" << endl;
}

void DxfWriter::tables(wofstream& dxf) const
{
	dxf << 0 << endl;
	dxf << "SECTION" << endl;
	dxf << 2 << endl;
	dxf << "TABLES" << endl;
	dxf << 0 << endl;
	dxf << "TABLE" << endl;
	dxf << 2 << endl;
	dxf << "LAYER" << endl;
	dxf << 70 << endl;
	dxf << 6 << endl;

	set<wstring> layer_strings;
	for (auto i = items->begin(); i != items->end(); ++i)
	{
		layer_strings.insert(layers.at((*i).get()));
	}

	int colorCounter = 0;
	for (auto l = layer_strings.begin(); l != layer_strings.end(); ++l)
	{
		dxf << 0 << endl;
		dxf << "LAYER" << endl;
		dxf << 2 << endl;
		dxf << *l << endl;
		dxf << 70 << endl;
		dxf << 0 << endl;
		dxf << 62 << endl;
		dxf << colorCounter++ << endl;
	}

	dxf << 0 << endl;
	dxf << "ENDTAB" << endl;
	dxf << 0 << endl;
	dxf << "ENDSEC" << endl;
}

void DxfWriter::blocks(wofstream& dxf) const
{
	dxf << 0 << endl;
	dxf << "SECTION" << endl;
	dxf << 2 << endl;
	dxf << "BLOCKS" << endl;
	dxf << 0 << endl;
	dxf << "ENDSEC" << endl;
}

void DxfWriter::entities(wofstream& dxf) const
{
	dxf << 0 << endl;
	dxf << "SECTION" << endl;
	dxf << 2 << endl;
	dxf << "ENTITIES" << endl;

	for (auto i = items->begin(); i != items->end(); ++i)
	{
		const Line* line = dynamic_cast<const Line*>((*i).get());
		if (line != nullptr)
		{
			write_line(dxf, layers.at((*i).get()), colors.at((*i).get()),
			           *line);
		}

		const g2d::Arc* arc = dynamic_cast<const g2d::Arc*>((*i).get());
		if (arc != nullptr)
		{
			write_arc(dxf, layers.at((*i).get()), colors.at((*i).get()), *arc);
		}

		const Path* path = dynamic_cast<const Path*>((*i).get());
		if (path != nullptr)
		{
			write_path(dxf, layers.at((*i).get()), colors.at((*i).get()),
			           *path);
		}
	}

	dxf << 0 << endl;
	dxf << "ENDSEC" << endl;
}

void DxfWriter::end(wofstream& dxf) const
{
	dxf << 0 << endl;
	dxf << "EOF";
}

void DxfWriter::flush() const
{
	// see: http://paulbourke.net/dataformats/dxf/min3d.html

	wofstream dxf(filename.c_str(), ios::out);

	header(dxf);
	tables(dxf);
	blocks(dxf);
	entities(dxf);
	end(dxf);

	dxf.close();
}

void DxfWriter::write_line(wofstream& dxf, const wstring& layer, int color,
                           const Line& line) const
{
	write_line(dxf, layer, color,
	           line.GetStartPoint().X, line.GetStartPoint().Y,
	           line.GetEndPoint().X, line.GetEndPoint().Y);
}

void DxfWriter::write_line(wofstream& dxf, const wstring& layer, int color,
                           double x1, double y1, double x2, double y2) const
{
	dxf << 0 << endl;
	dxf << "LINE" << endl;
	dxf << 8 << endl;
	dxf << layer << endl;
	dxf << 62 << endl;
	dxf << color << endl;
	dxf << 10 << endl;
	dxf << x1 << endl;
	dxf << 20 << endl;
	dxf << y1 << endl;
	dxf << 30 << endl;
	dxf << 0 << endl;
	dxf << 11 << endl;
	dxf << x2 << endl;
	dxf << 21 << endl;
	dxf << y2 << endl;
	dxf << 31 << endl;
	dxf << 0 << endl;
}

void DxfWriter::write_arc(wofstream& dxf, const wstring& layer, int color,
                          const g2d::Arc& arc) const
{
	double start_angle = arc.GetStartAngle();
	double end_angle = __normalize_angle(arc.GetStartAngle() +
	                                  arc.GetSubtendedAngle());
	if (arc.GetSubtendedAngle() < 0)
	{
		start_angle = end_angle;
		end_angle = arc.GetStartAngle();
	}

	write_arc(dxf, layer, color, arc.GetCenter().X, arc.GetCenter().Y,
	          arc.GetRadius(), toGrd(start_angle), toGrd(end_angle));
}

void DxfWriter::write_arc(wofstream& dxf, const wstring& layer, int color,
                          double cx, double cy, double radius,
                          double start, double end) const
{
	dxf << 0 << endl;
	dxf << "ARC" << endl;
	dxf << 8 << endl;
	dxf << layer << endl;
	dxf << 62 << endl;
	dxf << color << endl;
	dxf << 10 << endl;
	dxf << cx << endl;
	dxf << 20 << endl;
	dxf << cy << endl;
	dxf << 30 << endl;
	dxf << 0 << endl;
	dxf << 40 << endl;
	dxf << radius << endl;
	dxf << 50 << endl;
	dxf << start << endl;
	dxf << 51 << endl;
	dxf << end << endl;
	dxf << 31 << endl;
	dxf << 0 << endl;
}

void DxfWriter::write_path(wofstream& dxf, const wstring& layer, int color,
                           const Path& path) const
{
	for (unsigned int j = 0; j < path.size(); ++j)
	{
		const Line* p_line = dynamic_cast<const Line*>(path.at(j).get());
		if (p_line != nullptr)
		{
			write_line(dxf, layer, color, *p_line);
		}

		const g2d::Arc* p_arc = dynamic_cast<const g2d::Arc*>(path.at(j).get());
		if (p_arc != nullptr)
		{
			write_arc(dxf, layer, color, *p_arc);
		}
	}
}