/*
 * kernel_test.h
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
OpenCLTestStatus ocltest_runKernel(void(*kernel)(), unsigned int numDimensions,
		unsigned int *globalSizes, unsigned int *localSizes);

/**
 * This function combines all global IDs recursively to get all combinations
 * for the later work group starts. This is needed to get all global
 * combinations running as expected.
 */
OpenCLTestStatus _runKernel(void(*kernel)(), unsigned int numDimensions,
		unsigned int *globalSizes, unsigned int *localSizes,
		unsigned int *globalIds, unsigned int currentDimension);

/**
 * This method starts a work group with the given global IDs.
 */
OpenCLTestStatus _runWorkGroup(void(*kernel)(), unsigned int numDimensions,
		unsigned int *globalSizes, unsigned int *localSizes,
		unsigned int *globalIds);

/**
 * This method is used to combine all local threads for all dimensions
 * recursively. This is needed to get all local ID combinations running as
 * expected.
 */
OpenCLTestStatus _runWorkGroupThreads(void(*kernel)(),
		unsigned int numDimensions, unsigned int *globalSizes,
		unsigned int *localSizes, unsigned int *globalIds,
		unsigned int *localIds, unsigned int currentDimension);

/**
 * This function starts a single POSIX thread for a single work group thread.
 */
OpenCLTestStatus _runKernelThread(void(*kernel)(), unsigned int numDimensions,
		unsigned int *globalSizes, unsigned int *localSizes,
		unsigned int *globalIds, unsigned int *localIds);

/**
 * This struct aka. type is needed to start a POSIX thread with some
 * additional parameters.
 */
typedef struct
{
	unsigned int threadId;
	void (*kernel)();
	unsigned int *localIds;
} startParamsStruct;

/**
 * This is a helper function to start a POSIX thread with pthread_create.
 */
void *pthreadCreateCallback(void *startParams);

/**
 * This function calculates the thread id within a running work group. This
 * can be done by summing up the local IDs multiplied by their local sizes.
 */
unsigned int _getWorkGroupThreadId(unsigned int numDimensions,
		unsigned int *localSizes, unsigned int *localIds);

#endif /* KERNEL_TEST_H_ */
