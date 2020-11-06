#------------------------------------------------------------------------------
# Makefile
# Ly Phung
# lynphung
# CSE101
# 10/6/19
# Makefile for Maxtrix.c and Sparse.c
#------------------------------------------------------------------------------

Lex : Lex.o List.o
	gcc -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -c -std=c99 -Wall Lex.c

ListClient: ListClient.o List.o
	gcc -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -c -std=c99 -Wall ListClient.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

ListTest: ListTest.o List.o
	gcc -o ListTest ListTest.o List.o

ListTest.o : ListTest.c List.h
	gcc -c -std=c99 -Wall ListTest.c

clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o

submit: 
	submit cse101-pt.f19 pa1 List.h List.c ListClient.c Lex.c Makefile README

check:
	ls  /afs/cats.ucsc.edu/class/cse101-pt.f19/pa1/lynphung

valgrind:
	valgrind --leak-check=full ListClient
