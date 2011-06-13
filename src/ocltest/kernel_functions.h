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

#include <pthread.h>

int get_global_id(unsigned int dim);

int get_local_id(unsigned int dim);

#define CLK_LOCAL_MEM_FENCE 0

pthread_barrier_t local_mem_fence;

void barrier(unsigned int barrier_type);

#endif /* KERNEL_FUNCTIONS_H_ */
