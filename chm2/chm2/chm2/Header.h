#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <math.h>

using namespace std;

class Matrix
{
private:
	int n, m, k, prec, iter;
	vector <vector <double>> A;
	vector <double> x, F;
public:
	void input();

};