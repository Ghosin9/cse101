/*
* GraphTest.c
* Ly Phung
* lynphung
* CSE101
* 11/20/19
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
	 Graph A = newGraph(99);
	 List L = newList();
	 List C = newList();

	addArc(A, 64, 4);
    addArc(A, 64, 3);
    addArc(A, 42, 2);
    addArc(A, 2, 64);
    addArc(A, 4, 2);
    addArc(A, 3, 42);
    BFS(A, 3);
    getPath(L, A, 64);
    //printList(stdout, L);
    //printf("\n");
    append(C, 3);
    append(C, 42);
    append(C, 2);
    append(C, 64);
    if (!equals(L, C)) printf("1\n");
    moveFront(L);
    BFS(A, 2);
    getPath(L, A, 2);
    // printList(stdout, L);
    // printf("\n");
    append(C, 2);
    if (!equals(L, C)) printf("2\n");
    getPath(L, A, 99);
    if (equals(L, C)) printf("3\n");
    clear(L);
    clear(C);
    append(C, NIL);
    BFS(A, 99);
    getPath(L, A, 2);
    if (!equals(C, L)) printf("4\n");

	// if (getSize(A) != 0) printf("1\n");
 //        addEdge(A, 54, 1);
 //        addEdge(A, 54, 2);
 //        addEdge(A, 54, 3);
 //        addEdge(A, 1, 55);
 //        if (getSize(A) != 4) printf("2 %d\n", getSize(A));
 //        BFS(A, 67);
 //        if (getSize(A) != 4) printf("3 %d\n", getSize(A));
 //        addEdge(A, 55, 2);
 //        if (getSize(A) != 5) printf("4 %d\n", getSize(A));
 //        return 0;

	return(EXIT_SUCCESS);
}