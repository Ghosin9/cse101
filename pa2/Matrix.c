/*
* Matrix.c
* Ly Phung
* lynphung
* CSE101
* 10/20/19
* Implementation file for Matrix.h
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Matrix.h"
#include"List.h"

//Matrix
typedef struct MatrixObj
{
	List* rows;
	int size;
	int nonzero;
} MatrixObj;

//Entry
typedef struct EntryObj
{
	int col;
	double val;
} EntryObj;

typedef EntryObj* Entry;

//Matrix base
Matrix newMatrix(int n)
{
	Matrix M = malloc(sizeof(MatrixObj));
	assert(M!=NULL);
	M->rows = malloc(sizeof(List) * n);
	for(int x=0; x<n; x++)
	{
		M->rows[x] = newList();
		//printf("%d\n", length(M->rows[x]));
	}
	M->size = n;
	M->nonzero = 0;
	return(M);
}

void freeMatrix(Matrix* pM)
{
	if(pM!=NULL && *pM!=NULL)
	{
		makeZero(*pM);
		for(int x=0; x<size(*pM); x++)
			freeList(&((*pM)->rows[x]));
		free((*pM)->rows);
		free(*pM);
		*pM = NULL;
	}
}

//Entry base
Entry newEntry(int c, double v)
{
	Entry E = malloc(sizeof(EntryObj));
	E->col = c;
	E->val = v;
	return(E);
}

//access functions
int size(Matrix M)
{
	if (M==NULL)
	{
		printf("Matrix Error: calling size() on a NULL Matrix reference\n");
		exit(1);
	}

	return M->size;
}

int NNZ(Matrix M)
{
	if (M==NULL)
	{
		printf("Matrix Error: calling NNZ() on a NULL Matrix reference\n");
		exit(1);
	}

	return M->nonzero;
}

int equals(Matrix A, Matrix B)
{
	if(size(A)!=size(B))
		return 0;

	if(size(A) == 0 && size(B) == 0)
		return 1;

	//loop through the matrix's and compare each element, first checking col and then checking value
	for(int x=0; x<size(A); x++)
	{
		List a = A->rows[x];
		List b = B->rows[x];

		if (length(a)!=length(b))
			return 0;

		Entry Ea = NULL;
		Entry Eb = NULL;
		moveFront(a);
		moveFront(b);

		for(int x=0; x<length(a); x++)
		{
			Ea = (Entry)get(a);
			Eb = (Entry)get(b);

			if(Ea->col!=Eb->col)
				return 0;
			if(Ea->val!=Eb->val)
				return 0;

			moveNext(a);
			moveNext(b);
		}
	}
	return 1;
}

//manipulation functions
void makeZero(Matrix M)
{
	//loop through each list and call clear on all lists
	int s = size(M);
	for(int x=0; x<s; x++)
	{
		clear(M->rows[x]);
	}
	M->nonzero = 0;
}

void changeEntry(Matrix M, int i, int j, double x) //runtime 0(a)
{
	if(i>size(M)|| i<1)
	{
		printf("Matrix Error: calling changeEntry() on i out of bounds\n");
		exit(1);
	}

	if(j>size(M) || j<1)
	{
		printf("Matrix Error: calling changeEntry() on j out of bounds\n");
		exit(1);
	}

	//printf("adding %.1f at %d %d\n", x, i, j);

	List L = M->rows[i-1];
	if(length(L)==0)
	{
		//case 0 if the list is empty and x=0 (do nothing)
		//case 1 if the list is empty and x!=0
		//printf("case 0 & 1\n");
		if(x!=0)
		{
			append(L, newEntry(j, x));
			M->nonzero++;
		}
		//printMatrix(stdout, M);
		return;
	}

	//looping through the list to see if the entry exists
	moveFront(L);
	for(int y=0; y<length(L); y++)
	{
		Entry E = (Entry)get(L);
		if(j==E->col)
		{
			//case 2 if value exists & x=0
			//printf("case 2 & 3\n");
			if(x==0)
			{
				delete(L);
				M->nonzero--;
			}
			else //case 3 if value exits & x!=0
				E->val = x;
			//printMatrix(stdout, M);
			return;
		}
		else if(j<E->col)
		{
			//case 4 if value dne & x=0 (do nothing)
			//case 5 if value dne and x!=0
			//printf("case 4 & 5\n");
			if(x!=0)
			{
				insertBefore(L, newEntry(j, x));
				M->nonzero++;
			}
			//printMatrix(stdout, M);
			return;
		}
		else if (y==length(L)-1)
		{
			//case 6 if at end of list and x=0 (do nothing)
			//case 7 if at end of list and x!=0
			//printf("case 6 & 7\n");
			if(x!=0)
			{
				insertAfter(L, newEntry(j, x));
				M->nonzero++;
				//printMatrix(stdout, M);
			}
			//printMatrix(stdout, M);
			return;
		}
		moveNext(L);
	}
}

//operation functions
Matrix copy(Matrix A) //runtime 0(n+a)
{
	int s = size(A);
	Matrix B = newMatrix(s);

	//loop through matrix A to copy over everything
	for(int x=0; x<s; x++)
	{
		List a = A->rows[x];

		moveFront(a);
		for(int y=0; y<length(a); y++)
		{
			Entry e = (Entry)get(a);

			changeEntry(B, x+1, e->col, e->val);
			moveNext(a);
		}
	}

	return(B);
}

Matrix transpose(Matrix A) //runtime 0(n+a)
{
	Matrix B = newMatrix(size(A));

	for(int x=0; x<size(A); x++)
	{
		List a = A->rows[x];

		moveFront(a);
		for(int y=0; y<length(a); y++)
		{
			Entry e = (Entry)get(a);

			changeEntry(B, e->col, x+1, e->val);
			moveNext(a);
		}
	}
	return(B);
}

Matrix scalarMult(double x, Matrix A) //runtime 0(n+a)
{
	Matrix B = newMatrix(size(A));

	for(int z=0; z<size(A); z++)
	{
		List a = A->rows[z];

		moveFront(a);
		for(int y=0; y<length(a); y++)
		{
			Entry e = (Entry)get(a);

			changeEntry(B, z+1, e->col, e->val*x);
			moveNext(a);
		}
	}
	return(B);
}

Matrix sum(Matrix A, Matrix B) //runtime 0(n+a+b)
{
	if(size(A)!=size(B))
	{
		printf("Matrix Error: calling sum() on different sized Matrices\n");
		exit(1);
	}

	//if same matrix pointer
	if(A==B)
	{
		return scalarMult(2.0, A);
	}

	Matrix C = newMatrix(size(A));

	for(int i=0; i<size(A); i++)
	{
		List a = A->rows[i];
		List b = B->rows[i];

		moveFront(a);
		moveFront(b);

		Entry Ea, Eb;

		while(index(a) != -1 || index(b) !=-1)
		{
			if(index(a)>=0 && index(b)>=0) //if not at the end of the list
			{
				Ea = (Entry)get(a);
				Eb = (Entry)get(b);

				//case 1, if cols are ==
				if(Ea->col == Eb->col)
				{
					changeEntry(C, i+1, Ea->col, Ea->val + Eb->val);
					moveNext(a);
					moveNext(b);
				}
				else if (Ea->col > Eb->col)//case 2 if a->col > b->col
				{
					changeEntry(C, i+1, Eb->col, Eb->val);
					moveNext(b);
				}
				else //case 3 if b->col > a->col
				{
					changeEntry(C, i+1, Ea->col, Ea->val);
					moveNext(a);
				}
			}
			else if (index(a)>=0) //if at the end of list b, but not a
			{
				//case 4 if at end of list b, but not a
				Ea = (Entry)get(a);
				changeEntry(C, i+1, Ea->col, Ea->val);
				moveNext(a);
			}
			else //if at the end of list a, but not b
			{
				printf("case5\n");
				//case 5 if at end of list a, but not b
				Eb = (Entry)get(b);
				changeEntry(C, i+1, Eb->col, Eb->val);
				moveNext(b);
			}
		}
	}

	return(C);
}

Matrix diff(Matrix A, Matrix B) //runtime 0(n+a+b)
{
	if(size(A)!=size(B))
	{
		printf("Matrix Error: calling sum() on different sized Matrices\n");
		exit(1);
	}

	//if same matrix pointer
	if(A==B)
	{
		return scalarMult(0.0, A);
	}

	Matrix C = newMatrix(size(A));

	for(int i=0; i<size(A); i++)
	{
		List a = A->rows[i];
		List b = B->rows[i];

		moveFront(a);
		moveFront(b);

		Entry Ea, Eb;

		while(index(a) != -1 || index(b) !=-1)
		{
			if(index(a)>=0 && index(b)>=0) //if not at the end of the list
			{
				Ea = (Entry)get(a);
				Eb = (Entry)get(b);

				//case 1, if cols are ==
				if(Ea->col == Eb->col)
				{
					changeEntry(C, i+1, Ea->col, Ea->val - Eb->val);
					moveNext(a);
					moveNext(b);
				}
				else if (Ea->col > Eb->col)//case 2 if a->col > b->col
				{
					changeEntry(C, i+1, Eb->col, 0.0-Eb->val);
					moveNext(b);
				}
				else //case 3 if b->col > a->col
				{
					changeEntry(C, i+1, Ea->col, Ea->val);
					moveNext(a);
				}
			}
			else if (index(a)>=0) //if at the end of list b, but not a
			{
				//case 4 if at end of list b, but not a
				Ea = (Entry)get(a);
				changeEntry(C, i+1, Ea->col, Ea->val);
				moveNext(a);
			}
			else //if at the end of list a, but not b
			{
				//case 5 if at end of list a, but not b
				Eb = (Entry)get(b);
				changeEntry(C, i+1, Eb->col, 0.0-Eb->val);
				moveNext(b);
			}

		}
	}

	return(C);
}

double vectorDot(List P, List Q)
{
	//printf("inside dot\n");
	double dot =0;

	Entry p, q;

	moveFront(P);
	moveFront(Q);
	while(index(P)!=-1 || index(Q)!=-1)
	{
		//printf("P:%d, Q:%d\n", index(P), index(Q));
		if(index(P)>=0 && index(Q)>=0) //if not at the end of either list
		{
			p = (Entry)get(P);
			q = (Entry)get(Q);

			//case 1 if both cols are ==
			if(p->col == q->col)
			{
				//printf("case1\n");
				dot += p->val * q->val;
				moveNext(P);
				moveNext(Q);
			}
			else if (p->col > q->col) //case 2 if p->col > q->col
			{
				//printf("case2\n");
				moveNext(Q);
			}
			else //case 3 if q->col > p->col
			{
				//printf("case3\n");
				moveNext(P);
			}
		}
		else if (index(P)>=0)
		{
			//case 4 if at the end of list Q but not P
			moveNext(P);
		}
		else
		{
			//case 5 if at the end of list P but not Q
			moveNext(Q);
		}
	}

	return dot;
}

Matrix product(Matrix A, Matrix B) //runtime 0(n^2+a+b)
{
	Matrix C = newMatrix(size(A));
	Matrix D = transpose(B);

	for(int i=0; i<size(A); i++)
	{
		//printf("changing row\n");
		List a = A->rows[i];
		for(int j=0; j<size(A); j++)
		{
			//printf("changing col\n");
			List d = D->rows[j];
			double dot = vectorDot(a, d);
			//printf("%.1f\n", dot);
			changeEntry(C, i+1, j+1, dot);
		}
	}

	return(C);
}

void printMatrix(FILE* out, Matrix M)
{
	List L = NULL;

	for(int i=0; i<size(M); i++)
	{
		L = M->rows[i];
		moveFront(L);
		for(int j=0; j<length(L); j++)
		{
			Entry E = (Entry)get(L);
			if (j==0)
			{
				fprintf(out, "%d: (%d, %.1f)", i+1, E->col, E->val);
				if(length(L)==2)
					fprintf(out, " ");
			}
			else if (j==length(L)-1)
				fprintf(out, "(%d, %.1f)", E->col, E->val);
			else
				fprintf(out, " (%d, %.1f) ", E->col, E->val);

			if(j==length(L)-1)
				fprintf(out, "\n");
			moveNext(L);
		}
	}
}