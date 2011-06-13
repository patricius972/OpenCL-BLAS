/*
 * kernel_functions.c
 *
 *  Created on: Jun 13, 2011
 *      Author: ludwig
 */

#include "kernel_functions.h"

int initKernelTest(unsigned int numDimensions, unsigned int *globalSizes,
		unsigned int *localSizes)
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
		return THREADING_FAILURE;
	}
	return SUCCESS;
}

int dropKernelTest()
{
	free(_kernelThreads);
	if (pthread_barrier_destroy(&local_mem_fence) != 0)
	{
		return THREADING_FAILURE;
	}
	return SUCCESS;
}

int initWorkGroup(unsigned int numDimensions, unsigned int *globalIds)
{
	if (numDimensions != _numDimensions)
	{
		return INVALID_NUMBER_OF_DIMENSIONS;
	}
	_globalIds = globalIds;
	if (pthread_key_create(&_localIds, NULL) != 0)
	{
		fprintf(stderr, "Could not create key!");
		return THREADING_FAILURE;
	}
	return SUCCESS;
}

int dropWorkGroup()
{
	void *status = NULL;
	for (unsigned int threadId = 0; threadId < _workGroupThreadNum; ++threadId)
	{
		if (_kernelThreads[threadId] != 0)
		{
			if (pthread_join(_kernelThreads[threadId], &status) != 0)
			{
				return THREADING_FAILURE;
			}
			_kernelThreads[threadId] = 0;
			if (status != NULL)
			{
				free(status);
				return FAILURE_IN_KERNEL_RUN;
			}
		}
	}
	if (pthread_key_delete(_localIds) != 0)
	{
		fprintf(stderr, "Could not delete key!");
		return THREADING_FAILURE;
	}
	return SUCCESS;
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