/*
 * kernel_functions.c
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

#include "kernel_functions.h"

OpenCLTestStatus initKernelTest(unsigned int numDimensions,
		unsigned int *globalSizes, unsigned int *localSizes)
{
	_numDimensions = numDimensions;
	_globalSizes = globalSizes;
	_localSizes = localSizes;
	_workGroupThreadNum = 1;
	for (unsigned int dim = 0; dim < numDimensions; ++dim)
	{
		_workGroupThreadNum *= _localSizes[dim];
	}
	_kernelThreads = calloc(_workGroupThreadNum, sizeof(pthread_t));
	if (pthread_barrier_init(&local_mem_fence, NULL, _workGroupThreadNum) != 0)
	{
		return ocltest_threading_failure;
	}
	return ocltest_success;
}

OpenCLTestStatus dropKernelTest()
{
	free(_kernelThreads);
	if (pthread_barrier_destroy(&local_mem_fence) != 0)
	{
		return ocltest_threading_failure;
	}
	return ocltest_success;
}

OpenCLTestStatus initWorkGroup(unsigned int numDimensions,
		unsigned int *globalIds)
{
	if (numDimensions != _numDimensions)
	{
		return ocltest_invalid_number_of_dimensions;
	}
	_globalIds = globalIds;
	if (pthread_key_create(&_localIds, NULL) != 0)
	{
		fprintf(stderr, "Could not create key!");
		return ocltest_threading_failure;
	}
	return ocltest_success;
}

OpenCLTestStatus dropWorkGroup()
{
	void *status = NULL;
	for (unsigned int threadId = 0; threadId < _workGroupThreadNum; ++threadId)
	{
		if (_kernelThreads[threadId] != 0)
		{
			if (pthread_join(_kernelThreads[threadId], &status) != 0)
			{
				return ocltest_threading_failure;
			}
			_kernelThreads[threadId] = 0;
			if (status != NULL)
			{
				free(status);
				return ocltest_failure_in_kernel_run;
			}
		}
	}
	if (pthread_key_delete(_localIds) != 0)
	{
		fprintf(stderr, "Could not delete key!");
		return ocltest_threading_failure;
	}
	return ocltest_success;
}

int get_global_id(unsigned int dim)

{
	if (dim < _numDimensions)
	{
		return _globalIds[dim] * _localSizes[dim] + get_local_id(dim);
	}
	return 0;
}

int get_local_id(unsigned int dim)
{
	unsigned int *localIds;
	localIds = pthread_getspecific(_localIds);
	if (localIds == NULL)
	{
		fprintf(stderr, "Could not get local ids!\n");
		return 0;
	}
	if (dim < _numDimensions)
	{
		return localIds[dim];
	}
	return 0;
}

int get_global_size(unsigned int dim)
{
	if (dim < _numDimensions)
	{
		return _globalSizes[dim];
	}
	return 0;
}

int get_local_size(unsigned int dim)
{
	if (dim < _numDimensions)
	{
		return _localSizes[dim];
	}
	return 0;
}

void barrier(unsigned int barrier_type)
{
	if (barrier_type == CLK_LOCAL_MEM_FENCE)
	{
		int result = pthread_barrier_wait(&local_mem_fence);
		if ((result != 0) && (result != PTHREAD_BARRIER_SERIAL_THREAD))
		{
			fprintf(stderr, "Could not synchronize with barrier!\n");
			int *i = malloc(sizeof(int));
			pthread_exit(i);
		}
	}
}
