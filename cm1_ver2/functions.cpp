#include "header.h"


void Matrix::input()
{
	FILE *size, *di, *al, *au, *f;
	int i, j;
	chtype buf = 0;
	if (sizeof(chtype) == sizeof(float))
	{
		size = fopen("size.txt", "r");
		fscanf(size, "%d %d", &n, &l);
		fclose(size);
		L.resize(n);
		U.resize(n);
		D.resize(n);
		F.resize(n);

		middle = l / 2;
		for (i = 0; i < n; i++)
		{
			L[i].resize(middle);
			U[i].resize(middle);
		}
		//f
		f = fopen("f.txt", "r");
		for (i = 0; i < n; i++)
			fscanf(f, "%f", &F[i]);
		fclose(f);
		//di
		di = fopen("di.txt", "r");
		for (i = 0; i < n; i++)
			fscanf(di, "%f", &D[i]);
		fclose(di);

		//du

		au = fopen("au.txt", "r");
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < middle; j++)
				fscanf(au, "%f", &U[i][j]);
		}
		fclose(au);
		//al
		al = fopen("al.txt", "r");
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < middle; j++)
				fscanf(al, "%f", &L[i][j]);
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
			fscanf(size, "%d %d", &n, &l);
			fclose(size);
			L.resize(n);
			U.resize(n);
			D.resize(n);

			middle = l / 2;
			for (i = 0; i < n; i++)
			{
				L[i].reserve(middle);
				U[i].reserve(middle);
				L[i].resize(middle);
				U[i].resize(middle);
			}

			//f
			f = fopen("f.txt", "r");
			for (i = 0; i < n; i++)
				fscanf(f, "%lf", &F[i]);
			fclose(f);
			//di
			di = fopen("di.txt", "r");
			for (i = 0; i < n; i++)
				fscanf(di, "%lf", &D[i]);
			fclose(di);

			//du

			au = fopen("au.txt", "r");
			for (i = 0; i < n; i++)
			{
				for (j = 0; j < middle; j++)
					fscanf(au, "%lf", &L[i][j]);
			}
			for (int i1 = 1; i1 < n; i1++)
			{
				for (int i2 = i1, j1 = 0, j2 = middle-1; (i2 < n) && (i2 <= i1 + middle-1) && (j2 >= 0); i2++, j2--, j1++)
				{
					U[i1 - 1][j1] = L[i2][j2];
				}

			}
			//al
			al = fopen("al.txt", "r");
			for (i = 0; i < n; i++)
			{
				for (j = 0; j < middle; j++)
					fscanf(al, "%lf", &L[i][j]);
			}
		}
	}
}

void Matrix::LDU()
{
	int i, j, k;
	for (k = 0; k < n; k++)
	{
		i = k;
		forD(i, k);

		for (j = middle-1, i++; (j >= 0) && (i <n); j--, i++)
		{
			forL(i, j, k);
			forU(i, j, k);
		}
	}
}


void Matrix::forL(int i, int j, int t)
{
	int k = 0, border = 0, start, b1, b2, b3;
	chtype l, summ = 0;
	start = i - middle;
	if (start < 0)
	{
		start = 0;
	}
	b3 = i - middle + j;
	if (t > 0)
	{
		k = start;
		border = j;
		while (border>0)

		{
			if (L[i][j - border] == 0)
			{
				border--;
				continue;
			}//		l-елементы	d-элементы		u-элементы
			b1 = j - border; b2 = middle - border;//b2 = middle + border;
			summ += L[i][b1] * D[k] * U[b3][b2];
			k++;
			border--;
		}
	}
	
	l = (L[i][j] - summ) / D[b3];

	L[i][j] = l;
}
void Matrix::forD(int i, int t)
{
	int k = 0, border, b;
	chtype dk, summ = 0;
	if (t > 0)
	{
		if (i <= middle)
		{
			border = i;
		}
		else
		{
			border = middle;
		}
		for (k = i - border; k < i; k++, border--)
		{
			b = middle - border;
			//		l-елементы			d-элементы		u-элементы
			summ += L[i][b] * D[k] * U[i][b];
		}
	}
	dk = D[i] - summ;

	D[i] = dk;
}
void Matrix::forU(int i, int j, int t)
{
	int k = 0, border = 0, start, b1, b2, b3;
	chtype u, summ = 0;
	start = i - middle;
	if (start < 0)
	{
		start = 0;
	}
	b3 = i - middle + j;
	if (t > 0)
	{
		k = start;
		border = j;
		while (border>0)

		{
			if (U[i][j - border] == 0)
			{
				border--;
				continue;
			}//		l-елементы	d-элементы		u-элементы
			b1 = middle-border; b2 = j - border;//b2 = middle + border;
			summ += L[b3][b1] * D[k] * U[i][b2];
			k++;
			border--;
		}
	}

	u = (U[i][j] - summ) / D[b3];

	U[i][j] = u;
}

void Matrix::multyplyL()
{
	int i = 0, k = 0, j = 0, Max=1, border = 1;
	chtype summ=0;
	//сначала вычисл€ютс€ первые Matrix.middle элементов, ибо в матрице происходит смещение начала строки влево
	for (i = 1; i <= middle; i++)
	{
		summ = 0;
		for (j = 0; j < Max; j++)
		{
			k = middle - border + j;
			summ += F[j] * L[i][k];
		}
		Max++; border++;
		F[i] -= summ;
	}
	//строка матрицы пробегаетс€ от начала до конца, но кол-во элементов вектора ограничено Matrix.middle
	border = 1;
	for (i = middle + 1; i < n; i++)
	{
		summ = 0;
		for (j = 0; j < middle; j++)
		{
			summ += F[j+border] * L[i][j];
		}
		border++;
		F[i] -= summ;
	}
}


void Matrix::multyplyD()
{
	int i = 0;
	for (i = 0; i < n; i++)
		F[i] /= D[i];
}

void Matrix::multyplyU()
{
	int k = 0, i = 0, j = 0, Max = n-1, Min=0;
	chtype summ = 0;
	
	for (i = n-2; i>= 0; i--)
	{
		summ = 0;
		k = middle - 1;
		for (j = i+1; ((j <= Max)&&(k >= 0)); j++, k--)
		{
			summ += F[j] * U[j][k];
		}
		
		F[i] -= summ;
	}
	
}

void Matrix::output()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < middle; j++)
			printf("%f ", L[i][j]);
		printf("%f ", D[i]);
		for (int j = 0; j < middle; j++)
			printf("%f ", U[i][j]);
		printf("\n");
	}
}
void Matrix::vewVector()
{
	for (int i = 0; i < n; i++)
	{
		printf("%f\n", F[i]);
	}
}