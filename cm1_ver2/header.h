#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <fstream>
#include <io.h>
#include <vector>
#include <iostream>
#include <math.h>
using namespace std;
typedef double chtype;

class Matrix
{
private:
	int n, l, middle, k=1;
	vector <vector <chtype>> L, U, G;
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
	void gilbert(int);
	void gauss();
};
