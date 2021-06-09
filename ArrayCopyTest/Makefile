CC = gcc
CFLAGS = -O2
#INC?=-Iusr/include/
LIB?=-L/usr/include/ -lpapi

all: 2D_arrayTest.out

2D_arrayTest.out: ArrayCopyTest.c
	$(CC) $(CFLAGS) ArrayCopyTest.c -fopenmp -o 2D_arrayTest.out ${LIB}

#clean:
#	rm *.o
