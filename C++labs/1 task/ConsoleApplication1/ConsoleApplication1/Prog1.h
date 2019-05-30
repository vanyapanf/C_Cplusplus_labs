#pragma once
namespace Prog1 {
	struct Elem {
		int a;
		int num;
	};
	struct Line {
		//int nomstr;
		int kolelem;
		//int fl;
		Elem* nom;
	};
	/*struct Array {
		int kolstr;
		Line* str;
	};*/
	int GetNum(int&);
	Line* input(int &);
	int* createvector(Line*,int);
	int output(Line*, int*,int);
	Line* erase(Line *&, int);
}