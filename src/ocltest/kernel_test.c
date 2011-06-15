/*
 * kernel_test.c
 *
 *  Created on: Jun 13, 2011
 *      Author: ludwig
 */

#include "kernel_test.h"

OpenCLTestStatus ocltest_runKernel(void(*kernel)(), unsigned int numDimensions,
		unsigned int *globalSizes, unsigned int *localSizes)
{
	if (numDimensions > 3)
	{
		return ocltest_invalid_problem_dimension;
	}
	for (unsigned int dim = 0; dim < numDimensions; ++dim)
	{
		if (globalSizes[dim] % localSizes[dim] != 0)
		{
			return ocltest_invalid_local_size;
		}
	}
	initKernelTest(numDimensions, globalSizes, localSizes);
	unsigned int *globalIds = malloc(sizeof(unsigned int) * numDimensions);
	int result = _runKernel(kernel, numDimensions, globalSizes, localSizes,
			globalIds, 0);
	dropKernelTest();
	free(globalIds);
	return result;
}

OpenCLTestStatus _runKernel(void(*kernel)(), unsigned int numDimensions,
		unsigned int *globalSizes, unsigned int *localSizes,
		unsigned int *globalIds, unsigned int currentDimension)
{
	if (currentDimension < numDimensions)
	{
		int stepNum = globalSizes[currentDimension]
				/ localSizes[currentDimension];
		for (globalIds[currentDimension] = 0; globalIds[currentDimension]
				< stepNum; ++globalIds[currentDimension])
		{
			int result = _runKernel(kernel, numDimensions, globalSizes,
					localSizes, globalIds, currentDimension + 1);
			if (result != ocltest_success)
			{
				return result;
			}
		}
		return ocltest_success;
	}
	else
	{
		return _runWorkGroup(kernel, numDimensions, globalSizes, localSizes,
				globalIds);
	}
}

OpenCLTestStatus _runWorkGroup(void(*kernel)(), unsigned int numDimensions,
		unsigned int *globalSizes, unsigned int *localSizes,
		unsigned int *globalIds)
{
	initWorkGroup(numDimensions, globalIds);
	unsigned int *localIds = malloc(sizeof(unsigned int) * numDimensions);
	int result = _runWorkGroupThreads(kernel, numDimensions, globalSizes,
			localSizes, globalIds, localIds, 0);
	dropWorkGroup();
	free(localIds);
	return result;
}

OpenCLTestStatus _runWorkGroupThreads(void(*kernel)(),
		unsigned int numDimensions, unsigned int *globalSizes,
		unsigned int *localSizes, unsigned int *globalIds,
		unsigned int *localIds, unsigned int currentDimension)
{
	if (currentDimension < numDimensions)
	{
		for (localIds[currentDimension] = 0; localIds[currentDimension]
				< localSizes[currentDimension]; ++localIds[currentDimension])
		{
			int result = _runWorkGroupThreads(kernel, numDimensions,
					globalSizes, localSizes, globalIds, localIds,
					currentDimension + 1);
			if (result != ocltest_success)
			{
				return result;
			}
		}
		return ocltest_success;
	}
	else
	{
		return _runKernelThread(kernel, numDimensions, globalSizes, localSizes,
				globalIds, localIds);
	}
}

OpenCLTestStatus _runKernelThread(void(*kernel)(), unsigned int numDimensions,
		unsigned int *globalSizes, unsigned int *localSizes,
		unsigned int *globalIds, unsigned int *localIds)
{
	unsigned int threadId = _getWorkGroupThreadId(numDimensions, localSizes,
			localIds);

	startParamsStruct *params = malloc(sizeof(startParamsStruct));
	params->kernel = kernel;
	params->localIds = malloc(sizeof(unsigned int) * numDimensions);
	for (unsigned int dim = 0; dim < numDimensions; ++dim)
	{
		params->localIds[dim] = localIds[dim];
	}
	params->threadId = threadId;
	if (pthread_create(&_kernelThreads[threadId], NULL, pthreadCreateCallback,
			params) != 0)
	{
		return ocltest_threading_failure;
	}
	if (_kernelThreads[threadId] == 0)
	{
		fprintf(stderr, "ERROR!!!\n");
	}

	return ocltest_success;
}

void *pthreadCreateCallback(void *startParams)
{
	startParamsStruct *params = (startParamsStruct*) startParams;

	if (pthread_setspecific(_localIds, params->localIds) != 0)
	{
		free(params->localIds);
		free(params);
		fprintf(stderr, "Could not set specific!");
		int *i = malloc(sizeof(int));
		pthread_exit(i);
	}

	params->kernel();

	/* free all resources... */
	free(params->localIds);
	free(params);
	pthread_exit(NULL);
}

unsigned int _getWorkGroupThreadId(unsigned int numDimensions,
		unsigned int *localSizes, unsigned int *localIds)
{
	unsigned int threadId = 0;
	for (unsigned int dim = 0; dim < numDimensions; ++dim)
	{
		unsigned int dimId = localIds[dim];
		for (unsigned int dim2 = dim + 1; dim2 < numDimensions; ++dim2)
		{
			dimId *= localSizes[dim2];
		}
		threadId += dimId;
	}
	return threadId;
}
