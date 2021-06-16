CC = gcc
CFLAGS = -O2

all: Page_rank.out SimpleLockUnlockTest.out

Page_rank.out: PE_main_15344.c PE_functions_15344.c
	$(CC) $(CFLAGS) PE_main_15344.c PE_functions_15344.c -fopenmp -lpmemobj -lpmem -lpapi -o Page_rank.out
SimpleLockUnlockTest.out: SimpleLockUnlockTest.c
	$(CC) $(CFLAGS) SimpleLockUnlockTest.c -fopenmp -o SimpleLockUnlockTest.out

#clean:
#	rm *.o
