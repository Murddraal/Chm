#include "header.h"

void main()
{
	matrix Matrix;

	input(Matrix);

	for (int i = 0; i < Matrix.n; i++)
	{
		for (int j = 0; j < Matrix.middle; j++)
			printf("%f ", Matrix.L[i][j]);
		printf("%f ", Matrix.D[i]);
		for (int j = 0; j < Matrix.middle; j++)
			printf("%f ", Matrix.U[i][j]);
		printf("\n");
	}

	printf("\n\n\n");
	LDU(Matrix);


	for (int i = 0; i < Matrix.n; i++)
	{
		for (int j = 0; j < Matrix.middle; j++)
			printf("%f ", Matrix.L[i][j]);
		printf("%f ", Matrix.D[i]);
		for (int j = 0; j < Matrix.middle; j++)
			printf("%f ", Matrix.U[i][j]);
		printf("\n");
	}



}