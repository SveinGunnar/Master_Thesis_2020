CC = gcc
CFLAGS = -O2

all: Page_rank.out

Page_rank.out: PE_main_15344.c PE_functions_15344.c
	$(CC) $(CFLAGS) PE_main_15344.c PE_functions_15344.c -fopenmp -lpmemobj -lpmem -o Page_rank.out

#clean:
#	rm *.o
