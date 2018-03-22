CC = gcc

CFLAGS = -Wall -g  -pthread

all: littleRedHen balloon

littleRedHen: littleRedHen.c
	$(CC) -o littleRedHen littleRedHen.c $(CFLAGS)

balloon: balloon.c 
	$(CC) -o balloon balloon.c $(CFLAGS)


clean:
	rm -rf balloon littleRedHen *.o *_out.txt