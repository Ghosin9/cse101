/*
* Arithmetic.c
* Ly Phung
* lynphung
* CSE101
* 11/6/19
* Top level program that uses List.h and BigInteger.h
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"BigInteger.h"
#include"List.h"

int main(int argc, char* argv[])
{
	if (argc!= 3)
	{
		printf("Usage: Arithmetic <input file> <output file>\n");
		exit(1);
	}

	FILE *in, *out;

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

	int digitsA =0;
	fscanf(in, "%d", &digitsA);
	char lineA[digitsA+1];

	fscanf(in, "%s", lineA);
	//printf("A String: %s\n", lineA);

	int digitsB = 0;
	fscanf(in, "%d", &digitsB);
	char lineB[digitsB+1];

	fscanf(in, "%s", lineB);
	//printf("B String: %s\n", lineB);

	BigInteger A = stringToBigInteger(lineA);
	BigInteger B = stringToBigInteger(lineB);
	BigInteger C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R;

	printf("A\n");
	printBigInteger(out, A);
	fprintf(out, "\n");

	printf("B\n");
	printBigInteger(out, B);
	fprintf(out, "\n");

	printf("A+B\n");
	C = sum(A, B);
	printBigInteger(out, C);
	fprintf(out, "\n");

	printf("A-B\n");
	D = diff(A, B);
	printBigInteger(out, D);
	fprintf(out, "\n");

	printf("A-A\n");
	E = diff(A, A);
	printBigInteger(out, E);
	fprintf(out, "\n");

	printf("3A-2B\n");
	F = sum(A, A);
	add(F, A, F);
	G = sum(B, B);
	H = diff(C, D);
	printBigInteger(out, H);
	fprintf(out, "\n");

	printf("AB\n");	
	I = prod(A, B);
	printBigInteger(out, I);
	fprintf(out, "\n");

	printf("AA\n");
	J = prod(A, A);
	printBigInteger(out, J);
	fprintf(out, "\n");

	printf("BB\n");	
	K = prod(B, B);
	printBigInteger(out, K);
	fprintf(out, "\n");

	printf("9A + 16B\n");
	L = copy(A);
	for(int x=0; x <4; x++)
		multiply(L, L, A);
	M = stringToBigInteger("9");
	N = prod(L, M);

	O = copy(B);
	for(int x=0; x<5; x++)
		multiply(O, O, B);
	P = stringToBigInteger("16");
	Q = prod(O, P);

	R = sum(N, Q);
	printBigInteger(out, R);
	fprintf(out, "\n");

	fclose(in);
	fclose(out);

	freeBigInteger(&A);
	freeBigInteger(&B);
	freeBigInteger(&C);
	freeBigInteger(&D);
	freeBigInteger(&E);
	freeBigInteger(&F);
	freeBigInteger(&G);
	freeBigInteger(&H);
	freeBigInteger(&I);
	freeBigInteger(&J);
	freeBigInteger(&K);
	freeBigInteger(&L);
	freeBigInteger(&M);
	freeBigInteger(&N);
	freeBigInteger(&O);
	freeBigInteger(&P);
	freeBigInteger(&Q);
	freeBigInteger(&R);

	return(EXIT_SUCCESS);
}