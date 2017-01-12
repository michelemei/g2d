#include "stdafx.h"
#include <vector>
#include <memory>
#include <Path.h>
#include <Line.h>
#include <Arc.h>
#include <Shape.h>
#include <sstream>
#include "DxfWriter.h"
#include <offset.h>
#include "clipper.hpp"
//#include "timekeeper.h"
#include "DxfReader.h"

using namespace std;
using namespace osl::g2d;

const wchar_t* dxf_repository = L"C:\\temp\\";

#define _USE_MATH_DEFINES
#include <math.h>

void populate_test(vector<unique_ptr<Path>>& paths)
{
	// 001
	Path* p001 = new Path(unique_ptr<Line>(new Line(Point(10.0, 10.0), Point(10.0, 110.0))));
	p001->push_back(unique_ptr<Arc>(new Arc(Point(10.0, 110.0), Point(20.0, 50.0), Point(15.0,80.0), false)));
	p001->push_back(unique_ptr<Line>(new Line(Point(20.0, 50.0), Point(50.0, 10.0))));
	paths.push_back(unique_ptr<Path>(p001));

	// 002
	Path* p002 = new Path(unique_ptr<Arc>(new Arc(Point(2.0, 30.0), Point(-2.0, 30.0), Point(0.0, 0.0), false)));
	paths.push_back(unique_ptr<Path>(p002));

	// 003
	Path* p003 = new Path(unique_ptr<Line>(new Line(Point(0.0, 0.0), Point(0.0, 100.0))));
	p003->push_back(unique_ptr<Arc>(new Arc(Point(0.0, 100.0), Point(80.0, 100.0), Point(40.0, 100.0), false)));
	paths.push_back(unique_ptr<Path>(p003));

	// 004
	Path* p004 = new Path(unique_ptr<Line>(new Line(Point(0.0, 0.0), Point(0.0, 100.0))));
	p004->push_back(unique_ptr<Arc>(new Arc(Point(0.0, 100.0), Point(80.0, 100.0), Point(40.0, 100.0), true)));
	paths.push_back(unique_ptr<Path>(p004));

	// 005
	Path* p005 = new Path(unique_ptr<Arc>(new Arc(Point(0.0, 0.0), 20.0, M_PI / 4, M_PI / 2, true)));
	p005->push_back(unique_ptr<Line>(new Line(Point(0.0, 20.0), Point(0.0, -50.0))));
	paths.push_back(unique_ptr<Path>(p005));

	// 006
	Path* p006 = new Path(unique_ptr<Arc>(new Arc(Point(0.0, 0.0), 20.0, M_PI / 4, M_PI / 2, false)));
	p006->push_back(unique_ptr<Line>(new Line(Point(0.0, 20.0), Point(0.0, -50.0))));
	paths.push_back(unique_ptr<Path>(p006));

	// 007
	Path* p007 = new Path(unique_ptr<Line>(new Line(Point(-20.0, 0.0), Point(-2.0, 50.0))));
	p007->push_back(unique_ptr<Line>(new Line(Point(-2.0, 50.0), Point(2.0, 50.0))));
	p007->push_back(unique_ptr<Line>(new Line(Point(2.0, 50.0), Point(20.0, 0.0))));
	paths.push_back(unique_ptr<Path>(p007));

	// 008
	Path* p008 = new Path(unique_ptr<Line>(new Line(Point(0.0, 0.0), Point(30.0, 100.0))));
	p008->push_back(unique_ptr<Line>(new Line(Point(30.0, 100.0), Point(60.0, 0.0))));
	p008->push_back(unique_ptr<Line>(new Line(Point(60.0, 0.0), Point(45.0, 50.0))));
	p008->push_back(unique_ptr<Line>(new Line(Point(45.0, 50.0), Point(0.0, 50.0))));
	paths.push_back(unique_ptr<Path>(p008));
}

void export_originals()
{
	vector<unique_ptr<Path>> paths;
	populate_test(paths);

	for (unsigned int p = 0; p < paths.size(); ++p)
	{
		wstringstream name;
		if (p < 9)
			name << L"00";
		else if (p < 99)
			name << L"0";
		name << (p + 1);
		wstringstream filename;
		wstring dxf_repository_string(dxf_repository);
		filename << dxf_repository_string;
		filename << name.str() << ".dxf";

		osl::DxfWriter dxf(filename.str().c_str());
		dxf.append(*paths[p].get(), L"original", 0);
	}
}

void execute_offset()
{
	vector<unique_ptr<Path>> paths;
	populate_test(paths);

	vector<double> offset_values;
	offset_values.push_back(-13.0);
	//offset_values.push_back(-8.0);
	//offset_values.push_back(-5.0);
	//offset_values.push_back(-3.0);
	//offset_values.push_back(-2.0);
	//offset_values.push_back(-1.0);
	//offset_values.push_back(1.0);
	//offset_values.push_back(2.0);
	//offset_values.push_back(3.0);
	//offset_values.push_back(5.0);
	//offset_values.push_back(8.0);
	offset_values.push_back(13.0);

	for (unsigned int p = 0; p < paths.size(); ++p)
	{
		wstringstream name;
		if (p < 9)
			name << L"00";
		else if (p < 99)
			name << L"0";
		name << (p + 1);

		wstringstream filename;
		wstring dxf_repository_string(dxf_repository);
		filename << dxf_repository_string;
		filename << L"offset_" << name.str() << ".dxf";

		osl::DxfWriter dxf(filename.str().c_str());
		dxf.append(*paths[p].get(), L"input", 0);
		for (unsigned int v = 0; v < offset_values.size(); ++v)
		{
			auto offset = offset_path(*paths[p].get(), offset_values[v]);
			for (auto k = offset.begin(); k != offset.end(); ++k)
			{
				wstringstream ss;
				ss << L"offset_" << offset_values[v];
				int color = offset_values[v] > 0 ? int(140 + offset_values[v]) : int(10 - offset_values[v]);
				dxf.append(**k, ss.str().c_str(), color);
			}
		}
	}
}

void execute_offset_normal()
{
	vector<unique_ptr<Path>> paths;
	populate_test(paths);

	vector<double> offset_values;
	offset_values.push_back(-13.0);
	//offset_values.push_back(-8.0);
	//offset_values.push_back(-5.0);
	//offset_values.push_back(-3.0);
	//offset_values.push_back(-2.0);
	//offset_values.push_back(-1.0);
	//offset_values.push_back(1.0);
	//offset_values.push_back(2.0);
	//offset_values.push_back(3.0);
	//offset_values.push_back(5.0);
	//offset_values.push_back(8.0);
	offset_values.push_back(13.0);

	for (unsigned int p = 0; p < paths.size(); ++p)
	{
		wstringstream name;
		if (p < 9)
			name << L"00";
		else if (p < 99)
			name << L"0";
		name << (p + 1);

		wstringstream filename;
		wstring dxf_repository_string(dxf_repository);
		filename << dxf_repository_string;
		filename << L"offset_normal_" << name.str() << ".dxf";

		osl::DxfWriter dxf(filename.str().c_str());
		dxf.append(*paths[p].get(), L"input", 0);
		for (unsigned int v = 0; v < offset_values.size(); ++v)
		{
			auto offset = offset_path_normal(*paths[p].get(), offset_values[v]);

			wstringstream ss;
			ss << L"offset_" << offset_values[v];
			int color = offset_values[v] > 0 ? int(140 + offset_values[v]) : int(10 - offset_values[v]);
			dxf.append(*offset.get(), ss.str().c_str(), color);
			
		}
	}
}

void execute_buffer()
{
	vector<unique_ptr<Path>> paths;
	populate_test(paths);

	vector<double> offset_values;
	offset_values.push_back(-13.0);
	//offset_values.push_back(-8.0);
	//offset_values.push_back(-5.0);
	//offset_values.push_back(-3.0);
	//offset_values.push_back(-2.0);
	//offset_values.push_back(-1.0);
	//offset_values.push_back(1.0);
	//offset_values.push_back(2.0);
	//offset_values.push_back(3.0);
	//offset_values.push_back(5.0);
	//offset_values.push_back(8.0);
	offset_values.push_back(13.0);

	for (unsigned int p = 0; p < paths.size(); ++p)
	{
		wstringstream name;
		if (p < 9)
			name << L"00";
		else if (p < 99)
			name << L"0";
		name << (p + 1);

		wstringstream filename;
		wstring dxf_repository_string(dxf_repository);
		filename << dxf_repository_string;
		filename << L"buffer_" << name.str() << ".dxf";

		osl::DxfWriter dxf(filename.str().c_str());
		dxf.append(*paths[p].get(), L"input", 0);
		for (unsigned int v = 0; v < offset_values.size(); ++v)
		{
			auto buffer = buffer_path(*paths[p].get(), offset_values[v], be_round, be_round);
			for (auto k = buffer->GetPaths()->begin(); k != buffer->GetPaths()->end(); ++k)
			{
				wstringstream ss;
				ss << L"buffer_" << offset_values[v];
				int color = offset_values[v] > 0 ? int(140 + offset_values[v]) : int(10 - offset_values[v]);
				dxf.append(**k, ss.str().c_str(), color);
			}
		}
	}
}

#pragma region clipper

double toRad(double angle)
{
	return angle * 0.01745329251994329576;
}

void read_dxf(const wchar_t* filename, vector<const Path*>& paths)
{
	osl::DxfReader reader(filename);

	vector<unique_ptr<Oriented>> items;
	map<unsigned int, string> values;
	while (reader.GetNextEntity(values))
	{
		if (values[0].compare("LINE") == 0)
		{
			Line* line = new Line(Point(atof(values[10].c_str()), atof(values[20].c_str())),
			                      Point(atof(values[11].c_str()), atof(values[21].c_str())));
			items.push_back(unique_ptr<Line>(line));
		}
		else if (values[0].compare("ARC") == 0)
		{
			Arc* arc = new Arc(Point(atof(values[10].c_str()), atof(values[20].c_str())),
			                   atof(values[40].c_str()),
			                   toRad(atof(values[50].c_str())), toRad(atof(values[51].c_str())), true);
			items.push_back(unique_ptr<Arc>(arc));
		}
	}
	Path::IsConsecutive(items);
	paths.push_back(new Path(items));

	osl::DxfWriter writer(L"C:\\temp\\compare_copy.dxf");
	for (auto p = paths.begin(); p != paths.end(); ++p)
		writer.append(**p);
}

#define CLIPPER_FACTOR 1000
#define CLIPPER_FACTOR1 0.001

ClipperLib::cInt toClipper(double d)
{
	if (d < 0.0)
	{
		return ceil(d) - d < 0.5 ? ClipperLib::cInt(ceil(d)) : ClipperLib::cInt(floor(d));
	}
	return d - floor(d) < 0.5 ? ClipperLib::cInt(floor(d)) : ClipperLib::cInt(ceil(d));
}

ClipperLib::IntPoint toClipper(const Point& point)
{
	return ClipperLib::IntPoint(toClipper(point.X * CLIPPER_FACTOR), toClipper(point.Y * CLIPPER_FACTOR));
}

void discretize(const Path& path, vector<ClipperLib::IntPoint>& clipper_points, double chordalTollerance)
{
	for (unsigned int i = 0; i < path.size(); ++i)
	{
		const Line* line = dynamic_cast<const Line*>(path.at(i).get());
		if (line != nullptr)
		{
			clipper_points.push_back(toClipper(line->GetStartPoint()));
			if (i == path.size() - 1)
				clipper_points.push_back(toClipper(line->GetEndPoint()));
		}

		const Arc* arc = dynamic_cast<const Arc*>(path.at(i).get());
		if (arc != nullptr)
		{
			vector<Point> arc_points = arc->Discretize(chordalTollerance);
			vector<ClipperLib::IntPoint> arc_points_c;
			for (auto p = arc_points.begin(); p != arc_points.end(); ++p)
				arc_points_c.push_back(toClipper(*p));

			if (i == path.size() - 1)
				clipper_points.insert(clipper_points.end(), arc_points_c.begin(), arc_points_c.end());
			else
				clipper_points.insert(clipper_points.end(), arc_points_c.begin(), arc_points_c.end() - 1);
		}
	}
}

void execute_clipper(const vector<const Path*>& paths, double offset)
{
	ClipperLib::ClipperOffset clipperOffset;

	ClipperLib::Path clipper_points;
	for (auto p = paths.begin(); p != paths.end(); ++p)
		discretize(**p, clipper_points, 0.01);

	clipperOffset.AddPath(clipper_points, ClipperLib::jtRound, ClipperLib::etOpenRound);

	ClipperLib::Paths solution;
	//osl::timekeeper timekeeper;
	clipperOffset.Execute(solution, offset * CLIPPER_FACTOR);
	//printf("clipper: %llu\n", timekeeper.get_milliseconds());

	vector<Line> lines;
	for (auto p = solution.begin(); p != solution.end(); ++p)
	{
		for (unsigned int i = 0; i < (*p).size() - 1; ++i)
		{
			lines.push_back(Line(Point((*p)[i].X * CLIPPER_FACTOR1, (*p)[i].Y * CLIPPER_FACTOR1),
				Point((*p)[i + 1].X * CLIPPER_FACTOR1, (*p)[i + 1].Y * CLIPPER_FACTOR1)));
		}
		lines.push_back(Line(Point((*p)[(*p).size() - 1].X * CLIPPER_FACTOR1, (*p)[(*p).size() - 1].Y * CLIPPER_FACTOR1),
		                     Point((*p)[0].X * CLIPPER_FACTOR1, (*p)[0].Y * CLIPPER_FACTOR1)));
	}

	osl::DxfWriter clipper_result(L"C:\\temp\\clipper_result.dxf");
	for (auto l = lines.begin(); l != lines.end(); ++l)
		clipper_result.append(*l);
}

void execute_osl(const vector<const Path*>& paths, double offset)
{
	unique_ptr<Shape> buffer = buffer_paths(paths, offset, be_round, be_round);
	osl::DxfWriter osl_result(L"C:\\temp\\osl_result.dxf");
	osl_result.append(*buffer);
}

#pragma endregion 

void help()
{
	printf("Offset Visual Test");
	printf("Usage:\n");
	printf(" -web [path]   Performs all visual tests and export the results in path\n");
	printf(" -clipper_arc  Running the comparative test with clipper with arcs");
	printf(" -clipper_line Running the comparative test with clipper with lines");
	printf(" -help         Print this help");
}

int _tmain(int argc, _TCHAR* argv[])
{
	//int nRetVal = 0;
	//bool defRetVal = nRetVal == 0 ? false : true;
	//bool pippo;
	//for (pippo = false; nRetVal != false && pippo == false; pippo = true){}

	if (argc < 2)
	{
		help();
		return -1;
	}

	wstring command(argv[1]);
	if (command.compare(L"-web") == 0)
	{
		export_originals();
		execute_offset();
		execute_offset_normal();
		execute_buffer();
	}
	else if (command.compare(L"-clipper_arc") == 0)
	{
		vector<const Path*> paths;
		read_dxf(L"C:\\temp\\compare.dxf", paths);

		execute_clipper(paths, 2);
		execute_osl(paths, 2);
	}
	else if (command.compare(L"-clipper_line") == 0)
	{
		vector<const Path*> paths;
		read_dxf(L"C:\\temp\\compare.dxf", paths);

		execute_clipper(paths, 2);
		execute_osl(paths, 2);
	}
	else
	{
		help();
	}

	return 0;
}

#undef _USE_MATH_DEFINES
