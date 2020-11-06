/*
* BigInteger.c
* Ly Phung
* lynphung
* CSE101
* 11/6/19
* ImpNementation file for BigInteger ADT
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"List.h"
#include"BigInteger.h"

//big int
typedef struct BigIntegerObj
{
	int sign;
	List mag;
} BigIntegerObj;

BigInteger newBigInteger()
{
	BigInteger B = malloc(sizeof(BigIntegerObj));
	assert(B!=NULL);
	B->mag = newList();
	B->sign = 0;
	return(B);
}

void freeBigInteger(BigInteger* pN)
{
	if(pN!=NULL && *pN!=NULL)
	{
		makeZero(*pN);
		free(&((*pN)->mag));
		free(*pN);
		*pN = NULL;
	}
}

int sign(BigInteger N)
{
	return N->sign;
}

int compare(BigInteger A, BigInteger B)
{
	//cases if signs are different
	if(A->sign<B->sign)
	{
		return -1;
	}
	else if(A->sign>B->sign)
	{
		return 1;
	}

	//check for 0
	if(A->sign==0)
		return 0;

	//now signs must be equal and != 0
	//checking lengths
	if(length(A->mag)>length(B->mag))
	{
		//if positive
		if(A->sign==1)
			return 1;
		//if negative
		if(A->sign==-1)
			return -1;
	}
	else if (length(A->mag)<length(B->mag))
	{
		//if positive
		if(A->sign==1)
			return -1;
		//if negative
		if(A->sign==-1)
			return 1;
	}
	else //lengths are equal
	{
		for(int x=0; x < length(A->mag); x++)
		{
			moveFront(A->mag);
			moveFront(B->mag);

			if(get(A->mag)>get(B->mag))
			{
				if(A->sign==1)
					return 1;
				if(A->sign==-1)
					return -1;
			}

			if(get(A->mag)<get(B->mag))
			{
				if(A->sign==1)
					return -1;
				if(A->sign==-1)
					return 1;
			}

			moveNext(A->mag);
			moveNext(B->mag);
		}
	}

	return 0;
}

int equals(BigInteger A, BigInteger B)
{
	if(A==B)
		return 1;

	if(compare(A,B)==0)
		return 1;

	return 0;
}

void makeZero(BigInteger N)
{
	N->sign=0;
	clear(N->mag);
}

void negate(BigInteger N)
{
	N->sign*=-1;
}

BigInteger stringToBigInteger(char* s)
{
	BigInteger B = newBigInteger();

	//determine how many objects will be in list
	int finish = 0;
	int add = 0;
	for(int x=strlen(s)-1; x>=0; x--)
	{
		if(s[x]=='-')
		{
			B->sign=-1;
		}
		else if (s[x]=='+')
		{
			B->sign=1;
		}
		else
		{
			int temp = s[x] - '0';
			//change temp to right digit place
			for(int y=0; y<add; y++)
				temp*=10;

			finish+=temp;
			add++;
			//printf("adding: %d\n", finish);

			//reached digits = power
			if(add==POWER)
			{
				// printf("adding: %d\n", finish);
				if(finish!=0)
					B->sign=1;
				prepend(B->mag, finish);
				add = 0;
				finish = 0;
				// printList(stdout, B->mag);
			}
		}

		//if reached left side of bigInt and not enough digits=POWER
		if(x==0 && finish!=0 && add!=0)
		{
			prepend(B->mag, finish);
		}
	}

	//make zero if 
	int zero = 1;
	moveFront(B->mag);
	for(int x=0; x<length(B->mag); x++)
	{
		if(get(B->mag)!=0)
			zero = 0;
		moveNext(B->mag);
	}

	if(zero==1)
	{
		makeZero(B);
	}

	return B;
}

BigInteger copy(BigInteger N)
{
	BigInteger B = newBigInteger();

	// printf("N sign: %d", N->sign);
	// printf("\n");
	B->sign = N->sign;

	moveFront(N->mag);
	// printf("length: %d\n", length(N->mag));
	for(int x=0; x<length(N->mag); x++)
	{
		// printf("appending: %ld", get(N->mag));
		append(B->mag, get(N->mag));
		moveNext(N->mag);
	}

	return B;
}

void normalize(BigInteger N)
{
	// printf("inside normalize\n");
	List L=N->mag;
	int len = length(L);
	moveBack(L);
	int carry=0;

	for(int x=0; x<len; x++)
	{
		// printf("inside normalize loop\n");
		long num = get(L);
		set(L, num+carry);
		carry = 0;

		// printf("on element: %ld\n", get(L));

		if(num<0)
		{
			//if first in list
			if(x==length(L)-1)
			{
				set(L, num*(-1));
				N->sign=-1;
			}
			else
			{
				carry = (-1)*(num/BASE)-1;
				num -= BASE*carry;
				set(L, num);
			}
		}
		else if(num>=BASE)
		{
			carry = num/BASE;
			num -= BASE*carry;
			set(L, num);
		}

		if(x==length(L)-1 && carry !=0)
		{
			if(carry<0)
			{
				prepend(L, (-1)* carry);
				N->sign =-1;
			}
			else //carry >0
			{
				// printf("carry: %d", carry);
				// printf("\n");
				prepend(L, carry);
				// printList(stdout, L);
				// printf("\n");
				N->sign =1;
			}
		}

		movePrev(L);
	}

	// printList(stdout, L);
	// printf("\n");

	// printf("changing to 0\n");
	//change to zero
	int zero = 1;
	moveFront(N->mag);
	while(index(N->mag)!=-1)
	{
		// printf("%d\n", index(N->mag));
		if(get(N->mag)!=0)
			zero = 0;
		moveNext(N->mag);
	}

	if(zero==1)
	{
		// printf("made 0\n");
		makeZero(N);
	}

	// printf("finished normalize\n");
}

void add(BigInteger S, BigInteger A, BigInteger B)
{
	if(S==A && S==B)
	{
		moveBack(A->mag);
		for(int x=0; x<length(A->mag); x++)
		{
			set(S->mag, 2*get(A->mag)*A->sign);
			movePrev(A->mag);
		}
	}
	else if(S==A)
	{
		moveBack(A->mag);
		moveBack(B->mag);

		while(index(A->mag)!=-1 || index(B->mag)!=-1)
		{
			if(index(A->mag)==-1)
			{
				prepend(S->mag, get(B->mag)*B->sign);
				movePrev(B->mag);
			}
			else if(index(B->mag)==-1)
			{
				set(S->mag, get(A->mag)*A->sign);
				movePrev(A->mag);
			}
			else
			{
				set(S->mag, get(A->mag)*A->sign + get(B->mag)*B->sign);
				movePrev(A->mag);
				movePrev(B->mag);
			}
		}
	}
	else if(S==B)
	{
		moveBack(A->mag);
		moveBack(B->mag);

		while(index(A->mag)!=-1 || index(B->mag)!=-1)
		{
			if(index(A->mag)==-1)
			{
				set(S->mag, get(B->mag)*B->sign);
				movePrev(B->mag);
			}
			else if(index(B->mag)==-1)
			{
				prepend(S->mag, get(A->mag)*A->sign);
				movePrev(A->mag);
			}
			else
			{
				set(S->mag, get(A->mag)*A->sign + get(B->mag)*B->sign);
				movePrev(A->mag);
				movePrev(B->mag);
			}
		}
	}
	else
	{
		// printf("base case\n");
		makeZero(S);
		moveBack(A->mag);
		moveBack(B->mag);
		long temp = 0;

		while(index(A->mag)!=-1 || index(B->mag)!=-1)
		{
			// printf("inside loop\n");
			if(index(A->mag)==-1)
			{
				// printf("case 1\n");
				temp = get(B->mag)*B->sign;
				movePrev(B->mag);
			}
			else if(index(B->mag)==-1)
			{
				// printf("case 2\n");
				temp = get(A->mag)*A->sign;
				movePrev(A->mag);
			}
			else
			{
				// printf("case 3\n");
				temp = get(A->mag)*A->sign + get(B->mag)*B->sign;
				movePrev(A->mag);
				movePrev(B->mag);
			}

			// printf("added: %ld\n", temp);
			prepend(S->mag, temp);
		}
	}

	// printBigInteger(stdout, S);
	// printf("\n");
	// printf("Sign of S: %d", S->sign);
	// printf("\n");

	normalize(S);

	//changing sign
	int negatedA = 0;
	int negatedB = 0;
	int signal = 0;

	if(A->sign!=1)
	{
		// printf("negated A\n");
		negate(A);
		negatedA = 1;
	}

	if(B->sign!=1)
	{
		negate(B);
		negatedB = 1; 
	}

	if(compare(A, B)==1)
	{
		// printf("compare 1\n");
		if(negatedA==1)
		{
			// printf("unnegated A\n");
			negate(A);
		}
		if(negatedB==1)
			negate(B);

		//printf("changed to A->sign\n");
		signal = A->sign;
	}
	else if(compare(A, B)==-1)
	{
		// printf("compare 2\n");
		if(negatedA==1)
		{
			// printf("unnegated A\n");
			negate(A);
		}
		if(negatedB==1)
			negate(B);

		//printf("changed to B->sign\n");
		signal = B->sign;
	}
	else
	{
		if(negatedA==1)
		{
			// printf("unnegated A\n");
			negate(A);
		}
		if(negatedB==1)
			negate(B);
		signal = 0;
	}

	S->sign = signal;
}

BigInteger sum(BigInteger A, BigInteger B)
{
	BigInteger C = newBigInteger();

	add(C, A, B);

	return C;
}

void subtract(BigInteger D, BigInteger A, BigInteger B)
{
	if(D==A && D==B)
	{
		makeZero(D);
	}
	else
	{
		negate(B);
		add(D, A, B);
		negate(B);
	}
}

BigInteger diff(BigInteger A, BigInteger B)
{
	BigInteger C = newBigInteger();

	subtract(C, A, B);

	return C;
}

void multiply(BigInteger P, BigInteger A, BigInteger B)
{
	// printf("inside multiple\n");
	if(A->sign==0 || B->sign==0)
	{
		makeZero(P);
		return;
	}

	if(P==A && P==B)
	{
		// printf("case 1\n");
		int len = length(A->mag);
		moveBack(A->mag);
		for(int x=0; x<len; x++)
		{
			set(P->mag, get(A->mag)*get(A->mag));
			movePrev(A->mag);
		}
	}
	else if(P==A)
	{
		// printf("case 2\n");
		moveBack(A->mag);
		moveBack(B->mag);

		for(int x=0; x<length(A->mag); x++)
		{
			for(int y=0; y<length(B->mag); y++)
			{
				set(P->mag, get(A->mag)*get(B->mag));
				movePrev(B->mag);
			}
			movePrev(A->mag);
		}
	}
	else if(P==B)
	{
		// printf("case 3\n");
		moveBack(A->mag);
		moveBack(B->mag);

		for(int x=0; x<length(A->mag); x++)
		{
			for(int y=0; y<length(B->mag); y++)
			{
				set(P->mag, get(A->mag)*get(B->mag));
				movePrev(B->mag);
			}
			movePrev(A->mag);
		}
	}
	else
	{
		//printf("case 4\n");
		makeZero(P);
		moveBack(A->mag);

		if(A==B)
		{
			moveBack(A->mag);
			for(int x=0; x<length(A->mag); x++)
			{
				append(P->mag, get(A->mag)*get(A->mag));
				movePrev(A->mag);
			}
		}
		else
		{
			for(int x=0; x<length(A->mag); x++)
			{
				moveBack(B->mag);
				// printf("inside loop 1\n");
				for(int y=0; y<length(B->mag); y++)
				{
					// printf("adding: %ld\n", get(A->mag)*get(B->mag));
					prepend(P->mag, get(A->mag)*get(B->mag));
					movePrev(B->mag);
				}
				movePrev(A->mag);

				// printList(stdout, P->mag);
				// printf("\n");
			}
		}
		// printf("before loops\n");
	}

	// printf("A sign: %d\n", A->sign);
	// printf("B sign: %d\n", B->sign);
	P->sign = A->sign*B->sign;

	// printf("P sign: %d\n", P->sign);
	// printf("finished multiple\n");
}

BigInteger prod(BigInteger A, BigInteger B)
{
	BigInteger C = newBigInteger();

	multiply(C, A, B);

	return C;
}

void printBigInteger(FILE* out, BigInteger N)
{
	moveFront(N->mag);

	for(int x=0; x<length(N->mag); x++)
	{
		//calculate number of leading zeros, if needed at all
		int temp = get(N->mag);
		int zeros = 0;
		while(temp >0)
		{
			temp= temp/10;
			zeros++;
		}
		zeros = POWER-zeros;

		if(get(N->mag)==0)
			zeros--;

		if(x==length(N->mag))
			fprintf(out, "%ld", get(N->mag));
		else
		{
			for(int i=0; i < zeros; i++)
			{
				fprintf(out, "%d", 0);
			}
			fprintf(out, "%ld ", get(N->mag));
		}
		moveNext(N->mag);
	}
}