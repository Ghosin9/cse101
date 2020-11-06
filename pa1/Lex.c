
/*
* Lex.c
* Ly Phung
* lynphung
* CSE101
* 10/6/19
* Lex file that organizes text files in alphabetical order
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 100

int main(int argc, char* argv[])
{
	//check command line for the correct number of arguments
	if (argc!= 3)
	{
		printf("Usage: Lex <input file> <output file>");
	}

	//opening file
	FILE *in, *out;
	in = fopen(argv[1], "r");
	if(in==NULL)
	{
		printf("Unable to open file %s for reading", argv[1]);
		exit(1);
	}

	//printf("fuck1\n");

	out = fopen(argv[2], "w");
	if(out == NULL)
	{
		printf("Unable to open file %s for writing", argv[2]);
		exit(1);
	}

	//printf("fuck2\n");

	char line[MAX_LEN];
	int count = 0;
	while(fscanf(in, " %s", line) != EOF)
	{
		count++;
	}
	rewind(in);

	//printf("fuck3\n");

	char* words[count];
	//printf("penis\n");
	int a;
	//printf("cheese\n");
	for(a=0; a < count; a++)
	{
		words[a] = malloc(sizeof(char)*MAX_LEN);
		fgets(words[a], MAX_LEN, in);
	}

	List list = newList();

	int i;
	prepend(list, 0);
	for(i=1;i<count; i++)
	{
		moveFront(list);
		while(index(list)>=0 && strcmp(words[i], words[get(list)])>0)
		{
			moveNext(list);
		}
		
		//printf("index:%d \n", index(list));
		if(index(list)==-1)
		{
			append(list, i);
		}
		else
		{
			insertBefore(list, i);
		}
		// printList(stdout, list);
		// printf("\n");
	}

	moveFront(list);
	for(int x =0; x<length(list); x++)
	{
		fprintf(out, "%s", words[get(list)]);
		moveNext(list);
	}

	clear(list);
	freeList(&list);

	for(int x=0; x<count; x++)
	{
		free(words[x]);
	}

	fclose(in);
	fclose(out);
}