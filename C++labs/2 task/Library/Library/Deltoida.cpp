#include "stdafx.h"
#include "Deltoida.h"
#include <strstream>
#include <stdio.h>
#include <string.h>
namespace Application {
	Deltoida
		::Deltoida(double rad) :p(0, 0) {
		if (rad < 0)
			throw std::exception("Invalid radius");
		r = rad;
	}
	Deltoida::Deltoida(const Point& p0, double rad) : p(p0) {
		if (rad < 0) 
			throw std::exception("Invalid radius");
		r = rad;
	}
	Deltoida::Deltoida(double x0,double y0,double rad) : p(x0, y0) {
		if (rad < 0)
			throw std::exception("Invalid radius");
		r = rad;
	}
	Deltoida& Deltoida::SetR(double r0) {
		if (r0<0)
			throw std::exception("Invalid radius");
		r = r0;
		return *this;
	}


	Point Deltoida::coordinates(double t) {
		Point res;
		res.x= 2 * r*cos(t) + r*cos(2 * t);
		res.y= 2 * r*sin(t) - r*sin(2 * t);
		return res;
	}
	char *Deltoida::frm() const {
		char* s1 = "x=2* *cos(t)+ *cos(2*t);y=2* *sin(t)- *sin(2*t)";
		int l = strlen(s1) + 1;
		size_t size = 20;
		char num[20];
		sprintf_s(num, 20, "%.2f", r);
		l += strlen(num);
		sprintf_s(num, 20, "%.2f", r);
		l += strlen(num);
		sprintf_s(num, 20, "%.2f", r);
		l += strlen(num);
		sprintf_s(num, 20, "%.2f", r);
		l += strlen(num);
		char *s = new char[l];
		sprintf_s(s, l, "x=2*%.2f*cos(t)", r);
		int k = strlen(s);
		sprintf_s(s + k, l - k, "+%.2f*cos(2*t);", r);
		k = strlen(s);
		sprintf_s(s + k, l - k, "y=2*%.2f*sin(t)", r);
		k = strlen(s);
		sprintf_s(s + k, l - k, "-%.2f*sin(2*t)\n", r);
		return s;
	}
}
