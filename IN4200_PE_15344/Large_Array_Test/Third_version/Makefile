CC = gcc
CFLAGS = -O2

all: LargeArrayTest.out

LargeArrayTest.out: main.c functions.c
	$(CC) $(CFLAGS) main.c functions.c -fopenmp -lpmemobj -lpmem -o LargeArrayTest.out

#clean:
#	rm *.o
