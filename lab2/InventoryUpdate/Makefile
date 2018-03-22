CC = gcc

CFLAGS = -Wall -c -g -ansi

## A list of options to pass to the linker. 
LDFLAGS = -Wall -g -lm -ansi

## Name the executable program, list source files
PROG = inventoryUpdate
SRCS = inventoryUpdate.c 

## Build the program from the object files (-o option)
$(PROG): inventoryUpdate.o
	$(CC) inventoryUpdate.o -o $(PROG) $(LDFLAGS)

power.o: inventoryUpdate.c
	$(CC) $(CFLAGS) inventoryUpdate.c

## Remove all the compilation and debugging files
clean: 
	rm -f core $(PROG) inventoryUpdate.o *~
