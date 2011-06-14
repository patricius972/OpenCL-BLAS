/*
 * ocltest_test.c
 *
 *  Created on: Jun 13, 2011
 *      Author: ludwig
 */

#include <stdlib.h>

#include <ocltest/ocltest.h>

#define GLOBAL_SIZE_1 8
#define GLOBAL_SIZE_2 8

/* int results[GLOBAL_SIZE_1][GLOBAL_SIZE_2]; */
unsigned int counter = 0;

void sampleKernel()
{
	++counter;
	printf("%ix KERNEL! \n", counter);
/*	results[get_global_id(0) * get_local_size(0) + get_local_id(0)][get_global_id(
			1) * get_local_size(1) + get_local_id(1)];*/
}

int main(int argc, char **argv)
{
	if (ocltest_isInitialized())
	{
		return 1;
	}
	ocltest_init();
	if (!ocltest_isInitialized())
	{
		return 1;
	}
	unsigned int numDimensions = 2;
	unsigned int globalSizes[] =
	{ 8, 8 };
	unsigned int localSizes[] =
	{ 4, 2 };
	ocltest_runKernel(sampleKernel, numDimensions, globalSizes, localSizes);
	ocltest_drop();
	if (ocltest_isInitialized())
	{
		return 1;
	}
	if (counter != 64)
	{
		return 1;
	}
	return 0;
}
