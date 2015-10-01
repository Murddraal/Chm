#include "header.h"

void input(vector <vector <chtype>> &matrix, int *n, int *l)
{
	int i, j, jMax, iMin, middle;
	chtype buf=0;
	ifstream fin("size.txt"), au("au.txt"), al("al.txt"), di("di.txt");

	fin >> *n >> *l;
	fin.close();
	matrix.resize(*n);

	for (i = 0; i < *n; i++)
		matrix[i].resize(*l);

	for (i = 0; i< *n; i++)
	{
		for (j = 0; j < (*l - 1) / 2; j++)
			al >> matrix[i][j];
		di >> matrix[i][j];
	}
	di.close(); al.close();
	//DU

	
	middle = (*l - 1) / 2;//горизонтальная координата диагонали
	//"стартовые" позиции i j, с которых начинается прогон по диагонали, за исключением первой итерации. соответствует u12
	jMax = middle + 2; iMin = 0;
	//координаты для первой итерации, соответствует u11
	i = 0; j = middle + 1;
	while (!au.eof())
	{
		while (buf == 0)
			au >> buf;
		//вставляем число в матрицу и смещаемся на одну клетку вниз-влево
		matrix[i++][j--] = buf;
		if (j == middle)//если сместились на середину, то возвращаемся на "стартовое" положение, которое смещается на одну клетку вправо
		{
			i = iMin;
			j = jMax++;
			//если достигли правого края матрицы, то "стартовое" положение начинает смещаться по вертикали вниз
			if (jMax == *l)
			{
				jMax--;
				iMin++;
			}
		}
		buf = 0;

	}

	au.close();
	
}

void LDU(vector <vector<chtype>> &matrix, int n, int l)
{
	int i, j, k, diagj = (l - 1) / 2;
	for (k = 0; k < n; k++)
	{
		i = k;
		D(matrix, i, diagj, k);
		for (j = diagj + 1; j < l; j++)
			U(matrix, k, j, k);
		
		for (j = diagj - 1, i++; (j >= 0)&&(i<n); j--, i++)
		{
			L(matrix, i, j, k);
		}
	}
}


void L(vector <vector<chtype>> &matrix, int i, int j,int t)
{
	int k = 0, border = 0, middle = (matrix[i].size() - 1) / 2, start, b1, b2, b3;
	chtype l, summ = 0;
	start = i - middle;
	if (start < 0)
	{
		start = 0;
	}
	if (t > 0)
	{
		k = start;
		border = j;
		while(border>0)
			
		{
			if (matrix[i][j - border] == 0)
			{
				border--;
				continue;
			}//		l-елементы						d-элементы		u-элементы
			b1 = j - border; b2 = middle + border;
			summ += matrix[i][b1] * matrix[k][middle] * matrix[k][b2];
			k++;
			border--;
		}
	}
	b3 = i - middle + j;
	l = (matrix[i][j] - summ) / matrix[b3][middle];

	matrix[i][j] = l;
}
void D(vector <vector<chtype>> &matrix, int i, int j, int t)
{
	int k = 0, middle = (matrix[i].size() - 1) / 2, border, b1, b2;
	chtype dk, summ=0;
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
		for (k = i-border; k < i; k++, border--)
		{
			b1 = middle - border;
			b2 = middle + border;
			//		l-елементы			d-элементы		u-элементы
			summ += matrix[i][b1] * matrix[k][j] * matrix[k][b2];
		}
	}
	dk = matrix[i][j] - summ;

	matrix[i][j] = dk;
}
void U(vector <vector<chtype>> &matrix, int i, int j, int t)
{
	int k = 0, border = 0, middle = (matrix[i].size() - 1) / 2, start=0, b1, b2;
	chtype u, summ = 0;
	if (t > 0)
	{
		if (i - middle + 1 < 0)
		{
			border = i;
			if (j == matrix[i].size() - 1)
				border = 0;
		}
		else
			border = matrix[i].size() - j - 1;
		
		start = i - border;
		k = start;
		while (border>0)

		
		{
			if (matrix[i][middle - border] == 0)
			{
				border--;
				continue;
			}
			//		l-елементы						d-элементы		u-элементы
			b1 = middle - border;
			b2 = j + border;
			summ += matrix[i][b1] * matrix[k][middle] * matrix[k][b2];
			k++;
			border--;
		}
	}
	u = (matrix[i][j] - summ)/ matrix[i][middle];

	matrix[i][j] = u;
}