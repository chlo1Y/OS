CC = gcc

CFLAGS = -Wall -g -ansi -pthread

all: producerConsumer abcd threeAndTwo

producerConsumer: producerConsumer.c
	$(CC) -o producerConsumer producerConsumer.c $(CFLAGS)

abcd: abcd.c 
	$(CC) -o abcd abcd.c $(CFLAGS)

threeAndTwo: threeAndTwo.c 
	$(CC) -o threeAndTwo threeAndTwo.c $(CFLAGS)

clean:
	rm -rf producerConsumer abcd threeAndTwo *.o *_out.txt