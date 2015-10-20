#include "header.h"

void main()
{
	Matrix matrix;

	matrix.input();

	matrix.output();

	printf("\n\n\n");
	matrix.LDU();

	matrix.output();

	matrix.multyplyL();
	matrix.multyplyD();
	matrix.multyplyU();
	printf("\n\n\n");
	matrix.vewVector(false);

	



}