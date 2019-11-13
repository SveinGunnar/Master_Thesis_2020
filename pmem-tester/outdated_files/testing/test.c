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

/* size of the pmemobj pool -- 1 GB */
#define POOL_SIZE ((size_t)(1 << 30))

/* name of our layout in the pool */
#define LAYOUT_NAME "example_layout"

int
main(int argc, char *argv[])
{
	//const char path[] = "/mnt/pmem1/sveingf/testing";
	const char path[] = "myobjpool.set";
	PMEMobjpool *pop;

	/* create the pmemobj pool or open it if it already exists */
	pop = pmemobj_create(path, LAYOUT_NAME, POOL_SIZE, 0666);

	if (pop == NULL)
	    pop = pmemobj_open(path, LAYOUT_NAME);

	if (pop == NULL) {
		perror(path);
		printf("error");
		exit(1);
	}

	/* ... */
	printf("ended");
	pmemobj_close(pop);
}
