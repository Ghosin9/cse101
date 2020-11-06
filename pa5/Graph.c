/*
* Graph.c
* Ly Phung
* lynphung
* CSE101
* 12/1/19
* Implementation file for Graph.h
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"List.h"
#include"Graph.h"

int time =0;

typedef struct GraphObj
{
	List* vertices;
	//white = 0, gray = 1, black = 2
	int* color;
	int* parent;
	int* discover;
	int* finish;

	int order;
	int size;
} GraphObj;

Graph newGraph(int n)
{
	Graph G = malloc(sizeof(GraphObj));
	G->vertices = malloc(sizeof(List)*(n+1));

	G->color = calloc((n+1), sizeof(int));
	G->parent = calloc((n+1), sizeof(int));
	G->discover = calloc((n+1), sizeof(int));
	G->finish = calloc((n+1), sizeof(int));

	for(int x=1; x<n+1; x++)
	{
		G->vertices[x] = newList();
		G->color[x] = 0;
		G->parent[x] = NIL;
		G->discover[x] = UNDEF;
		G->finish[x] = UNDEF;
	}

	G->order =n;
	G->size = 0;

	return G;
}

void freeGraph(Graph* pG)
{
	if(pG!=NULL && *pG!=NULL)
	{
		free(&((*pG)->color));
		free(&((*pG)->parent));
		free(&((*pG)->discover));
		free(&((*pG)->finish));

		int len = getOrder(*pG);
		for(int x=1; x<=len; x++)
		{
			clear((*pG)->vertices[x]);
			freeList(&((*pG)->vertices[x]));
		}

		free(&((*pG)->vertices));
		
		free(*pG);
		*pG = NULL;
	}
}

int getOrder(Graph G)
{
	return G->order;
}

int getSize(Graph G)
{
	return G->size;
}

int getParent(Graph G, int u)
{
	if(u < 1 || u > getOrder(G))
	{
		printf("Graph Error: calling getParent() on an index out of bounds\n");
		exit(1);
	}

	return G->parent[u];
}

int getDiscover(Graph G, int u)
{
	if(u < 1 || u > getOrder(G))
	{
		printf("Graph Error: calling getDiscover() on an index out of bounds\n");
		exit(1);
	}

	return G->discover[u];
}

int getFinish(Graph G, int u)
{
	if(u < 1 || u > getOrder(G))
	{
		printf("Graph Error: calling getFinish() on an index out of bounds\n");
		exit(1);
	}

	return G->finish[u];
}

void addEdge(Graph G, int u, int v)
{
	if(u < 1 || u > getOrder(G))
	{
		printf("Graph Error: calling getPath() on an index out of bounds\n");
		exit(1);
	}

	if(v < 1 || v > getOrder(G))
	{
		printf("Graph Error: calling getPath() on an index out of bounds\n");
		exit(1);
	}

	//adding the v to List u in order
	moveFront(G->vertices[u]);
	int x;
	int len = length(G->vertices[u]);
	for(x=1; x<=len; x++)
	{
		if(get(G->vertices[u]) > v)
		{
			insertBefore(G->vertices[u], v);
			break;
		}
		moveNext(G->vertices[u]);
	}
	if(x==len+1)
	{
		append(G->vertices[u], v);
	}

	//adding the u to List v in order
	moveFront(G->vertices[v]);
	len = length(G->vertices[v]);
	for(x=1; x<=len; x++)
	{
		if(get(G->vertices[v]) > u)
		{
			insertBefore(G->vertices[v], u);
			break;
		}
		moveNext(G->vertices[v]);
	}
	if(x==len+1)
	{
		append(G->vertices[v], u);
	}

	G->size++;
}

void addArc(Graph G, int u, int v)
{
	if(u < 1 || u > getOrder(G))
	{
		printf("Graph Error: calling getPath() on an index out of bounds\n");
		exit(1);
	}

	if(v < 1 || v > getOrder(G))
	{
		printf("Graph Error: calling getPath() on an index out of bounds\n");
		exit(1);
	}

	moveFront(G->vertices[u]);
	int x;
	int len = length(G->vertices[u]);
	for(x=1; x<=len; x++)
	{
		if(get(G->vertices[u]) > v)
		{
			insertBefore(G->vertices[u], v);
			break;
		}
		moveNext(G->vertices[u]);
	}
	if(x==len+1)
	{
		append(G->vertices[u], v);
	}
	G->size++;
}

void Visit(Graph G, int x)
{
	time++;
	G->discover[x] = time;
	G->color[x] = 1;

	//printf("discovered: %d at time: %d\n", x, time);

	int len = length(G->vertices[x]);
	moveFront(G->vertices[x]);
	for(int y = 1; y <= len; y++)
	{
		if(G->color[get(G->vertices[x])] == 0)
		{
			G->parent[get(G->vertices[x])] = x;
			Visit(G, get(G->vertices[x]));
		}
		moveNext(G->vertices[x]);
	}

	G->color[x] = 2;
	time++;
	G->finish[x] = time;

	//printf("finished: %d at time: %d\n", x, time);
}

void DFS(Graph G, List S)
{
	if(length(S)!=getOrder(G))
	{
		printf("Graph Error: calling DFS on a List length not equal to Graph order\n");
		exit(1);
	}

	for(int x =1; x<=getOrder(G); x++)
	{
		G->color[x] = 0; //change color to white
		G->parent[x] = NIL; //parent == NIL
	}

	time = 0;

	moveFront(S);
	int len = length(S);
	for(int x=1; x<=len; x++)
	{
		if(G->color[get(S)]==0)
			Visit(G, get(S));
		moveNext(S);
	}

	//ordering List S
	clear(S);
	int low = len*2;
	int index = 0;
	int val = 0;
	int x, y;

	for(x=1; x<=len; x++)
	{
		low = len*2;
		for(y=1; y<=len; y++)
		{
			if(G->finish[y] <= low && G->finish[y]>val)
			{
				low = G->finish[y];
				index = y;
			}
		}

		prepend(S, index);
		val = G->finish[index];
	}
}

Graph transpose(Graph G)
{
	Graph H = newGraph(getOrder(G));
	for(int x=1; x<=getOrder(G); x++)
	{
		int len = length(G->vertices[x]);
		moveFront(G->vertices[x]);
		for(int y=0; y<len; y++)
		{
			addArc(H, get(G->vertices[x]), x);
			moveNext(G->vertices[x]);
		}
	}

	return H;
}

Graph copyGraph(Graph G)
{
	Graph H = newGraph(getOrder(G));
	//memleaks since copyList creates a newList Obj
	for(int x=1; x<=getOrder(G); x++)
	{
		H->vertices[x] = copyList(G->vertices[x]);
		H->color[x] = G->color[x];
		H->parent[x] = G->parent[x];
		H->discover[x] = G->discover[x];
		H->finish[x] = G->finish[x];
	}

	return H;
}

void printGraph(FILE* out, Graph G)
{
	for(int x=1; x<=getOrder(G); x++)
	{
		fprintf(out, "%d: ", x);
		moveFront(G->vertices[x]);
		for(int i =0; i<length(G->vertices[x]); i++)
		{
			fprintf(out, "%d ", get(G->vertices[x]));
			moveNext(G->vertices[x]);
		}
		fprintf(out, "\n");
	}
	fprintf(out, "\n");
}