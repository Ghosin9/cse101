/*
* Graph.c
* Ly Phung
* lynphung
* CSE101
* 11/20/19
* Implementation file for Graph.h
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"List.h"
#include"Graph.h"

typedef struct GraphObj
{
	List* vertices;
	//white = 0, gray = 1, black = 2
	int* color;
	int* parent;
	int* distance;

	int order;
	int size;
	int source;
} GraphObj;

Graph newGraph(int n)
{
	Graph G = malloc(sizeof(GraphObj));
	G->vertices = malloc(sizeof(List)*(n+1));

	G->color = calloc((n+1), sizeof(int));
	G->parent = calloc((n+1), sizeof(int));
	G->distance = calloc((n+1), sizeof(int));

	for(int x=1; x<n+1; x++)
	{
		G->vertices[x] = newList();
		G->color[x] = 0;
		G->parent[x] = NIL;
		G->distance[x] = INF;
	}

	G->order =n;
	G->size = 0;
	G->source = NIL;

	return G;
}

void freeGraph(Graph* pG)
{
	if(pG!=NULL && *pG!=NULL)
	{
		free((*pG)->color);
		free((*pG)->parent);
		free((*pG)->distance);

		makeNull(*pG);

		free((*pG)->vertices);
		
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

int getSource(Graph G)
{
	return G->source;
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

int getDist(Graph G, int u)
{
	if(u < 1 || u > getOrder(G))
	{
		printf("Graph Error: calling getDist() on an index out of bounds\n");
		exit(1);
	}

	return G->distance[u];
}

void getPath(List L, Graph G, int u)
{
	if(u < 1 || u > getOrder(G))
	{
		printf("Graph Error: calling getPath() on an index out of bounds\n");
		exit(1);
	}

	if(getSource(G)==NIL)
	{
		printf("Graph Error: calling getPath() on a NIL source reference\n");
		exit(1);
	}

	//printf("getting path between: %d and %d\n", getSource(G), u);

	int temp =u;
	while(G->parent[temp]!=NIL)
	{
		temp = G->parent[temp];
		//printf("prepending: %d\n", temp);
		prepend(L, temp);
		if(temp==G->source)
			break;
	}
	append(L, u);

	if(u!=getSource(G) && G->parent[u]==NIL)
	{
		clear(L);
		append(L, NIL);
	}
}

void makeNull(Graph G)
{
	int len = getOrder(G);
	for(int x=1; x<=len; x++)
	{
		G->parent[x] = NIL;
		G->distance[x] = INF;
		clear(G->vertices[x]);
		freeList(&(G->vertices[x]));
	}
	G->order = 0;
	G->size = 0;
	G->source = NIL;
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

void BFS(Graph G, int s)
{
	for(int i=1; i<=getOrder(G); i++)
	{
		G->color[i]=0;
		G->distance[i]=INF;
		G->parent[i]=NIL;
	}

	//source node
	G->source = s;
	G->color[s] = 1;
	G->distance[s] = 0;
	G->parent[s] = NIL;

	List Q = newList();
	append(Q, s);

	//printf("source: %d\n", s);

	while(length(Q)!=0)
	{
		moveFront(Q);
		int x = get(Q);
		deleteFront(Q);

		//printf("checking: %d\n", x);

		moveFront(G->vertices[x]);
		for(int y=1; y<=length(G->vertices[x]); y++)
		{
			if(G->color[get(G->vertices[x])]==0) //if color is white
			{
				//printf("adjacent to %d: %d\n", x, get(G->vertices[x]));

				G->color[get(G->vertices[x])]=1; //change to gray
				G->distance[get(G->vertices[x])] = G->distance[x]+1;

				//printf("distance from source %d: %d\n", s, G->distance[get(G->vertices[x])]);

				G->parent[get(G->vertices[x])] = x;

				//printf("parent of %d: %d\n", get(G->vertices[x]), x);

				append(Q, get(G->vertices[x]));
			}
			moveNext(G->vertices[x]);
		}

		G->color[x] = 2;
	}
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