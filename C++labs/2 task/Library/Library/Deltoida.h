#pragma once
#ifndef _DELTOIDA_H_
#define _DELTOIDA_H_
//#include "gtest\gtest_prod.h"
#include <math.h>
namespace Application {
	struct Point {
		double x, y;
		Point(double x0 = 0, double y0 = 0) :x(x0), y(y0) {}
	};
	class Deltoida {
	private:
		Point p;
		double r;
	public:
		Deltoida(double rad = 1);
		Deltoida(const Point &p0, double rad = 1);
		Deltoida(double x0, double y0, double rad = 1);
		Deltoida &SetP(const Point &p0) { p = p0; return *this; };
		Deltoida &SetR(double r0);
		Point GetP() const { return p; };
		double GetR() const { return r; };
		double lenght1() const { return 4 * r/3; };//длина пересечения дельтоиды с касательной
		double lenght2() const { return 16 * r/3 ; };//длина кривой
		double area() const { return 3.14159 * 2 * r*r/9; };
		Point coordinates(double t); 
		char* frm() const;
	};
}
#endif

	