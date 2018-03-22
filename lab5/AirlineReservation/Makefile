CC = gcc

CFLAGS = -Wall -c -g -pthread

LDFLAGS = -Wall -g -pthread

airlinereservation: airlinereservation.o airplane.o
	$(CC) airlinereservation.o airplane.o -o airlinereservation $(LDFLAGS)

airlinereservation.o: airlinereservation.c airlinereservation.h
	$(CC) $(CFLAGS) airlinereservation.c -o airlinereservation.o

airplane.o: airplane.c airplane.h input.h
	$(CC) $(CFLAGS) airplane.c -o airplane.o
clean: 
	rm -f core airlinereservation airlinereservation.o *~
