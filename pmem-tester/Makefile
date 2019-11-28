CC = gcc
CFLAGS = -O2

all: Pmemobj_copy.out Pmemobj_add.out Pmemobj_scale.out Pmemobj_triad.out Pmemobj_openMP.out Pmemobj_openMP_2.out Pmemobj_multitest.out Pmemobj_average.out Pmemobj_latency.out Pmemobj_rw.out Pmemobj_double_nvdimm.out

Pmemobj_copy.out: pmemobj_copy.c
	$(CC) $(CFLAGS) pmemobj_copy.c -o Pmemobj_copy.out -lpmemobj -lpmem
Pmemobj_scale.out: pmemobj_scale.c
	$(CC) $(CFLAGS) pmemobj_scale.c -o Pmemobj_scale.out -lpmemobj -lpmem
Pmemobj_add.out: pmemobj_add.c
	$(CC) $(CFLAGS) pmemobj_add.c -o Pmemobj_add.out -lpmemobj -lpmem
Pmemobj_triad.out: pmemobj_triad.c
	$(CC) $(CFLAGS) pmemobj_triad.c -o Pmemobj_triad.out -lpmemobj -lpmem

Pmemobj_multitest.out: pmemobj_multitest.c
	$(CC) $(CFLAGS) pmemobj_multitest.c -o Pmemobj_multitest.out -lpmemobj -lpmem
Pmemobj_openMP.out: pmemobj_openMP.c
	$(CC) $(CFLAGS) pmemobj_openMP.c -o Pmemobj_openMP.out -lpmemobj -lpmem -fopenmp
Pmemobj_openMP_2.out: pmemobj_openMP_2.c
	$(CC) $(CFLAGS) pmemobj_openMP_2.c -o Pmemobj_openMP_2.out -lpmemobj -lpmem -fopenmp

Pmemobj_rw.out: pmemobj_rw.c
	$(CC) $(CFLAGS) pmemobj_rw.c -o Pmemobj_rw.out -lpmemobj -lpmem -fopenmp
Pmemobj_double_nvdimm.out: pmemobj_double_nvdimm.c
	$(CC) $(CFLAGS) pmemobj_double_nvdimm.c -o Pmemobj_double_nvdimm.out -lpmemobj -lpmem -fopenmp

Pmemobj_average.out: pmemobj_average.c
	$(CC) $(CFLAGS) pmemobj_average.c -o Pmemobj_average.out -lpmemobj -lpmem
Pmemobj_latency.out: pmemobj_latency.c
	$(CC) $(CFLAGS) pmemobj_latency.c -o Pmemobj_latency.out -lpmemobj -lpmem -fopenmp

#all: main_memkind.out main_memkind_openMP.out
#main_memkind.out: main_memkind.c
#	$(CC) $(CFLAGS) main_memkind.c -o main_memkind.out -lmemkind
#main_memkind_openMP.out: main_memkind_openMP.c
#	$(CC) $(CFLAGS) main_memkind_openMP.c -o main_memkind_openMP.out -lmemkind -fopenmp

clean:
	rm main_memkind.out main_memkind_openMP.out *.o
