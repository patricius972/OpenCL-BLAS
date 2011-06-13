/*
 * kernel_test.h
 *
 *  Created on: Jun 13, 2011
 *      Author: ludwig
 */

#ifndef KERNEL_TEST_H_
#define KERNEL_TEST_H_

#include <stdio.h>
#include <stdlib.h>

#include "ocltest_constants.h"
#include "kernel_functions.h"


/**
 * This function runs a OpenCL kernel code for testing purpose. The kernel is
 * a simple function without parameters which is the correct function call
 * with all correct parameters. The kernel itself is called only with blank
 * afterwards. This is used to not to implemented a parser for OpenCL C
 * parsing.
 */
int ocltest_testKernel(void(*kernel)(), unsigned int numDimensions,
		unsigned int *globalSizes, unsigned int *localSizes);

/**
 * This function is the same like testKernel(), but needs to get all sizes in
 * all three dimensions. This function calls _runKernel() every work group.
 */
int _testKernel(void(*kernel)(), unsigned int numDimensions,
		unsigned int *globalSizes, unsigned int *localSizes,
		unsigned int *globalIds, unsigned int currentDimension);

int _runWorkGroup(void(*kernel)(), unsigned int numDimensions,
		unsigned int *globalSizes, unsigned int *localSizes,
		unsigned int *globalIds);

int _runWorkGroupThreads(void(*kernel)(), unsigned int numDimensions,
		unsigned int *globalSizes, unsigned int *localSizes,
		unsigned int *globalIds, unsigned int *localIds,
		unsigned int currentDimension);

int _runKernelThread(void(*kernel)(), unsigned int numDimensions,
		unsigned int *globalSizes, unsigned int *localSizes,
		unsigned int *globalIds, unsigned int *localIds);

typedef struct {
	unsigned int threadId;
	void (*kernel)();
	unsigned int *localIds;
} startParamsStruct;

void *start(void *startParams);

#endif /* KERNEL_TEST_H_ */
