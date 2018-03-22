CC = gcc

CFLAGS = -Wall -c -g -ansi

## A list of options to pass to the linker. 
LDFLAGS = -Wall -g -lm -ansi

## Name the executable program, list source files
PROG = pigLatin
SRCS = pigLatin.c 

## Build the program from the object files (-o option)
$(PROG): pigLatin.o
	$(CC) pigLatin.o -o $(PROG) $(LDFLAGS)

pigLatin.o: pigLatin.c
	$(CC) $(CFLAGS) pigLatin.c

## Remove all the compilation and debugging files
clean: 
	rm -f core $(PROG) pigLatin.o *~
	
