CC = gcc

CFLAGS = -Wall -c -g -ansi

## A list of options to pass to the linker. 
LDFLAGS = -Wall -g -lm

## Name the executable program, list source files
PROG = sig

## Build the program from the object files (-o option)
$(PROG): signals.c  signals.h
	$(CC) signals.c  -o  $(PROG) $(LDFLAGS)


## Remove all the compilation and debugging files
clean: 
	rm -f core $(PROG) signals.o *~
	
