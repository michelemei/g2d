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

using namespace std;
using namespace osl::g2d;

const wchar_t* dxf_repository = L"C:\\temp\\";

#define _USE_MATH_DEFINES
#include <math.h>

void populate_test(vector<unique_ptr<Path>>& paths)
{
	// 001
	Path* p001 = new Path(unique_ptr<Line>(new Line(Point(10.0, 10.0), Point(10.0, 110.0))));
	p001->push_back(unique_ptr<Line>(new Line(Point(10.0, 110.0), Point(60.0, 90.0))));
	p001->push_back(unique_ptr<Line>(new Line(Point(60.0, 90.0), Point(20.0, 50.0))));
	p001->push_back(unique_ptr<Line>(new Line(Point(20.0, 50.0), Point(60.0, 10.0))));
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

void execute_offset()
{
	vector<unique_ptr<Path>> paths;
	populate_test(paths);

	vector<double> offset_values;
	offset_values.push_back(1.0);
	offset_values.push_back(2.0);
	offset_values.push_back(3.0);
	offset_values.push_back(4.0);
	offset_values.push_back(5.0);
	offset_values.push_back(6.0);
	offset_values.push_back(7.0);
	offset_values.push_back(8.0);
	offset_values.push_back(9.0);
	offset_values.push_back(10.0);
	offset_values.push_back(15.0);

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
				dxf.append(**k, ss.str().c_str(), 140 + v);
			}
		}
	}
}

void execute_buffer()
{
	vector<unique_ptr<Path>> paths;
	populate_test(paths);

	vector<double> offset_values;
	offset_values.push_back(1.0);
	offset_values.push_back(2.0);
	offset_values.push_back(3.0);
	offset_values.push_back(4.0);
	offset_values.push_back(5.0);
	offset_values.push_back(6.0);
	offset_values.push_back(7.0);
	offset_values.push_back(8.0);
	offset_values.push_back(9.0);
	offset_values.push_back(10.0);
	offset_values.push_back(15.0);

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
				dxf.append(**k, ss.str().c_str(), 140 + v);
			}
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	execute_offset();
	execute_buffer();
	return 0;
}

#undef _USE_MATH_DEFINES
