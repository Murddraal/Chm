#include "header.h"

void input(matrix &Matrix)
{
	FILE *size, *di, *al, *au;
	int i, j;
	chtype buf = 0;
	if (sizeof(chtype) == sizeof(float))
	{
		size = fopen("size.txt", "r");
		fscanf(size, "%d %d", &Matrix.n, &Matrix.l);
		fclose(size);
		Matrix.L.resize(Matrix.n);
		Matrix.U.resize(Matrix.n);
		Matrix.D.resize(Matrix.n);

		Matrix.middle = Matrix.l / 2;
		for (i = 0; i < Matrix.n; i++)
		{
			Matrix.L[i].resize(Matrix.middle);
			Matrix.U[i].resize(Matrix.middle);
		}

		//di
		di = fopen("di.txt", "r");
		for (i = 0; i < Matrix.n; i++)
			fscanf(di, "%f", &Matrix.D[i]);
		fclose(di);

		//du

		au = fopen("au.txt", "r");
		for (i = 0; i < Matrix.n; i++)
		{
			for (j = 0; j < Matrix.middle; j++)
				fscanf(au, "%f", &Matrix.U[i][j]);
		}
		fclose(au);
		//al
		al = fopen("al.txt", "r");
		for (i = 0; i < Matrix.n; i++)
		{
			for (j = 0; j < Matrix.middle; j++)
				fscanf(al, "%f", &Matrix.L[i][j]);
		}
		fclose(al);
	}
	else
	{
		FILE *size, *di, *al, *au;
		int i, j;
		chtype buf = 0;
		if (sizeof(chtype) == sizeof(float))
		{
			size = fopen("size.txt", "r");
			fscanf(size, "%d %d", &Matrix.n, &Matrix.l);
			fclose(size);
			Matrix.L.resize(Matrix.n);
			Matrix.U.resize(Matrix.n);
			Matrix.L.reserve(Matrix.n);
			Matrix.U.reserve(Matrix.n);

			Matrix.D.reserve(Matrix.n);
			Matrix.D.resize(Matrix.n);

			Matrix.middle = Matrix.l / 2;
			for (i = 0; i < Matrix.n; i++)
			{
				Matrix.L[i].reserve(Matrix.middle);
				Matrix.U[i].reserve(Matrix.middle);
				Matrix.L[i].resize(Matrix.middle);
				Matrix.U[i].resize(Matrix.middle);
			}

			//di
			di = fopen("di.txt", "r");
			for (i = 0; i < Matrix.n; i++)
				fscanf(di, "%lf", &Matrix.D[i]);
			fclose(di);

			//du

			au = fopen("au.txt", "r");
			for (i = 0; i < Matrix.n; i++)
			{
				for (j = 0; j < Matrix.middle; j++)
					fscanf(au, "%lf", &Matrix.L[i][j]);
			}
			for (int i1 = 1; i1 < Matrix.n; i1++)
			{
				for (int i2 = i1, j1 = 0, j2 = rwall; (i2 < Matrix.n) && (i2 <= i1 + rwall) && (j2 >= 0); i2++, j2--, j1++)
				{
					Matrix.U[i1 - 1][j1] = Matrix.L[i2][j2];
				}

			}
			//al
			al = fopen("al.txt", "r");
			for (i = 0; i < Matrix.n; i++)
			{
				for (j = 0; j < Matrix.middle; j++)
					fscanf(al, "%lf", &Matrix.L[i][j]);
			}
		}
	}
}

void LDU(matrix &Matrix)
{
	int i, j, k;
	for (k = 0; k < Matrix.n; k++)
	{
		i = k;
		forD(Matrix, i, k);

		for (j = rwall, i++; (j >= 0) && (i <Matrix.n); j--, i++)
		{
			forL(Matrix, i, j, k);
			forU(Matrix, i, j, k);
		}
	}
}


void forL(matrix &Matrix, int i, int j, int t)
{
	int k = 0, border = 0, start, b1, b2, b3;
	chtype l, summ = 0;
	start = i - Matrix.middle;
	if (start < 0)
	{
		start = 0;
	}
	b3 = i - Matrix.middle + j;
	if (t > 0)
	{
		k = start;
		border = j;
		while (border>0)

		{
			if (Matrix.L[i][j - border] == 0)
			{
				border--;
				continue;
			}//		l-елементы	d-элементы		u-элементы
			b1 = j - border; b2 = Matrix.middle - border;//b2 = middle + border;
			summ += Matrix.L[i][b1] * Matrix.D[k] * Matrix.U[b3][b2];
			k++;
			border--;
		}
	}
	
	l = (Matrix.L[i][j] - summ) / Matrix.D[b3];

	Matrix.L[i][j] = l;
}
void forD(matrix &Matrix, int i, int t)
{
	int k = 0, border, b;
	chtype dk, summ = 0;
	if (t > 0)
	{
		if (i <= Matrix.middle)
		{
			border = i;
		}
		else
		{
			border = Matrix.middle;
		}
		for (k = i - border; k < i; k++, border--)
		{
			b = Matrix.middle - border;
			//		l-елементы			d-элементы		u-элементы
			summ += Matrix.L[i][b] * Matrix.D[k] * Matrix.U[i][b];
		}
	}
	dk = Matrix.D[i] - summ;

	Matrix.D[i] = dk;
}
void forU(matrix &Matrix, int i, int j, int t)
{
	int k = 0, border = 0, start, b1, b2, b3;
	chtype u, summ = 0;
	start = i - Matrix.middle;
	if (start < 0)
	{
		start = 0;
	}
	b3 = i - Matrix.middle + j;
	if (t > 0)
	{
		k = start;
		border = j;
		while (border>0)

		{
			if (Matrix.U[i][j - border] == 0)
			{
				border--;
				continue;
			}//		l-елементы	d-элементы		u-элементы
			b1 = Matrix.middle-border; b2 = j - border;//b2 = middle + border;
			summ += Matrix.L[b3][b1] * Matrix.D[k] * Matrix.U[i][b2];
			k++;
			border--;
		}
	}

	u = (Matrix.U[i][j] - summ) / Matrix.D[b3];

	Matrix.U[i][j] = u;
}

void multyplyL(matrix & Matrix)
{
	int i = 0, j = 0, Max=1, border = 1;
	chtype summ=0;
	//сначала вычисл€ютс€ первые Matrix.middle элементов, ибо в матрице происходит смещение начала строки влево
	for (i = 1; i <= Matrix.middle; i++)
	{
		for (j = 0; j < Max; j++)
		{
			summ += Matrix.F[j] * Matrix.L[i][Matrix.middle-border+j];
		}
		Max++; border++;
		Matrix.F[i] -= summ;
	}
	//строка матрицы пробегаетс€ от начала до конца, но кол-во элементов вектора ограничено Matrix.middle
	border = 1;
	for (i = Matrix.middle + 1; i < Matrix.n; i++)
	{
		for (j = 0; j < Matrix.middle; j++)
		{
			summ += Matrix.F[j+border] * Matrix.L[i][j];
		}
		border++;
		Matrix.F[i] -= summ;
	}
}

void multyplyD(matrix & Matrix)
{
	int i = 0;
	for (i = 0; i < Matrix.n; i++)
		Matrix.F[i] /= Matrix.D[i];
}

void multyplyU(matrix & Matrix)
{
	int i = dwall, j = 0,  border = rwall;
	chtype summ = 0;
	Matrix.F[dwall] /= Matrix.U[dwall][rwall];
	
	for (i = dwall-1; i > dwall-rwall; i--)
	{
		for ()
		{
			
		}
		border--;
		Matrix.F[i] = (Matrix.F[i-1]-summ)/Matrix.U[i][rwall];
	}
}