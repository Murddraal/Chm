#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <fstream>
#include <io.h>
#include <vector>
#include <iostream>
#define dwall Matrix.n - 1
#define rwall Matrix.middle -1
using namespace std;
typedef float chtype;

struct matrix
{
	vector <vector <chtype>> L, U;
	vector <chtype> D, x, y, z, F;
	int n, l, middle;
};

void input(matrix &);
void LDU(matrix &);
void forL(matrix &, int, int, int);
void forD(matrix &, int, int);
void forU(matrix &, int, int, int);
void multyplyL(matrix &);
void multyplyU(matrix &);


