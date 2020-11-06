/*
* MatrixTest.c
* Ly Phung
* lynphung
* CSE101
* 10/20/19
* Testerfile for Matrix
*/

#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"

int main(int argc, char* argv[])
{
	int n = 2;
	Matrix A = newMatrix(n);
	Matrix B = newMatrix(n);
	Matrix C, D, E, F, G, H, I, J;

	changeEntry(A, 1,1,1); changeEntry(A, 1,2,2);
 	changeEntry(A, 2,1,3); changeEntry(A, 2,2,4);

 	printf("finished Change Entry on A\n");

 	changeEntry(B, 1,1,0); changeEntry(B, 1,2,4);
	changeEntry(B, 2,1,2); changeEntry(B, 2,2,0);

	printf("finished Change Entry on B\n");

	//print out 4
	printf("%d\n", NNZ(A));
   	printMatrix(stdout, A);
   	printf("\n");

   	//print out 2
   	printf("%d\n", NNZ(B));
  	printMatrix(stdout, B);
   	printf("\n");

   	//print true
   	C = copy(A);
   	printf("Does C equal A? %s\n\n", equals(A, C)?"true":"false" );

   	//tranpose of A&B
   	D =transpose(A);
   	printf("transpose of A\n");
   	printMatrix(stdout, D);
   	printf("\n");

   	E = transpose(B);
   	printf("transpose of B\n");
   	printMatrix(stdout, E);
   	printf("\n");

   	//tranpose of A&B
   	F = scalarMult(2.0, A);
   	printf("scalarMult x2 of A\n");
   	printMatrix(stdout, F);
   	printf("\n");

   	G = scalarMult(3.0, B);
   	printf("scalarMult x3 of B\n");
   	printMatrix(stdout, G);
   	printf("\n");

   	//sum of A&B
   	H = sum(A, B);
   	printf("sum of A & B\n");
   	printMatrix(stdout, H);
   	printf("\n");

   	//diff of A&B
   	I = diff(A, B);
   	printf("diff of A & B\n");
   	printMatrix(stdout, I);
   	printf("\n");

	//product of A and B
   	J = product(A, B);
   	printf("product of A & B\n");
   	printMatrix(stdout, J);
   	printf("\n");

   	makeZero(A);
   	//print 0
   	printf("%d\n", NNZ(A));
   	printMatrix(stdout, A);
   	printf("\n");

   	freeMatrix(&A);
   	freeMatrix(&B);
   	freeMatrix(&C);
   	freeMatrix(&D);
   	freeMatrix(&E);
   	freeMatrix(&F);
   	freeMatrix(&G);
   	freeMatrix(&H);
   	freeMatrix(&I);
   	freeMatrix(&J);

	//sum_getNNZ test 1-----------------------------------------------------
	// Matrix A = newMatrix(3);

	// changeEntry(A, 1, 1, 4); changeEntry(A, 1, 2, 2); changeEntry(A, 1, 3, 0);
 //    changeEntry(A, 2, 1, 2); changeEntry(A, 2, 2, 2);
 //    changeEntry(A, 3, 1, 0); 						  changeEntry(A, 3, 3, 0);

 //    printf("%d\n", NNZ(A));
	// printMatrix(stdout, A);
	// printf("\n");

 //    Matrix B = sum(A, A);

 //    printf("%d\n", NNZ(B));
	// printMatrix(stdout, B);
	// printf("\n");

   	return EXIT_SUCCESS;
}