#include "Header.h"

void Matrix::input()
{
	FILE *di, *au, *al, *sizes;
	int i, j;

	sizes = fopen("sizes.txt", "r");
	fscanf(sizes, "%d %d %d %d", &n, &m, &k, &prec, &iter);
	fclose(sizes);
	A.resize(n);
	for (i = 0; i < n; i++)
	{
		A[i].resize(7);
	}

	di = fopen("di.txt", "r");
	al = fopen("al.txt", "r");
	au = fopen("au.txt", "r");
	for (i = 0; i < n; i++)
	{
		fscanf(di, "%lf", &A[i][3]);
		for (j = 0; j < 3; j++)
		{
			fscanf(al, "%lf", A[i][j]);
			fscanf(au, "%lf", A[i][j + 4]);
		}
	};
	fclose(di);
	fclose(au);
	fclose(al);

}