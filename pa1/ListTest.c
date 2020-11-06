#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]) 
{
	List A = newList();
		append(A, 1);
        deleteBack(A);
        append(A, 2);
        append(A, 3);
        append(A, 5);
        moveFront(A);
        insertAfter(A, 12);
        deleteBack(A);
        //printf("%d", length(A));
        if (length(A) != 3)
        		printf("%d", length(A));
        return 0;
}
