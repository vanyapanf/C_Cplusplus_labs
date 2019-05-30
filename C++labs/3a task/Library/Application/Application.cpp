// Application.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include "..\Library\Vector.h"
int ILI() {
	Application::Vector v1, v2;
	int fl = 0;
	try {
		std::cout << "Enter v1" << std::endl;
		v1.input(std::cin);
	}
	catch(std::exception &ex){
		if (ex.what() != "")
			fl = 1;
		std::cout << ex.what() << std::endl;
	}
	try {
		std::cout << "Enter v2" << std::endl;
		v2.input(std::cin);
	}
	catch (std::exception &ex) {
		if (ex.what() != "")
			fl = 1;
		std::cout << ex.what() << std::endl;
	}
	if (fl == 1)
		return 0;
	std::cout << "Operation v1+v2:";
	Application::Vector vres = v1.Operation1(v2);
	vres.output(std::cout);
	return 0;
}
int I() {
	Application::Vector v1, v2;
	int fl = 0;
	try {
		std::cout << "Enter v1" << std::endl;
		v1.input(std::cin);
	}
	catch (std::exception &ex) {
		if (ex.what() != "")
			fl = 1;
		std::cout << ex.what() << std::endl;
	}
	try {
		std::cout << "Enter v2" << std::endl;
		v2.input(std::cin);
	}
	catch (std::exception &ex) {
		if (ex.what() != "")
			fl = 1;
		std::cout << ex.what() << std::endl;
	}
	if (fl == 1)
		return 0;
	std::cout << "Operation v1*v2:";
	Application::Vector vres = v1.Operation2(v2);
	vres.output(std::cout);
	return 0;
}
int Comparison() {
	Application::Vector v1, v2;
	int fl = 0;
	try {
		std::cout << "Enter v1" << std::endl;
		v1.input(std::cin);
	}
	catch (std::exception &ex) {
		if (ex.what() != "")
			fl = 1;
		std::cout << ex.what() << std::endl;
	}
	try {
		std::cout << "Enter v2" << std::endl;
		v2.input(std::cin);
	}
	catch (std::exception &ex) {
		if (ex.what() != "")
			fl = 1;
		std::cout << ex.what() << std::endl;
	}
	if (fl == 1)
		return 0;
	std::cout << "Comparison v1,v2:";
	int res = v1.Operation3(v2);
	if (res == 0)
		std::cout << "v1>v2";
	if (res == 1)
		std::cout << "v2>v1";
	if (res == 2)
		std::cout << "v1=v2";
	std::cout << std::endl;
	return 0;
}
int Negation() {
	Application::Vector v;
	int fl = 0;
	try {
		std::cout << "Enter v" << std::endl;
		v.input(std::cin);
	}
	catch (std::exception &ex) {
		if (ex.what() != "")
			fl = 1;
		std::cout << ex.what() << std::endl;
	}
	if (fl == 1)
		return 0;
	std::cout << "Negation v:";
	Application::Vector vres = v.Operation4();
	vres.output(std::cout);
	std::cout << std::endl;
	return 0;
}
int Analysis() {
	Application::Vector v;
	int fl = 0;
	try {
		std::cout << "Enter v" << std::endl;
		v.input(std::cin);
	}
	catch (std::exception &ex) {
		if (ex.what() != "")
			fl = 1;
		std::cout << ex.what() << std::endl;
	}
	if (fl == 1)
		return 0;
	std::cout << "Analysis v:";
	int an = v.Analysis();
	if (an == 0)
		std::cout << "have not x ";
	if (an == 1)
		std::cout << "have x ";
	std::cout << std::endl;
	return 0;
}
int _tmain(int argc,_TCHAR* argv)
{	
	char* ptr[5] = {"0.v1+v2","1.v1*v2","2.v1<>v2","3.Negation v","4.Analysis v"};
	std::cout << "Menu:" << std::endl;
	for (int i = 0; i < 5; ++i)
		std::cout << ptr[i] << std::endl;
	int fl = 1;
	while (fl) {
		int k;
		std::cout << "Enter deistvie or press ctrl+Z to quit:" << std::endl;
		std::cin >> k;
		if (std::cin.eof())
			break;
		switch (k) { 
		case 0: {
			int i = ILI();
			break; }
		case 1: {
			int i = I();
			break; }
		case 2: {
			int i = Comparison();
			break; }
		case 3: {
			int i = Negation();
			break; }
		case 4: {
			int i = Analysis();
			break; }
		}
	}
	
	return 0;
}
/*Application::Vector v1("xx0001111");
Application::Vector v2(9);
int fl1 = 1;
while (fl1) {
std::cout << "Vector 1:" << v1.frm();
std::cout << "Vector 2:" << v2.frm();
std::cout << "Operation v1+v2:";
Application::Vector vres = v1.Operation1(v2);
vres.output(std::cout);
std::cout << "Operation v1*v2:";
Application::Vector vres = v1.Operation2(v2);
vres.output(std::cout);
std::cout << "Comparison v1,v2:";
int res = v1.Operation3(v2);
if (res == 0)
std::cout << "v1>v2";
if (res == 1)
std::cout << "v2>v1";
if (res == 2)
std::cout << "v1=v2";
std::cout << "Negation v1,v2:";
Application::Vector vres = v1.Operation4();
vres.output(std::cout);
Application::Vector vres = v2.Operation4();
vres.output(std::cout);
std::cout << "Analysis v1,v2:";
int an = v1.Analysis();
if (an == 0)
std::cout << "have not x ";
if (an == 1)
std::cout << "have x ";
int an = v2.Analysis();
if (an == 0)
std::cout << "have not x ";
if (an == 1)
std::cout << "have x ";
std::cout << "Enter v1 and v2 to continue or press ctrl+Z to quit" << std::endl;
v1.input(std::cin);
v2.input(std::cin);*/

