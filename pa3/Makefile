#------------------------------------------------------------------------------
#  Makefile for CMPS 101 Programming Assignment 3
#  Ly Phung
#  lynphung
#  CSE101
#  11/6/19
#
#  make                     makes ArithmeticClient
#  make clean               removes all binaries
#  make memcheck            runs Arithmetic Client under valgrind
#------------------------------------------------------------------------------

CLIENT         = Arithmetic
ADT1           = BigInteger
ADT2           = List
SOURCE         = $(CLIENT).c
OBJECT         = $(CLIENT).o
ADT1_SOURCE    = $(ADT1).c
ADT1_OBJECT    = $(ADT1).o
ADT1_HEADER    = $(ADT1).h
ADT2_SOURCE    = $(ADT2).c
ADT2_OBJECT    = $(ADT2).o
ADT2_HEADER    = $(ADT2).h
COMPILE        = gcc -c -std=c99 -Wall
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(CLIENT) : $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(CLIENT) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

$(OBJECT) : $(SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(SOURCE)

$(ADT1_OBJECT) : $(ADT1_SOURCE) $(ADT1_HEADER)
	$(COMPILE) $(ADT1_SOURCE)

$(ADT2_OBJECT) : $(ADT2_SOURCE) $(ADT2_HEADER)
	$(COMPILE) $(ADT2_SOURCE)

clean :
	$(REMOVE) $(CLIENT) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

submit: 
	submit cse101-pt.f19 pa3 Arithmetic.c BigInteger.c BigInteger.h BigIntegerTest.c List.c List.h ListTest.c Makefile README

check:
	ls  /afs/cats.ucsc.edu/class/cse101-pt.f19/pa3/lynphung

memcheck : $(CLIENT)
	$(MEMCHECK) $(CLIENT)
