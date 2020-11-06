/*
* FindPath.c
* Ly Phung
* lynphung
* CSE101
* 11/20/19
* File that uses List.c and Graph.c to find the shortest path between vertices
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

	//making graph
	int x =1, y=1;
	while(x!=0 || y !=0)
	{
		fscanf(in, "%d %d", &x, &y);
		if(x==0 && y ==0)
			break;
		//printf("adding: %d %d\n", x, y);
		addEdge(G, x, y);
	}

	fprintf(out, "\n");

	printGraph(out, G);

	x=1;
	y=1;
	while(x!=0 || y!=0)
	{
		//printf("inside BFS loop\n");

		fscanf(in, "%d %d", &x, &y);

		if(x==0 && y==0)
			break;

		BFS(G, x);
		if(getDist(G, y)==-1)
		{
			fprintf(out, "The distance from %d to %d is infinity\n", x, y);
			fprintf(out, "No %d-%d path exists\n", x, y);
		}
		else
		{
			fprintf(out, "The distance from %d to %d is %d\n", x, y, getDist(G, y));
			fprintf(out, "A shortest %d-%d path is: ", x, y);

			List L = newList();
			getPath(L, G, y);
			printList(out, L);
			fprintf(out, "\n");
			freeList(&L);
		}
		fprintf(out, "\n");
	}

	return(EXIT_SUCCESS);
}