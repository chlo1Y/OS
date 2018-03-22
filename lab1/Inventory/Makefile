CC = gcc

CFLAGS = -Wall -c -g -ansi

## A list of options to pass to the linker. 
LDFLAGS = -Wall -g -lm -ansi

## Name the executable program, list source files
PROG = inv
SRCS = inv.c 

## Build the program from the object files (-o option)
$(PROG): inv.o
	$(CC) inv.o -o $(PROG) $(LDFLAGS)

inv.o: inv.c
	$(CC) $(CFLAGS) inv.c

## Remove all the compilation and debugging files
clean: 
	rm -f core $(PROG) inv.o *~
