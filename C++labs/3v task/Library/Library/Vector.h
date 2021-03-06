#pragma once
#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <iostream>
namespace Application {
	class Vector {
	private:
		int SZ;
		char* znach;
	public:
		Vector() :SZ(0),znach(nullptr) {};
		Vector(int n);
		Vector(char* znach);
		Vector(const Vector&);
		Vector(Vector&&);
		Vector(const Vector &, int);
		std::istream & input(std::istream&);
		std::ostream & output(std::ostream&);
		int GetSZ() const { return SZ; };
		const char* GetZnach(){ return znach; };
		//Vector Operation1(const Vector &v2);//���
		//const Vector operator+ (const Vector &v2);
		friend const Vector operator+ (const Vector &v1, const Vector &v2);
		//Vector Operation2(const Vector &v2);//�
		friend const Vector operator*(const Vector &v1,const Vector &v2);
		//int Operation3(const Vector &v2);//���������
		friend const int operator-(const Vector &v1,const Vector &v2);
		//Vector Operation4();//��
		Vector& operator~();
		int Analysis();
		Vector &operator=(const Vector &);
		Vector &operator=(Vector &&);
		~Vector() { delete[]znach; };
	};
}
#endif

