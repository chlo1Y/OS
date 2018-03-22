CC = gcc

CFLAGS = -Wall -c -g -ansi

## A list of options to pass to the linker. 
LDFLAGS = -Wall -g -ansi

## Name the executable program, list source files
PROG = queue
SRCS = queue.c 

## Build the program from the object files (-o option)
$(PROG): queue.o driver.c
	$(CC) queue.o driver.c -o $(PROG) $(LDFLAGS)

queue.o: queue.c
	$(CC) $(CFLAGS) queue.c

## Remove all the compilation and debugging files
clean: 
	rm -f core $(PROG) queue.o *~
	
