/*
* GraphTest.c
* Ly Phung
* lynphung
* CSE101
* 12/1/19
* Tester file for Graph.c
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"List.h"
#include"Graph.h"

int main(int argc, char* argv[])
{
	Graph A = newGraph(100);
	List L = newList();

	addArc(A, 64, 4);
    addArc(A, 64, 3);
    addArc(A, 42, 2);
    addArc(A, 2, 64);
    addArc(A, 4, 2);
    addArc(A, 3, 42);

    printGraph(stdout, A);

    for (int i = 1; i <= 100; i++) {
      prepend(L, i);
    }

    DFS(A, L);

    // for(int x=1; x<=getOrder(A); x++)
    // {
    // 	printf("%d: %d\n", x, getDiscover(A, x));
    // }
    // printList(stdout, L);
    // printf("\n");

    if (getDiscover(A, 100) != 1) printf("2, discover of 100: %d\n", getDiscover(A, 100));
    if (getDiscover(A, 64) != 73) printf("3, discover of 64: %d\n", getDiscover(A, 64));
    if (getDiscover(A, 4) != 80) printf("4, discover of 4: %d\n", getDiscover(A, 4));
    DFS(A, L);

    // for(int x=1; x<=getOrder(A); x++)
    // {
    // 	printf("%d: %d\n", x, getDiscover(A, x));
    // }
    // printList(stdout, L);
    // printf("\n");

    if (getDiscover(A, 4) != 126) printf("5, discover of 4: %d\n", getDiscover(A, 4));
    if (getDiscover(A, 63) != 117) printf("6, discover of 63: %d\n", getDiscover(A, 63));
    DFS(A, L);
    if (getDiscover(A, 65) != 71) printf("7, discover of 65: %d\n", getDiscover(A, 65));
    if (getDiscover(A, 1) != 199) printf("8, discover of 1: %d\n", getDiscover(A, 1));

	return(EXIT_SUCCESS);
}