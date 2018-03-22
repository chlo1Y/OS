CC = gcc

CFLAGS = -Wall -c -g -ansi

## A list of options to pass to the linker. 
LDFLAGS = -Wall -g -lm -ansi -pthread

## Name the executable program, list source files
PROG = threads

## Build the program from the object files (-o option)
$(PROG): threads.c  threads.h
	$(CC) threads.c  -o  $(PROG) $(LDFLAGS)


## Remove all the compilation and debugging files
clean: 
	rm -f core $(PROG) threads.o *~
	
