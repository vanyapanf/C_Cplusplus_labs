#pragma once
#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <iostream>
namespace Application {
	class Vector {
	private:
		static const int SZ = 10;
		int n;
		char znach[SZ];
	public:
		Vector() :n(0) {};
		Vector(int n);
		Vector(char* znach);
		std::istream & input(std::istream&);
		std::ostream & output(std::ostream&);
		Vector Operation1(const Vector &v2);//���
		Vector Operation2(const Vector &v2);//�
		int Operation3(const Vector &v2);//���������
		Vector Operation4();//��
		int Analysis();
	};
}
#endif

