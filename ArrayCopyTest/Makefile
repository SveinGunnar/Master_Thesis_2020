CC = gcc
CFLAGS = -O2
<<<<<<< HEAD
INC?=-I/usr/include/
LIB?=-L/usr/lib/ -lpapi
=======
#INC?=-Iusr/include/
#LIB?=-L/usr/include/ -lpapi
>>>>>>> 501745ac9651ad68d6a40e62e69aa125a9e853e1

all: 2D_arrayTest.out LoadStoreTest.out

2D_arrayTest.out: ArrayCopyTest.c
	$(CC) $(CFLAGS) ArrayCopyTest.c -o 2D_arrayTest.out -fopenmp -lpapi
LoadStoreTest.out: LoadStoreTest.c
	$(CC) $(CFLAGS) LoadStoreTest.c -o LoadStoreTest.out -fopenmp -lpapi	

#clean:
#	rm *.o
