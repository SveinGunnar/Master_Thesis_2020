CC = gcc
CFLAGS = -O2

all: Stream_c_s.out Stream_c_m.out Stream_pmemobj_s.out Stream_pmemobj_m.out Stream_sum.out Stream_sum_pmemobj.out
#Stream_nvdimm.out Stream_nvdimm2.out Stream_c_malloc.out

Stream_c_s.out: stream.c
	$(CC) $(CFLAGS) stream.c -o Stream_c_s.out

Stream_c_m.out: stream.c
	$(CC) $(CFLAGS) stream.c -o Stream_c_m.out -fopenmp

Stream_pmemobj_s.out: stream_pmemobj.c
	$(CC) $(CFLAGS) stream_pmemobj.c -o Stream_pmemobj_s.out -lpmemobj -lpmem

Stream_pmemobj_m.out: stream_pmemobj.c
	$(CC) $(CFLAGS) stream_pmemobj.c -o Stream_pmemobj_m.out -lpmemobj -lpmem -fopenmp

Stream_sum.out: stream_sum.c
	$(CC) $(CFLAGS) stream_sum.c -o Stream_sum.out -fopenmp

Stream_sum_pmemobj.out: stream_sum_pmemobj.c
	$(CC) $(CFLAGS) stream_sum_pmemobj.c -o Stream_sum_pmemobj.out -lpmemobj -lpmem -fopenmp

#Stream_c_malloc.out: stream_malloc.c
#	$(CC) $(CFLAGS) stream_malloc.c -o Stream_c_malloc.out

#Stream_nvdimm.out: stream_nvdimm.c
#	$(CC) $(CFLAGS) stream_nvdimm.c -o Stream_nvdimm.out -lvmmalloc

#Stream_nvdimm2.out: stream_nvdimm2.c
#	$(CC) $(CFLAGS) stream_nvdimm2.c -o Stream_nvdimm2.out -lpmemobj -lpmem  

clean:
	rm stream_c.exe *.o

# an example of a more complex build line for the Intel icc compiler
stream.icc: stream.c
	icc -O3 -xCORE-AVX2 -ffreestanding -qopenmp -DSTREAM_ARRAY_SIZE=80000000 -DNTIMES=20 stream.c -o stream.omp.AVX2.80M.20x.icc
