#include "header.h"


void Matrix::input()
{
	FILE *size, *di, *al, *au, *f;
	int i, j;
	chtype buf = 0;
	
		size = fopen("size.txt", "r");
		fscanf(size, "%d %d", &n, &l);
		fclose(size);
		L.resize(n);
		U.resize(n);
		D.resize(n);
		F.resize(n);

		middle = l / 2;
		

		if (sizeof(chtype) == sizeof(float))
		{
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

		//au

		au = fopen("au.txt", "r");
		for (i = 0; i < n; i++)
		{
			U[i].resize(middle);
			for (j = 0; j < middle; j++)
				fscanf(au, "%f", &U[i][j]);
		}
		fclose(au);
		//al
		al = fopen("al.txt", "r");
		for (i = 0; i < n; i++)
		{
			L[i].resize(middle);
			for (j = 0; j < middle; j++)
				fscanf(al, "%f", &L[i][j]);
		}
		fclose(al);
	}
	else
	{
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

		//au

		au = fopen("au.txt", "r");
		for (i = 0; i < n; i++)
		{
			U[i].resize(middle);
			for (j = 0; j < middle; j++)
				fscanf(au, "%lf", &U[i][j]);
		}
		fclose(au);
		//al
		al = fopen("al.txt", "r");
		for (i = 0; i < n; i++)
		{
			L[i].resize(middle);
			for (j = 0; j < middle; j++)
				fscanf(al, "%lf", &L[i][j]);
		}
		fclose(al);
	}
		chtype p = 10;
		k = 16;
		D[0] += pow(p, -k);
		F[0] += pow(p, -k);
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
			forLU(i, j, k);
		}
	}
}



void Matrix::forD(int i, int t)
{
	int k = 0, border, b;//b - позиция j элементов в U L
	//chtype dk, summ = 0;
	double dk, summ = 0;
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

void Matrix::forLU(int i, int j, int t)
{
	int k = 0, border = 0, start, b1, b2, b3;//b1 - позиция j для L, b2 - позиция j для U
	//chtype l=0, u=0, summL = 0, summU=0;
	double l = 0, u = 0, summL = 0, summU = 0;
	start = i - middle;
	if (start < 0)
	{
		start = 0;
	}
	b3 = i - middle + j;//строка в U
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
			b1 = j - border; b2 = middle - border;
			summL += L[i][b1] * D[k] * U[b3][b2];
			summU += L[b3][b2] * D[k] * U[i][b1];
			k++;
			border--;
		}
	}

	l = (L[i][j] - summL) / D[b3];
	u = (U[i][j] - summU) / D[b3];

	U[i][j] = u;
	L[i][j] = l;
}

void Matrix::multyplyL()
{
	int i = 0, k = 0, j = 0, Max=1, border = 1;
	//chtype summ=0;
	double summ = 0;
	//сначала вычисляются первые Matrix.middle элементов, ибо в матрице происходит смещение начала строки влево
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
	//строка матрицы пробегается от начала до конца, но кол-во элементов вектора ограничено Matrix.middle
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
	//chtype summ = 0;
	double summ = 0;
	
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
	if (sizeof(chtype) == sizeof(float))
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < middle; j++)
				printf("%.8f ", L[i][j]);
			printf("%.8f ", D[i]);
			for (int j = 0; j < middle; j++)
				printf("%.8f ", U[i][j]);
			printf("\n");
		}
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < middle; j++)
				printf("%.16lf ", L[i][j]);
			printf("%.16lf ", D[i]);
			for (int j = 0; j < middle; j++)
				printf("%.16lf ", U[i][j]);
			printf("\n");
		}
	}
}
void Matrix::vewVector(bool inFile)
{
	if (!inFile)
	{
		if (sizeof(chtype) == sizeof(float))
		{
			for (int i = 0; i < n; i++)
			{
				printf("%.8f\n", F[i]);
			}
		}
		else
		{
			for (int i = 0; i < n; i++)
			{
				printf("%.16lf\n", F[i]);
			}
		}
	}
	else
	{
		FILE *output;
		output = fopen("vector x.txt", "w");
		if (sizeof(chtype) == sizeof(float))
		{
			for (int i = 0; i < n; i++)
			{
				fprintf(output, "%.8f\n", F[i]);
			}
		}
		else
		{
			for (int i = 0; i < n; i++)
			{
				fprintf(output, "%.16lf\n", F[i]);
			}
		}
	}
}

void Matrix::gilbert(int k)
{
	
	
	vector <chtype> x;
	G.resize(k);
	F.resize(k);
	x.resize(k);
	n = k;
	l = k * 2 - 1;
	middle = l / 2;
	
	for (int i = 0; i < k; i++)//заполнение плотной матрицы гильберта
	{
		G[i].resize(k);
		for (int j = 0; j < k; j++)
			G[i][j] = (chtype)1 / (i + j + 1);
	}
	for (int i = 0; i < k; i++)//вектор на который умножаем
	{
		x[i] = i + 1;
	}
	for (int i = 0; i < k; i++)//умножение матриц на вектор
	{
		for (int j = 0; j < k; j++)
			F[i] += G[i][j] * x[j];
	}

	D.resize(k);
	L.resize(k);
	U.resize(k);
	for (int i = 0; i < k; i++)//преобразование в ленточный формат
	{
		L[i].resize(k - 1);
		U[i].resize(k - 1);
		D[i] = G[i][i];
	
	}
	
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < i; j++)
		{
			L[i][abs(i - j - k + 1)] = G[i][j];
			U[i][abs(i - j - k + 1)] = G[j][i];
		}
	}

	
	return;
}

void Matrix::gauss()
{
	FILE *g, *f;
	int i, j;
	chtype buf = 0;

	n = 10;
	G.resize(10);
	F.resize(10);
	
	if (sizeof(chtype) == sizeof(float))
	{
		//f
		f = fopen("f.txt", "r");
		for (i = 0; i < n; i++)
			fscanf(f, "%f", &F[i]);
		fclose(f);
		//G
		g = fopen("gauss.txt", "r");
		for (i = 0; i < n; i++)
		{
			G[i].resize(n);
			for (j = 0; j < 10; j++)
				fscanf(g, "%f", &G[i][j]);
		}
		fclose(g);
	}
	else
	{
		//f
		f = fopen("f.txt", "r");
		for (i = 0; i < n; i++)
			fscanf(f, "%lf", &F[i]);
		fclose(f);
		//G
		g = fopen("gauss.txt", "r");
		for (i = 0; i < n; i++)
		{
			G[i].resize(n);
			for (j = 0; j < n; j++)
				fscanf(g, "%lf", &G[i][j]);
		}
		fclose(g);
	}
	chtype p = 10;
	k = 0;
	G[0][0] += pow(p, -k);
	F[0] += pow(p, -k);
	///////////////////////////////////
	chtype max, coef, tmp;
	vector<chtype> x;
	x.resize(n);
	int max_i = 0;
	for (int i = 0; i < n; i++)
	{
		max = G[i][i];
		max_i = i;
		//Поиск максимального элемента в столбце
		for (int j = i + 1; j < n; j++)
			(abs(G[j][i])>max) ? max_i = j, max = abs(G[j][i]) : 0;
		(max == 0) ? printf("the system has no solutions") : 0;
		//Если это не обрабатываемая строка, то меняем строки
		if (max_i != i)
		{
			//Перестановка в матрице и в векторе 
			for (int k = i; k < n; k++)
				swap(G[i][k], G[max_i][k]);
		}

		//Преобразование матрицы
		for (int j = i + 1; j < n; j++)
		{
			coef = G[j][i] / G[i][i];
			G[j][i] = 0;
			if (coef)
				for (int k = i + 1; k < n; k++)
					G[j][k] = coef * G[i][k] - G[j][k];
		}
	}
	//Решение СЛАУ 
	for (int i = n - 1; i >= 0; i--)
	{
		x[i] = 0;
		tmp = G[i][n-1];
		for (int j = n - 1; j > i; j--)
			tmp -= G[i][j] * x[j];
		x[i] = tmp / G[i][i];
	}
	for (i = 0; i < n; i++)
		F[i] = x[i];
	return;
}