#include "stdafx.h"
#include "Vector.h"
#include "string.h"
namespace Application {
	Vector::Vector(int kol) :SZ(0), znach(nullptr){
		int i;
		if (kol > 0){
			SZ = kol;
			znach = new char[kol+1];
			for (i = 0; i < kol; ++i)
				znach[i] = 'x'; 
			znach[i] = '\0';
		}
		else
			throw std::exception("wrong kol");
	}
	Vector::Vector(char* str):SZ(0), znach(nullptr){
		if (str != NULL) {
			SZ =strlen(str) ;
			znach = new char[SZ+1];
			int i = 0;
			while (*str != '\0') { 
				if ((*str != '0') && (*str != '1') && (*str != 'x')) {
					throw std::exception("wrong znach");
					break;
				}
				znach[i] = *str;
				++i;
				++str;
			}
			znach[i] = '\0';
		}
	}
	Vector::Vector(const Vector &v) :SZ(v.SZ), znach(new char[v.SZ+1]) {
		int i;
		for (i = 0; i < v.SZ; ++i)
			znach[i] = v.znach[i];
		znach[i] = '\0';
	}
	Vector::Vector(Vector &&v) : SZ(v.SZ), znach(v.znach) {
		v.znach = nullptr;
	}
	Vector::Vector(const Vector &v, int size) {
		int i;
		if (v.SZ == size) {
			SZ = size;
			znach = new char[SZ+1];
			for (i = 0; i < SZ; ++i)
				znach[i] = v.znach[i];
			znach[i] = '\0';
		}
		else {
			SZ = size;
			znach = new char[SZ+1];
			for (i = 0; i < v.SZ; ++i)
				znach[i] = v.znach[i];
			for (i = v.SZ; i < SZ; ++i)
				znach[i] = 'x';
			znach[i] = '\0';
		}
	}
	Vector& Vector::operator=(const Vector &v) {
		int i;
		if (this != &v) {
			SZ = v.SZ;
			delete[]znach;
			znach = new char[SZ+1];
			for (i = 0; i < SZ; ++i)
				znach[i] = v.znach[i];
			znach[i] = '\0';
		}
		return *this;
	}
	Vector & Vector::operator=(Vector &&v) {
		int n = SZ;
		SZ = v.SZ;
		v.SZ = n;
		char* s = znach;
		znach = v.znach;
		v.znach = s;
		return(*this);
	}
	std::istream & Vector::input(std::istream &s) {
		char buf[100];
		s >> buf;
		*this = Vector(buf);
		return s;
	}
	std::ostream  & Vector::output(std::ostream &s) {
		for (int i = 0; i < SZ; ++i)
			s << znach[i];
		s << std::endl;
		return s;
	}
    const Vector operator+(const Vector &v1,const Vector &v2){
		int len = v1.SZ > v2.SZ ? v1.SZ : v2.SZ;
		Vector vres(v1, len), vv2(v2, len);
		for (int i = 0; i < vres.SZ; ++i) {
			if (vres.znach[i] == '0'&&vv2.znach[i] == '0')
				vres.znach[i] = '0';
			else
			if (vres.znach[i] == '1'&&vv2.znach[i] == '1')
				vres.znach[i] = '1';
			else
			if ((vres.znach[i] == '0'&&vv2.znach[i] == '1') || (vres.znach[i] == '1'&&vv2.znach[i] == '0'))
				vres.znach[i] = '1';
			else
			if ((vres.znach[i] == '0'&&vv2.znach[i] == 'x') || (vres.znach[i] == 'x'&&vv2.znach[i] == '0'))
				vres.znach[i] = 'x';
			else
			if ((vres.znach[i] == 'x'&&vv2.znach[i] == '1') || (vres.znach[i] == '1'&&vv2.znach[i] == 'x'))
				vres.znach[i] = '1';
		}
		return vres;
	}
	 const Vector operator*(const Vector &v1,const Vector &v2) {
		int len = v1.SZ > v2.SZ ? v1.SZ : v2.SZ;
		Vector vres(v1, len), vv2(v2, len);
		for (int i = 0; i < vres.SZ; ++i) {
			if (vres.znach[i] == '0'&&vv2.znach[i] == '0')
				vres.znach[i] = '0';
			if (vres.znach[i] == '1'&&vv2.znach[i] == '1')
				vres.znach[i] = '1';
			if ((vres.znach[i] == '0'&&vv2.znach[i] == '1') || (vres.znach[i] == '1'&&vv2.znach[i] == '0'))
				vres.znach[i] = '0';
			if ((vres.znach[i] == '0'&&vv2.znach[i] == 'x') || (vres.znach[i] == 'x'&&vv2.znach[i] == '0'))
				vres.znach[i] = '0';
			if ((vres.znach[i] == 'x'&&vv2.znach[i] == '1') || (vres.znach[i] == '1'&&vv2.znach[i] == 'x'))
				vres.znach[i] = 'x';
		}
		return vres;
	}
	const int operator-(const Vector &v1,const Vector &v2) {
		int len = v1.SZ > v2.SZ ? v1.SZ : v2.SZ;
		Vector vv1(v1, len), vv2(v2, len);
		for (int i = 0; i < vv1.SZ; ++i) {
			if (((vv1.znach[i] == 'x') && (vv2.znach[i] == '0')) || ((vv1.znach[i] == '1') && (vv2.znach[i] == 'x')) || ((vv1.znach[i] == '1') && (vv2.znach[i] == '0')))
				return 0;
			else
			if (((vv2.znach[i] == 'x') && (vv1.znach[i] == '0')) || ((vv2.znach[i] == '1') && (vv1.znach[i] == 'x')) || ((vv2.znach[i] == '1') && (vv1.znach[i] == '0')))
				return 1;
		}
		return 2;
	}
	Vector& Vector::operator~() {
		int i;
		for (i = 0; i < SZ; ++i) {
			if (znach[i] == '0')
				znach[i] = '1';
			else {
				if (znach[i] == '1')
					znach[i] = '0';
				if (znach[i] == 'x')
					znach[i] = 'x';
			}
		}
		znach[i] = '\0';
		return (*this);
	}
	int Vector::Analysis() {
		for (int i = 0; i < SZ; ++i)
			if (znach[i] == 'x')
				return 1;
		return 0;
	}
}


