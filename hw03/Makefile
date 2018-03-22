CC = gcc

CFLAGS = -Wall -c -g -ansi

## A list of options to pass to the linker. 
LDFLAGS = -Wall -g -lm -ansi -pthread

## Name the executable program, list source files
PROG = factoring
SRCS = factoring.c 

## Build the program from the object files (-o option)
$(PROG): factoring.o
	$(CC) factoring.o -o $(PROG) $(LDFLAGS)

factoring.o: factoring.c
	$(CC) $(CFLAGS) factoring.c

## Remove all the compilation and debugging files
clean: 
	rm -f core $(PROG) factoring.o *~
	
