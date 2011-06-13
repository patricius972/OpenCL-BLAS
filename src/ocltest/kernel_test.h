/*
 * kernel_test.h
 *
 *  Created on: Jun 13, 2011
 *      Author: ludwig
 */

#ifndef KERNEL_TEST_H_
#define KERNEL_TEST_H_

#define SUCCESS 0
#define INVALID_PROBLEM_DIMENSION 1

/**
 * This function runs a OpenCL kernel code for testing purpose. The kernel is
 * a simple function without parameters which is the correct function call
 * with all correct parameters. The kernel itself is called only with blank
 * afterwards. This is used to not to implemented a parser for OpenCL C
 * parsing.
 */
int testKernel(void *kernel(), size_t numSizes, size_t *globalSize,
		size_t *localSize);

/**
 * This function is the same like testKernel(), but needs to get all sizes in
 * all three dimensions. This function calls _runKernel() every work group.
 */
int _testKernel(void *kernel(), size_t globalSize1, size_t globalSize2,
		size_t globalSize3, size_t localSize1, size_t localSize2,
		size_t localSize3);

int _runKernel(void *kernel(), int globalPos1, int globalPos2, int globalPos3,
		size_t globalSize1, size_t globalSize2, size_t globalSize3,
		size_t localSize1, size_t localSize2, size_t localSize3);

int _startKernelThread(void *kernel(), int globalId, int localId) {

}

#endif /* KERNEL_TEST_H_ */
