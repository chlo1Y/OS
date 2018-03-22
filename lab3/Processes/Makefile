CC = gcc

CFLAGS = -Wall -g -ansi

all: myCopy processes

myCopy: myCopy.c
	$(CC) -o myCopy myCopy.c $(CFLAGS)

processes: processes.c processes.h
	$(CC) -o processes processes.c $(CFLAGS)

clean:
	rm -rf myCopy processes *.o *_out.txt
