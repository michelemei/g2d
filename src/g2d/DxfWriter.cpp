#include "stdafx.h"
#include "DxfWriter.h"
#include "Arc.h"
#include "Line.h"
#include "Path.h"
#include "Shape.h"
#include <set>
#include <string>
#include <fstream>
#include <map>
#include "g2d_math.h"
#include <assert.h>

using namespace std;
using namespace osl;
using namespace g2d;

double toGrd(double angle)
{
	return angle * 57.295779513082320;
}

struct DxfWriter::DxfWriterAttributes
{
	wstring filename;
	unique_ptr<vector<unique_ptr<Item>>> items;
	map<const Item*, wstring> layers;
	map<const Item*, int> colors;
};

DxfWriter::DxfWriter(const wchar_t* filename)
	: attributes(new DxfWriterAttributes())
{
	attributes->filename = filename;
	attributes->items = unique_ptr<vector<unique_ptr<Item>>>(new vector<unique_ptr<Item>>());
}

DxfWriter::~DxfWriter()
{
	flush();
	delete attributes;
}

void DxfWriter::append(const Item& item, const wchar_t* id, int color)
{
	unique_ptr<Item> clone = item.Clone();
	attributes->layers[clone.get()] = wstring(id);
	attributes->colors[clone.get()] = color;
	attributes->items->push_back(move(clone));
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
	for (auto i = attributes->items->begin(); i != attributes->items->end(); ++i)
	{
		layer_strings.insert(attributes->layers.at((*i).get()));
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

void DxfWriter::end(wofstream& dxf) const
{
	dxf << 0 << endl;
	dxf << "EOF";
}

void DxfWriter::flush() const
{
	// see: http://paulbourke.net/dataformats/dxf/min3d.html

	wofstream dxf(attributes->filename.c_str(), ios::out);

	header(dxf);
	tables(dxf);
	blocks(dxf);
	entities(dxf);
	end(dxf);

	dxf.close();
}

void write_line(wofstream& dxf, const wstring& layer, int color, double x1, double y1, double x2, double y2)
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

void write_arc(wofstream& dxf, const wstring& layer, int color,
                          double cx, double cy, double radius,
                          double start, double end)
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

void write_arc(wofstream& dxf, const wstring& layer, int color, const g2d::Arc& arc)
{
	double start_angle = arc.GetStartAngle();
	double end_angle = normalize_angle(arc.GetStartAngle() +
	                                  arc.GetSubtendedAngle());
	if (arc.GetSubtendedAngle() < 0)
	{
		start_angle = end_angle;
		end_angle = arc.GetStartAngle();
	}

	write_arc(dxf, layer, color, arc.GetCenter().X, arc.GetCenter().Y,
	          arc.GetRadius(), toGrd(start_angle), toGrd(end_angle));
}

void write_line(wofstream& dxf, const wstring& layer, int color, const Line& line)
{
	write_line(dxf, layer, color,
	           line.GetStartPoint().X, line.GetStartPoint().Y,
	           line.GetEndPoint().X, line.GetEndPoint().Y);
}


void write_path(wofstream& dxf, const wstring& layer, int color, const Path& path)
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

void write_shape(wofstream& dxf, const wstring& layer, int color, const Shape& shape)
{
	for (auto p = shape.GetPaths()->begin(); p != shape.GetPaths()->end(); ++p)
	{
		write_path(dxf, layer, color, *p->get());
	}
}

void DxfWriter::entities(wofstream& dxf) const
{
	dxf << 0 << endl;
	dxf << "SECTION" << endl;
	dxf << 2 << endl;
	dxf << "ENTITIES" << endl;

	for (auto i = attributes->items->begin(); i != attributes->items->end(); ++i)
	{
		const Line* line = dynamic_cast<const Line*>((*i).get());
		if (line != nullptr)
		{
			write_line(dxf, attributes->layers.at((*i).get()), attributes->colors.at((*i).get()),
			           *line);
			continue;
		}

		const g2d::Arc* arc = dynamic_cast<const g2d::Arc*>((*i).get());
		if (arc != nullptr)
		{
			write_arc(dxf, attributes->layers.at((*i).get()), attributes->colors.at((*i).get()), *arc);
			continue;
		}

		const Path* path = dynamic_cast<const Path*>((*i).get());
		if (path != nullptr)
		{
			write_path(dxf, attributes->layers.at((*i).get()), attributes->colors.at((*i).get()), *path);
			continue;
		}

		const Shape* shape = dynamic_cast<const g2d::Shape*>((*i).get());
		if (shape != nullptr)
		{
			write_shape(dxf, attributes->layers.at((*i).get()), attributes->colors.at((*i).get()), *shape);
			continue;
		}

		assert(false);
	}

	dxf << 0 << endl;
	dxf << "ENDSEC" << endl;
}