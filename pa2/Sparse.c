/*
* Sparse.c
* Ly Phung
* lynphung
* CSE101
* 10/20/19
* Handles input and output files and uses Matrix.c and List.c 
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Matrix.h"

#define MAX_LEN 256

int main(int argc, char* argv[])
{
	//check command line #
	if (argc!= 3)
	{
		printf("Usage: Sparse <input file> <output file>\n");
		exit(1);
	}

	FILE *in, *out;
	int size, a, b;
	int i, j;
	double x;

	in = fopen(argv[1], "r");
	if(in==NULL)
	{
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}

	out = fopen(argv[2], "w");
	if(out == NULL)
	{
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}

	fscanf(in, "%d %d %d", &size, &a, &b);
	Matrix A = newMatrix(size);
	Matrix B = newMatrix(size);

	//for Matrix A
	for(int y=0; y<a; y++)
	{
		fscanf(in, "%d %d %lf", &i, &j, &x);
		//printf("A:adding %.1f @ %d %d\n", x, i, j);
		changeEntry(A, i, j, x);
	}

	//for Matrix B
	for(int y=0; y<b; y++)
	{
		fscanf(in, "%d %d %lf", &i, &j, &x);
		//printf("B:adding %.1f @ %d %d\n", x, i, j);
		changeEntry(B, i, j, x);
	}

	Matrix scalar;
	Matrix AplusB;
	Matrix AplusA;
	Matrix BminusA;
	Matrix AminusA;
	Matrix TA;
	Matrix AmultB;
	Matrix BmultB;

	fprintf(out, "A has %d non-zero entries:\n", a);
	printMatrix(out, A);
	fprintf(out, "\n");

	fprintf(out, "B has %d non-zero entries:\n", b);
	printMatrix(out, B);
	fprintf(out, "\n");

	fprintf(out, "(1.5)*A =\n");
	scalar = scalarMult(1.5, A);
	printMatrix(out, scalar);
	fprintf(out, "\n");

	fprintf(out, "A+B =\n");
	AplusB = sum(A, B);
	printMatrix(out, AplusB);
	fprintf(out, "\n");

	fprintf(out, "A+A =\n");
	AplusA = sum(A, A);
	printMatrix(out, AplusA);
	fprintf(out, "\n");

	fprintf(out, "B-A =\n");
	BminusA = diff(B, A);
	printMatrix(out, BminusA);
	fprintf(out, "\n");

	fprintf(out, "A-A =\n");
	AminusA = diff(A, A);
	printMatrix(out, AminusA);
	fprintf(out, "\n");

	fprintf(out, "Transpose(A) =\n");
	TA = transpose(A);
	printMatrix(out, TA);
	fprintf(out, "\n");

	fprintf(out, "A*B =\n");
	AmultB = product(A, B);
	printMatrix(out, AmultB);
	fprintf(out, "\n");

	fprintf(out, "B*B =\n");
	BmultB = product(B, B);
	printMatrix(out, BmultB);
	fprintf(out, "\n");

	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&scalar);
	freeMatrix(&AplusB);
	freeMatrix(&AplusA);
	freeMatrix(&BminusA);
	freeMatrix(&AminusA);
	freeMatrix(&TA);
	freeMatrix(&AmultB);
	freeMatrix(&BmultB);

	fclose(in);
	fclose(out);

	return EXIT_SUCCESS;
}