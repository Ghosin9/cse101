/*
* List.c
* Ly Phung
* lynphung
* CSE101
* 10/20/19
* Implementation file for List.h
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"List.h"

//Node
typedef struct NodeObj
{
	void* value;
	struct NodeObj* next;
	struct NodeObj* prev;
} NodeObj;

typedef NodeObj* Node;

Node newNode(void* v)
{
	Node N = malloc(sizeof(NodeObj));
	assert(N!=NULL);
	N->value = v;
	N->next = NULL;
	N->prev = NULL;
	return(N);
}

void freeNode(Node* pN)
{
	if(pN!=NULL && *pN!=NULL)
	{
		free((*pN)->value);
		free(*pN);
		*pN = NULL;
	}
}

//List
typedef struct ListObj
{
	Node cursor;
	Node front;
	Node back;
	int length;
	int index;
} ListObj;

List newList(void)
{
	List L = malloc(sizeof(ListObj));
	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	return(L);
}

void freeList(List* pL)
{
	if(pL!=NULL && *pL!=NULL)
	{
		if(length(*pL)>0)
			clear(*pL);
		free(*pL);
		*pL = NULL;
	}
}

//access functions
int length(List L)
{
	if(L==NULL)
	{
		printf("List Error: calling length() on a NULL List reference\n");
		exit(1);
	}
	return(L->length);
}

int index(List L)
{
	if(L==NULL)
	{
		printf("List Error: calling index() on a NULL List reference\n");
		exit(1);
	}

	return L->index;
}

void* front(List L)
{
	if(L==NULL)
	{
		printf("List Error: calling front() on a NULL List reference\n");
		exit(1);
	}
	return(L->front->value);
}

void* back(List L)
{
	if(L==NULL)
	{
		printf("List Error: calling back() on a NULL List reference\n");
		exit(1);
	}
	return(L->back->value);
}

void* get(List L)
{
	if(L==NULL)
	{
		printf("List Error: calling get() on a NULL List reference\n");
		exit(1);
	}

	return(L->cursor->value);
}

//manipulation functions

void clear(List L)
{
	if(L==NULL)
	{
		printf("List Error: calling clear() on a NULL List reference\n");
		exit(1);
	}

	//loop through delete to clear everything
	int l=L->length;
	for(int x=0; x<l; x++)
	{
		deleteFront(L);
	}
	L->length = 0;
	L->index = -1;
}

void moveFront(List L)
{
	if(L==NULL)
	{
		printf("List Error: calling moveFront() on a NULL List reference\n");
		exit(1);
	}

	//if length is > 0
	if(L->length>0)
	{
		L->cursor = L->front;
		L->index = 0;
	}
}

void moveBack(List L)
{
	if(L==NULL)
	{
		printf("List Error: calling moveBack() on a NULL List reference\n");
		exit(1);
	}

	if(L->length>0)
	{
		L->cursor=L->back;
		L->index = L->length-1;
	}
}

void movePrev(List L)
{
	if(L==NULL)
	{
		printf("List Error: calling movePrev() on a NULL List reference\n");
		exit(1);
	}

	//if cursor is not undefined
	if(L->index!=-1)
	{
		//if cursor is at front
		if(L->index==0)
		{
			L->cursor = NULL;
			L->index = -1;
		}
		else //if cursor isnt at front
		{
			L->cursor=L->cursor->prev;
			L->index--;
		}
	}
}

void moveNext(List L)
{
	if(L==NULL)
	{
		printf("List Error: calling moveNext() on a NULL List reference\n");
		exit(1);
	}

	//if cursor is defined
	if(L->index!=-1)
	{
		//if cursor is not at back
		if(L->index==L->length-1)
		{
			L->cursor = NULL;
			L->index = -1;
		}
		else
		{
			L->cursor=L->cursor->next;
			L->index++;
		}
	}
}

void prepend(List L, void* data)
{
	if(L==NULL)
	{
		printf("List Error: calling prepend() on a NULL List reference\n");
		exit(1);
	}

	if(L->index!=-1)
	{
		L->index++;
	}

	Node N = newNode(data);
	Node temp = L->front;
	//if empty List
	if(L->length==0)
	{
		L->front = N;
		L->back = N;
	}
	else
	{
		N->next = temp;
		temp->prev = N;
		L->front = N;
	}
	L->length++;
}

void append(List L, void* data)
{
	if(L==NULL)
	{
		printf("List Error: calling append() on a NULL List reference\n");
		exit(1);
	}

	Node N = newNode(data);
	Node temp = L->back;
	//if empty list
	if(L->length==0)
	{
		L->front = N;
		L->back = N;
	}
	else
	{
		N->prev =temp;
		temp->next = N;
		L->back = N;
	}
	L->length++;
}

void insertBefore(List L, void* data)
{
	if(L==NULL)
	{
		printf("List Error: calling insertBefore() on a NULL List reference\n");
		exit(1);
	}

	//if first element
	if(L->index==0)
	{
		prepend(L, data);
	}
	else
	{
		Node N = newNode(data);
		L->cursor->prev->next = N;
		N->prev = L->cursor->prev;
		N->next = L->cursor;
		L->cursor->prev = N;
		L->length++;
		L->index++;
	}
}

void insertAfter(List L, void* data)
{
	if(L==NULL)
	{
		printf("List Error: calling insertAfter() on a NULL List reference\n");
		exit(1);
	}

	//if back element
	if(L->cursor->next ==NULL)
	{
		append(L, data);
	}
	else
	{
		Node N = newNode(data);
		Node H = L->cursor->next;
		
		N->prev =L->cursor;
		N->next = H;
		H->prev = N;
		L->cursor->next = N;
		// N->prev = L->cursor;
		// N->next = L->cursor->next;
		// L->cursor->next->next->prev = N;
		// L->cursor->next = N;
		L->length++;
	}
}

void deleteFront(List L)
{
	if(L==NULL)
	{
		printf("List Error: calling deleteFront() on a NULL List reference\n");
		exit(1);
	}

	if(L->length==0)
	{
		printf("List Error: calling deleteFront() on an empty List reference\n");
		exit(1);
	}

	//if index exists
	if(L->index!=-1)
	{
		L->index--;
		if(L->index==-1)
			L->cursor=NULL;
	}

	Node N = L->front;
	//if only 1 element
	if(L->length==1)
	{
		L->front=NULL;
	}
	else
	{
		L->front->next->prev = NULL;
		L->front= L->front->next;
	}

	freeNode(&N);
	L->length--;
}

void deleteBack(List L)
{
	if(L==NULL)
	{
		printf("List Error: calling deleteBack() on a NULL List reference\n");
		exit(1);
	}

	if(L->length==0)
	{
		printf("List Error: calling deleteBack() on an empty List reference\n");
		exit(1);
	}

	if(L->index==L->length-1)
	{
		L->index=-1;
		L->cursor=NULL;
	}

	Node N = L->back;
	//if only 1 element
	// if(L->length==1)
	// {
	// 	L->back =NULL;
	// }
	// else
	//{
		L->back=L->back->prev;
		//L->back->next = NULL;
	//}

	freeNode(&N);
	L->length--;
}

void delete(List L)
{
	if(L==NULL)
	{
		printf("List Error: calling delete() on a NULL List reference\n");
		exit(1);
	}

	if(L->length==0)
	{
		printf("List Error: calling delete() on an empty List reference\n");
		exit(1);
	}

	//first element
	if(L->index==0)
	{
		deleteFront(L);
	}
	else if(L->index==L->length-1) //last element
	{
		deleteBack(L);
	}
	else //middle element
	{
		Node N = L->cursor;
		L->cursor->prev->next = L->cursor->next;
		L->cursor->next->prev = L->cursor->prev;
		freeNode(&N);
		L->cursor=NULL;
		L->length--;
	}
	L->index = -1;
}