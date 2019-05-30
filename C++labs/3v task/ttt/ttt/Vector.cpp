
#include "Vector.h"
#include <string.h>
namespace Application {
	Vector::Vector(int kol) :n(kol) {
		for (int i = 0; i < n; ++i)
			znach[i] = 'x';
	}
	Vector::Vector(char* str) {
		if (str == NULL) {
			Vector();
			throw std::exception("vector is nullptr");
			//Vector();
		}
		else {
			n = 0;
			while (*str != '\0') {
				if (n > 10) {
					Vector();
					throw std::exception("size of vector is >10");
					//std::cout << "size of vector is >10"<< std::endl;
					//Vector() ;
					break;
				}
				if ((*str != '0') || (*str != '1') || (*str != 'x')) {
					Vector();
					throw std::exception("wrong znach");
					//std::cout << "wrong znach"<< std::endl;
					//Vector();
					break;
				}
				znach[n] = *str;
				++str;
				++n;
			}
		}
	}
	std::istream & Vector::input(std::istream &s) {
		char buf[10];
		s >> buf;
		*this=Vector(buf);
		return s;
	}
	std::ostream  & Vector::output(std::ostream &s) {
		for (int i = 0; i < n; ++i)
			s << znach[i];
		s << std::endl;
		return s;
	}
	Vector Vector::Operation1(const Vector &v2) {
		Vector vres(*this), vv2(v2);
			if (vres.n > vv2.n) {			
				for (int i = vv2.n; i < n; ++i)
					vv2.znach[i] = 'x';
				vv2.n = n;
			}
			if (vv2.n > vres.n) {
				for (int i = n; i < vv2.n; ++i)
					vres.znach[i] = 'x';
				vres.n = v2.n;
		   }
		for (int i = 0; i < n; ++i) {
			if (vres.znach[i] == '0'&&vv2.znach[i] == '0')
				vres.znach[i] = '0';
			if (vres.znach[i] == '1'&&vv2.znach[i] == '1')
				vres.znach[i] = '1';
			if ((vres.znach[i] == '0'&&vv2.znach[i] == '1') || (vres.znach[i] == '1'&&vv2.znach[i] == '0'))
				vres.znach[i] = '1';
			if ((vres.znach[i] == '0'&&vv2.znach[i] == 'x') || (vres.znach[i] == 'x'&&vv2.znach[i] == '0'))
				vres.znach[i] = 'x';
			if ((vres.znach[i] == 'x'&&vv2.znach[i] == '1') || (vres.znach[i] == '1'&&vv2.znach[i] == 'x'))
				vres.znach[i] = '1';
		}
				return vres;
	}
	Vector Vector::Operation2(const Vector &v2) {
		Vector vres(*this), vv2(v2);
		if (vres.n > vv2.n) {
			for (int i = vv2.n; i < n; ++i)
				vv2.znach[i] = 'x';
			vv2.n = n;
		}
		if (vv2.n > vres.n) {
			for (int i = n; i < vv2.n; ++i)
				vres.znach[i] = 'x';
			vres.n = v2.n;
		}
		for (int i = 0; i < n; ++i) {
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
	int Vector::Operation3(const Vector &v2) {
		Vector vv1(*this), vv2(v2);
		if (vv1.n > vv2.n) {
			for (int i = vv2.n; i < n; ++i)
				vv2.znach[i] = 'x';
			vv2.n = n;
		}
		if (vv2.n > vv1.n) {
			for (int i = n; i < vv2.n; ++i)
				vv1.znach[i] = 'x';
			vv1.n = vv2.n;
		}
        for (int i = 0; i < vv1.n; ++i) {
			if (vv1.znach[i] > vv2.znach[i])
				return 0;
			if (vv2.znach[i] > vv1.znach[i])
				return 1;
		}
		return 2;
	}
	Vector Vector::Operation4() {
		Vector vres;
		vres.n = n;
		for (int i = 0; i < n; ++i) {
			if (znach[i] == '0')
				vres.znach[i] = '1';
			if (znach[i] == '1')
				vres.znach[i] = '0';
			if (znach[i] == 'x')
				vres.znach[i] = 'x';
		}
		return vres;
	}
	int Vector::Analysis() {
		for (int i = 0; i < n; ++i)
			if (znach[i] == 'x')
				return 1;
		return 0;
	}
}


