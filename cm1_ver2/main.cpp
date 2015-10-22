#include "header.h"

void main()
{
	Matrix matrix;
	int choice, size, infile2;
	bool infile1;
	printf("1) matrix from file\n2) gilbert\n3) gauss\n");
	scanf("%d", &choice);
	if (choice == 1)
	{
		matrix.input();
		matrix.LDU();

		matrix.multyplyL();
		matrix.multyplyD();
		matrix.multyplyU();
	}
	if (choice == 2)
	{		
		printf("size: ");
		scanf("%d", &size);
		matrix.gilbert(size);
		matrix.LDU();

		matrix.multyplyL();
		matrix.multyplyD();
		matrix.multyplyU();
	}
	else
	{
		matrix.gauss();
	}

	printf("\n\n\n");
	printf("Write vector in 'vector x.txt'?\n1 - yes, 0 - no\n");
	
	scanf("%d", &infile2);
	if (infile2 == 0)
		infile1 = false;
	else
		infile1 = true;
	matrix.vewVector(infile1);	

	return;

}