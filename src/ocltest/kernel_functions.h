/*
 * kernel_functions.h
 *
 *  Created on: Jun 13, 2011
 *      Author: ludwig
 */

/*
   Copyright 2011 PureSol Technologies

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
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

OpenCLTestStatus initKernelTest(unsigned int numDimensions,
		unsigned int *globalSizes, unsigned int *localSizes);
OpenCLTestStatus dropKernelTest();

unsigned int *_globalIds;
pthread_key_t _localIds;

OpenCLTestStatus initWorkGroup(unsigned int numDimensions,
		unsigned int *globalIds);
OpenCLTestStatus dropWorkGroup();

int get_global_id(unsigned int dim);
int get_local_id(unsigned int dim);
int get_global_size(unsigned int dim);
int get_local_size(unsigned int dim);

#define CLK_LOCAL_MEM_FENCE 0

pthread_barrier_t local_mem_fence;

void barrier(unsigned int barrier_type);

#endif /* KERNEL_FUNCTIONS_H_ */
