#include "header.h"

void main()
{
	vector <vector <chtype>> matrix;
	int n=0, l=0;
	input(matrix, &n, &l);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < l; j++)
			cout << matrix[i][j] << " ";
		cout << "\n";
	}
	cout << "\n\n\n";

	LDU(matrix, n, l);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < l; j++)
			cout << matrix[i][j] << " ";
		cout << "\n";
	}
	system("pause");
}