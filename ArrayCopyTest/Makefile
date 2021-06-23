CC = gcc
CFLAGS = -O2

all: 2D_arrayTest.out LoadStoreTest.out

2D_arrayTest.out: ArrayCopyTest.c
	$(CC) $(CFLAGS) ArrayCopyTest.c -o 2D_arrayTest.out -fopenmp -lpapi
LoadStoreTest.out: LoadStoreTest.c
	$(CC) $(CFLAGS) LoadStoreTest.c -o LoadStoreTest.out -fopenmp -lpapi	

#clean:
#	rm *.o
