// Application.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../Library/Deltoida.h"
#include <iostream>
int main(int argc, _TCHAR* argv[])
{
	Application::Deltoida D(0, 0);
	Application::Point p(0);
	int fl1 = 1;
	char*s = NULL;
	while (fl1) {
		std::cout << "Your deltoida is: " << std::endl;
		s = D.frm();
		std::cout << s << std::endl;
		delete[]s;
		std::cout << "length of tangent: " << D.lenght1() << std::endl;
		std::cout << "length of deltoida: " << D.lenght2() << std::endl;
		std::cout << "area of deltoida: " << D.area() << std::endl;
		int fl2 = 1;
		while (fl2) {
			std::cout << "Enter t to calculate x and y:" << std::endl;
			double t;
			Application::Point p;
			std::cin >> t;
			fl2 = std::cin.good();
			if (!fl2)
				continue;
			try {
				p = D.coordinates(t);
				std::cout << "x: " << p.x << "y: " << p.y << std::endl;
			}
			catch(std::exception &ex){
				std::cout << ex.what() << std::endl;
			}
		}
		std::cin.clear();
		std::cout << "Enter r and x and y to continue or press ctrl+Z to quit" << std::endl;
		double r,x,y;
		std::cin >> r >> x >> y;
		Application:: Point p;
		p.x = x;
		p.y = y;
		if (std::cin.good()) {
			try {
				D.SetR(r);
				D.SetP(p);
			}
			catch (std::exception &ex) {
				std::cout << ex.what() << std::endl;
			}
		}
		else fl1 = 0;
	}
    return 0;
}

