/*
* ListTest.c
* Ly Phung
* lynphung
* CSE101
* 11/6/19
* Tester file for List ADT
*/

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[])
{
	List A = newList();
	List B = newList();
	List C;

	for(long i = 0; i < 10; i++)
	{
		append(A, i);
		prepend(B, i);
	}

	printList(stdout, A);
	printf("\n");
	printList(stdout, B);
	printf("\n");
	printf("length of A: %d\n", length(A));
	printf("length of B: %d\n", length(B));

	moveFront(A);
	for(int i = 0; i < 5; i++)
		moveNext(A);

	delete(A);

	moveBack(A);
	for(int i = 0; i < 4; i++)
		movePrev(A);

	insertAfter(A, -2);
	insertBefore(A, -1);

	printList(stdout, A);
	printf("\n");
	printf("length of A: %d\n", length(A));

	deleteFront(A);
	deleteBack(A);

	printList(stdout, A);
	printf("\n");
	printf("length of A: %d\n", length(A));

	C = copyList(A);
	printf("length of C: %d\n", length(C));

	clear(C);
	printf("length of C: %d\n", length(C));

	freeList(&A);
	freeList(&B);
	freeList(&C);

	return(EXIT_SUCCESS);
}

//OUTPUT OF PROGRAM
// 0 1 2 3 4 5 6 7 8 9
// 9 8 7 6 5 4 3 2 1 0
// length of A: 10
// length of B: 10
// 0 1 2 3 -1 4 -2 6 7 8 9
// length of A: 11
// 1 2 3 -1 4 -2 6 7 8
// length of A: 9
// length of C: 9
// length of C: 0