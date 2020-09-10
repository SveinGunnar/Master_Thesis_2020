CC = gcc
CFLAGS = -O2

all: Analyse.out

Analyse.out: Analyse.c main.c
	$(CC) $(CFLAGS) Analyse.c main.c -fopenmp -lpmemobj -lpmem -o Analyse.out

#clean:
#	rm *.o
