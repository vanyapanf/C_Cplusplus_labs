#include <iostream>
#include "Prog1.h"
namespace Prog1 {
	int GetNum(int &a) {
		std::cin >> a;
		if (!std::cin.good())
			return -1;
		return 1;
	}
	Line* erase(Line *&lines,int m) {
		int i;
		for (i = 0; i < m; i++)
			delete[] lines[i].nom;
		delete[] lines;
		lines = nullptr;
		return nullptr;
	}
	Line* input(int &rm) {
		int m,n,ch,ch1,ch2,i=0;
		Line* lines = nullptr;
		int* ar;
		std::cout << "Enter m and n:" << std::endl;
		if (GetNum(m) < 0)
			return nullptr;
		if (GetNum(n) < 0)
			return nullptr;
		try {
			lines = new Line[m];
		}
		catch (const std::bad_alloc &ba) {
			std::cout << "too many rows in matrix:" << ba.what() << std::endl;
			return nullptr;
		}
		for (i = 0; i < m; ++i) {
			lines[i].kolelem = 0;
			lines[i].nom = nullptr;
		}
		for ( i = 0; i < m; ++i) {
			std::cout << "Enter nom of line:" << std::endl;
			if (GetNum(ch) < 0) {
				erase(lines, i);
				return nullptr;
			}
			//lines[ch].fl = 1;
			if ((ch > m - 1) || (ch < 0)) 
				break;
			//lines[ch].nomstr = ch;
			lines[ch].kolelem = 0;
			std::cout << "Enter elements (znach,indx):" << std::endl;
			try {
				ar = new int[n];
			}
			catch (const std::bad_alloc &ba) {
				std::cout <<  ba.what() << std::endl;
				erase(lines, i);
				return nullptr;
			}
			for (int j = 0; j < n; ++j)
				ar[j] = 0;
			for (int j = 0; j < n; ++j) {
					if (GetNum(ch1) < 0) {
					erase(lines, i);
					return nullptr;
				}
				if (ch1 == -1)
					break;
				if (GetNum(ch2) < 0)
				{
					erase(lines, i);
					return nullptr;
				}
				if ((ch2 > n-1)||(ch2<0))
				{
					erase(lines, i);
					return nullptr;
				}
				ar[ch2] = ch1;
				++lines[ch].kolelem;
			}
			try {
				lines[ch].nom = new Elem[lines[ch].kolelem];
			}
			catch (const std::bad_alloc &ba) {
				std::cout << "too many items in matrix:" << ba.what() << std::endl;
				erase(lines, i);
				return nullptr;
			}
			int j1 = 0;
			for(int j=0;j<n;++j)
					if (ar[j] != 0) {
						lines[ch].nom[j1].a = ar[j];
						lines[ch].nom[j1].num = j;
						++j1;
					}
		}
		rm = m;
		return lines;
	}
	int* createvector(Line *lines ,int m) {
		int *vect = nullptr;
		try {
			vect = new int[m];
		}
		catch(const std::bad_alloc &ba){
			std::cout << ba.what() << std::endl;
			return nullptr;
		}
		for (int i = 0; i <m; ++i) {
			vect[i] = 0;
				for (int j = 0; j < lines[i].kolelem; ++j) {
					int fl = 0;
					int ch = lines[i].nom[j].a;
					for (int j1 = 0; j1 < j; ++j1)
						if (lines[i].nom[j1].a == ch) {
							fl = 1;
							break;
						}
					if (fl == 0)
						++vect[i];
			}
		}
		return vect;
	}
	int output(Line* lines, int *vect,int m) {
		int ch;
		std::cout << "Result vector:" << std::endl;
		for (int i = 0; i <m; ++i)
			std::cout << vect[i] << std::endl;
		std::cout << "Matrix:" << std::endl;
		for (int i = 0; i < m; ++i) {
			if (lines[i].nom!=nullptr) {
				std::cout << "Nomer str:" << i << std::endl;
				for (int j = 0; j < lines[i].kolelem; ++j)
					std::cout << "Znach:" << lines[i].nom[j].a << " Nomer:" << lines[i].nom[j].num << std::endl;
			}
		}
		std::cin >>ch;
		return 1;
	}
}