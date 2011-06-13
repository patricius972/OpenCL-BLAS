/*
 * kernel_functions.h
 *
 *  Created on: Jun 13, 2011
 *      Author: ludwig
 */

/**
 * These are functions which are defined in OpenCL-C which need to be
 * implemented as well within the testing framework. The testing is done on
 * work group basis as it would run on a single SIMD processor. The work is
 * performed with POSIX threads.
 */

#ifndef KERNEL_FUNCTIONS_H_
#define KERNEL_FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "ocltest_constants.h"

unsigned int _numDimensions;
unsigned int *_globalSizes;
unsigned int *_localSizes;
unsigned int _workGroupThreadNum;
pthread_t *_kernelThreads;

int initKernelTest(unsigned int numDimensions, unsigned int *globalSizes,
		unsigned int *localSizes);
int dropKernelTest();

unsigned int *_globalIds;
pthread_key_t _localIds;

int initWorkGroup(unsigned int numDimensions, unsigned int *globalIds);
int dropWorkGroup();

int get_global_id(unsigned int dim);
int get_local_id(unsigned int dim);
int get_global_size(unsigned int dim);
int get_local_size(unsigned int dim);

#define CLK_LOCAL_MEM_FENCE 0

pthread_barrier_t local_mem_fence;

void barrier(unsigned int barrier_type);

#endif /* KERNEL_FUNCTIONS_H_ */
