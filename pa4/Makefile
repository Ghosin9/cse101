#------------------------------------------------------------------------------
#  Makefile for CMPS 101 Programming Assignment 4
#  Ly Phung
#  lynphung
#  CSE101
#  11/20/19
#  Makefile for FindPath that implements Graph.c and List.c
#------------------------------------------------------------------------------

CLIENT         = FindPath
ADT1           = Graph
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
	submit cse101-pt.f19 pa4 List.c List.h Graph.c Graph.h GraphTest.c FindPath.c Makefile README

check:
	ls  /afs/cats.ucsc.edu/class/cse101-pt.f19/pa4/lynphung

memcheck : $(CLIENT)
	$(MEMCHECK) $(CLIENT)
