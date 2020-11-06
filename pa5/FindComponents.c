/*
* FindComponents.c
* Ly Phung
* lynphung
* CSE101
* 12/1/19
* File that uses List.c and Graph.c to find connect components in a DFS graph
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"List.h"
#include"Graph.h"

int main(int argc, char* argv[])
{
	//check command line for the correct number of arguments
	if (argc!= 3)
	{
		printf("Usage: FindPath <input file> <output file>");
	}

	//opening file
	FILE *in, *out;
	in = fopen(argv[1], "r");
	if(in==NULL)
	{
		printf("Unable to open file %s for reading", argv[1]);
		exit(1);
	}

	out = fopen(argv[2], "w");
	if(out == NULL)
	{
		printf("Unable to open file %s for writing", argv[2]);
		exit(1);
	}

	int order =0;
	fscanf(in, "%d", &order);

	Graph G = newGraph(order);
	List L = newList();
	for(int x=1; x<=order; x++)
		append(L, x);

	//making graph
	int x =1, y=1;
	while(x!=0 || y !=0)
	{
		fscanf(in, "%d %d", &x, &y);
		if(x==0 && y ==0)
			break;
		//printf("adding: %d %d\n", x, y);
		addArc(G, x, y);
	}

	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);
	//printGraph(stdout, G);

	DFS(G, L);

	Graph H = transpose(G);
	//printGraph(stdout, H);

	DFS(H, L);
	printList(stdout, L);

	int components = 0;
	//printf("order: %d\n", order);
	for(int x=order; x>=1; x--)
	{
		if(getParent(H, x) == NIL)
			components++;
		//printf("parent: %d\n", getParent(H, x));
	}
	fprintf(out, "G contains %d strongly connected components:\n", components);

	List stack = newList();
	moveBack(L);
	components = 1;
	for(int x=1; x<=order; x++)
	{
		if(getParent(H, get(L))==NIL)
		{
			fprintf(out, "Component %d: ", components);
			prepend(stack, get(L));
			printList(out, stack);
			fprintf(out, "\n");
			clear(stack);
			components++;
		}
		else
			prepend(stack, get(L));
		movePrev(L);
	}

	return(EXIT_SUCCESS);
}