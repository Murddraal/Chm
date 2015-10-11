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
	vector <chtype> D, x, y, z, F;
public:
	void input();
	void LDU();
	void forL(int, int, int);
	void forD(int, int);
	void forU(int, int, int);
	void multyplyL();
	void multyplyU();
	void multyplyD();
	void output();
};

<<<<<<< HEAD
=======
class Matrics
{
private:
	int n, l, middle;
	vector <vector <chtype>> L, U;
	vector <chtype> D, x, y, z, F;
public:
	void input(matrix &);
	void LDU(matrix &);
	void forL(matrix &, int, int, int);
	void forD(matrix &, int, int);
	void forU(matrix &, int, int, int);
	void multyplyL(matrix &);
	void multyplyU(matrix &);
	void multyplyD(matrix &);
};

>>>>>>> origin/master


