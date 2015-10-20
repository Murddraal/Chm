#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <fstream>
#include <io.h>
#include <vector>
#include <iostream>
using namespace std;
typedef float chtype;

class Matrix
{
private:
	int n, l, middle;
	vector <vector <chtype>> L, U;
	vector <chtype> D, F;
public:
	void input();
	void LDU();
	void forD(int, int);
	void forLU(int, int, int);
	void multyplyL();
	void multyplyU();
	void multyplyD();
	void output();
	void vewVector(bool);
};
