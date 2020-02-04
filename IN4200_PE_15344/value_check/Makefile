CC = gcc
CFLAGS = -O2

all: Page_rank.out

Page_rank.out: main.c functions.c
	$(CC) $(CFLAGS) main.c functions.c -fopenmp -lpmemobj -lpmem -o Page_rank.out

#clean:
#	rm *.o
