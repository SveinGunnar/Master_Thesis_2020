CC = gcc
CFLAGS = -O2

all: 2D_arrayTest.out

2D_arrayTest.out: ArrayCopyTest.c
	$(CC) $(CFLAGS) ArrayCopyTest.c -fopenmp -lpmemobj -lpmem -o 2D_arrayTest.out

#clean:
#	rm *.o
