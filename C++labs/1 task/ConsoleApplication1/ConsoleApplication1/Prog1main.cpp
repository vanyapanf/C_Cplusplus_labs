#include <iostream>
#include "Prog1.h"
using namespace Prog1;
int main(){
	Line* lines=nullptr;
	int* vect= nullptr;
	int m;
	lines = input(m);
	if (lines == nullptr)
	{
		std::cout << "Error" << std::endl;
		return 1;
	}
	vect=createvector(lines, m);
	if (vect == nullptr)
	{
		std::cout << "Error" << std::endl;
		return 1;
	}
	output(lines, vect,m);
	erase(lines, m);
	return 0;
}