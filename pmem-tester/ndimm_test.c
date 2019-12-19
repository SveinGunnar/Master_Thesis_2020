#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#ifndef _WIN32
#include <unistd.h>
#endif
#include <stdint.h>
#include <string.h>
#include <libpmemobj.h>

POBJ_LAYOUT_BEGIN(array);
POBJ_LAYOUT_TOID(array, double);
POBJ_LAYOUT_END(array);

//#define ARRAY_LENGTH 2013265920
//#define ARRAY_LENGTH 2147483648
#define ARRAY_LENGTH 2147000000

/* size of the pmemobj pool -- 1 GB */
#define POOL_SIZE ((size_t)(1 << 30))

/* name of our layout in the pool */
#define LAYOUT_NAME "my_layout"

int
main(int argc, char *argv[])
{
	const char path[] = "/mnt/pmem0-xfs/pool.obj";
	PMEMobjpool *pop;

	/* create the pmemobj pool or open it if it already exists */
	//pop = pmemobj_create(path, LAYOUT_NAME, POOL_SIZE, 0666);

	//if (pop == NULL)
	pop = pmemobj_open(path, LAYOUT_NAME);

	if (pop == NULL) {
		perror(path);
		exit(1);
	}

	int i;

	TOID(double) nvm_array1;

/*	TOID(double) nvm_array2;
        TOID(double) nvm_array3;
        TOID(double) nvm_array4;
	TOID(double) nvm_array5;
        TOID(double) nvm_array6;
        TOID(double) nvm_array7;
	TOID(double) nvm_array8;
        TOID(double) nvm_array9;
//      TOID(double) nvm_array10;
//      TOID(double) nvm_array11;
//      TOID(double) nvm_array12;
*/
        POBJ_ALLOC(pop, &nvm_array1, double, sizeof(double) * ARRAY_LENGTH, NULL, NULL);
/*      POBJ_ALLOC(pop, &nvm_array2, double, sizeof(double) * ARRAY_LENGTH, NULL, NULL);
        POBJ_ALLOC(pop, &nvm_array3, double, sizeof(double) * ARRAY_LENGTH, NULL, NULL);
        POBJ_ALLOC(pop, &nvm_array4, double, sizeof(double) * ARRAY_LENGTH, NULL, NULL);
	POBJ_ALLOC(pop, &nvm_array5, double, sizeof(double) * ARRAY_LENGTH, NULL, NULL);
        POBJ_ALLOC(pop, &nvm_array6, double, sizeof(double) * ARRAY_LENGTH, NULL, NULL);
        POBJ_ALLOC(pop, &nvm_array7, double, sizeof(double) * ARRAY_LENGTH, NULL, NULL);
	POBJ_ALLOC(pop, &nvm_array8, double, sizeof(double) * ARRAY_LENGTH, NULL, NULL);
        POBJ_ALLOC(pop, &nvm_array9, double, sizeof(double) * ARRAY_LENGTH, NULL, NULL);
//      POBJ_ALLOC(pop, &nvm_array10, double, sizeof(double) * ARRAY_LENGTH, NULL, NULL);
//      POBJ_ALLOC(pop, &nvm_array11, double, sizeof(double) * ARRAY_LENGTH, NULL, NULL);
//      POBJ_ALLOC(pop, &nvm_array12, double, sizeof(double) * ARRAY_LENGTH, NULL, NULL);
*/
	srand((unsigned int)time(NULL));
        for(i=0;i<ARRAY_LENGTH;i++){
                D_RW(nvm_array1)[i] = ((double)rand())/((double)(RAND_MAX));
/*              D_RW(nvm_array2)[i] = ((double)rand())/((double)(RAND_MAX));
		D_RW(nvm_array3)[i] = ((double)rand())/((double)(RAND_MAX));
                D_RW(nvm_array4)[i] = ((double)rand())/((double)(RAND_MAX));
		D_RW(nvm_array5)[i] = ((double)rand())/((double)(RAND_MAX));
                D_RW(nvm_array6)[i] = ((double)rand())/((double)(RAND_MAX));
		D_RW(nvm_array7)[i] = ((double)rand())/((double)(RAND_MAX));
		D_RW(nvm_array8)[i] = ((double)rand())/((double)(RAND_MAX));
                D_RW(nvm_array9)[i] = ((double)rand())/((double)(RAND_MAX));
//              D_RW(nvm_array10)[i] = ((double)rand())/((double)(RAND_MAX));
//              D_RW(nvm_array11)[i] = ((double)rand())/((double)(RAND_MAX));
//              D_RW(nvm_array12)[i] = ((double)rand())/((double)(RAND_MAX));
*/
	}

	printf("%f\n", D_RO(nvm_array1)[52356]);
/*
	printf("%f\n", D_RO(nvm_array2)[52356]);
	printf("%f\n", D_RO(nvm_array3)[52356]);
	printf("%f\n", D_RO(nvm_array4)[52356]);
	printf("%f\n", D_RO(nvm_array5)[52356]);
	printf("%f\n", D_RO(nvm_array6)[52356]);
	printf("%f\n", D_RO(nvm_array7)[52356]);
	printf("%f\n", D_RO(nvm_array8)[52356]);
        printf("%f\n", D_RO(nvm_array9)[52356]);
//      printf("%f\n", D_RO(nvm_array10)[52356]);
//      printf("%f\n", D_RO(nvm_array11)[52356]);
//      printf("%f\n", D_RO(nvm_array12)[52356]);
*/
	
	POBJ_FREE(&nvm_array1);
/*
	POBJ_FREE(&nvm_array2);
        POBJ_FREE(&nvm_array3);
        POBJ_FREE(&nvm_array4);
	POBJ_FREE(&nvm_array5);
        POBJ_FREE(&nvm_array6);
        POBJ_FREE(&nvm_array7);
	POBJ_FREE(&nvm_array8);
        POBJ_FREE(&nvm_array9);
//      POBJ_FREE(&nvm_array10);
//      POBJ_FREE(&nvm_array11);
//      POBJ_FREE(&nvm_array12);
*/

	pmemobj_close(pop);
	return 0;
}
