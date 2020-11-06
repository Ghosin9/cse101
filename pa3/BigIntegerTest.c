/*
* BigIntegerTest.c
* Ly Phung
* lynphung
* CSE101
* 11/6/19
* Tester file for BigInteger ADT
*/

#include<stdio.h>
#include<stdlib.h>
#include"BigInteger.h"

int main(int argc, char* argv[])
{
	// BigInteger A = stringToBigInteger("+111122223333");
	// BigInteger B = stringToBigInteger("+222211110000");
	// BigInteger C = copy(A);
	// BigInteger D = stringToBigInteger("-0");
	// BigInteger E = stringToBigInteger("0");

	// printf("A:");
	// printBigInteger(stdout, A);
	// printf("\n");
	// printf("Sign of A: %d", sign(A));
	// printf("\n");

	// printf("B:");
	// printBigInteger(stdout, B);
	// printf("\n");
	// printf("Sign of B: %d", sign(B));
	// printf("\n");

	// printf("C:");
	// printBigInteger(stdout, C);
	// printf("\n");
	// printf("Sign of C: %d", sign(C));
	// printf("\n");

	// printf("compare A to B: %d", compare(A, B));
	// printf("\n");

	// printf("equals A to B: %d", equals(A,B));
	// printf("\n");

	// printf("equals A to C: %d", equals(A,C));
	// printf("\n");

	// add(D, A, B);
	// printf("add of A and B = D:");
	// printBigInteger(stdout, D);
	// printf("\n");
	// printf("Sign of D: %d", sign(D));
	// printf("\n");

	// subtract(C, A, B);
	// printf("sub of A and B = C:");
	// printBigInteger(stdout, C);
	// printf("\n");
	// printf("Sign of C: %d", sign(C));
	// printf("\n");

	// multiply(E, A, B);
	// printf("mult of A and B = E:");
	// printBigInteger(stdout, E);
	// printf("\n");
	// printf("Sign of E: %d", sign(E));
	// printf("\n");

	BigInteger pA = stringToBigInteger("+111122223333");
    BigInteger pB = stringToBigInteger("+222211110000");

    //pos + pos = pos
    printf("case 1\n");
    BigInteger pD = stringToBigInteger("+333333333333");
    BigInteger pC = sum(pA, pB);

    if(!equals(pC, pD)) printf("failed 1\n");

    //-> neg + pos == 0
    printf("case 2\n");
    negate(pA); //A-> -111122223333
    pB = stringToBigInteger("+111122223333");
    pC = sum(pA, pB);
    if(sign(pC) != 0) printf("failed 2\n");

printf("case 3\n");
    //-> neg + pos > 0
   	pB = stringToBigInteger("+112122223333");
    pC = sum(pA, pB);
    if(sign(pC) != 1) printf("failed 3\n");

printf("case 4\n");
    //-> neg + pos < 0
    //negate(*pA);
    pB = stringToBigInteger("+110122223333");
    pC = sum(pA, pB);
    if(sign(pC) != -1) printf("failed 4\n");

printf("case 5\n");
    //-> neg + neg
    pB = stringToBigInteger("-222211110000");
    pD = stringToBigInteger("-333333333333");
    pC = sum(pA, pB);
    if(!equals(pC, pD)) printf("failed 5\n");

	return (EXIT_SUCCESS);
}