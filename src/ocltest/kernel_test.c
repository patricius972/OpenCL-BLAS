/*
 * kernel_test.c
 *
 *  Created on: Jun 13, 2011
 *      Author: ludwig
 */

#include "kernel_test.h"

int ocltest_runKernel(void(*kernel)(), unsigned int numDimensions,
		unsigned int *globalSizes, unsigned int *localSizes)
{
	if (numDimensions > 3)
	{
		return INVALID_PROBLEM_DIMENSION;
	}
	for (unsigned int dim = 0; dim < numDimensions; ++dim)
	{
		if (globalSizes[dim] % localSizes[dim] != 0)
		{
			return INVALID_LOCAL_SIZE;
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

int _runKernel(void(*kernel)(), unsigned int numDimensions,
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
			if (result != SUCCESS)
			{
				return result;
			}
		}
		return SUCCESS;
	}
	else
	{
		return _runWorkGroup(kernel, numDimensions, globalSizes, localSizes,
				globalIds);
	}
}

int _runWorkGroup(void(*kernel)(), unsigned int numDimensions,
		unsigned int *globalSizes, unsigned int *localSizes,
		unsigned int *globalIds)
{
	printf("Starting workgroup!\n");
	initWorkGroup(numDimensions, globalIds);
	unsigned int *localIds = malloc(sizeof(unsigned int) * numDimensions);
	int result = _runWorkGroupThreads(kernel, numDimensions, globalSizes,
			localSizes, globalIds, localIds, 0);
	printf("Destroying workgroup!\n");
	dropWorkGroup();
	printf("Workgroup destroyed!\n");
	free(localIds);
	return result;

}

int _runWorkGroupThreads(void(*kernel)(), unsigned int numDimensions,
		unsigned int *globalSizes, unsigned int *localSizes,
		unsigned int *globalIds, unsigned int *localIds,
		unsigned int currentDimension)
{
	if (currentDimension < numDimensions)
	{
		for (localIds[currentDimension] = 0; localIds[currentDimension]
				< localSizes[currentDimension]; ++localIds[currentDimension])
		{
			int result = _runWorkGroupThreads(kernel, numDimensions,
					globalSizes, localSizes, globalIds, localIds,
					currentDimension + 1);
			if (result != SUCCESS)
			{
				return result;
			}
		}
		return SUCCESS;
	}
	else
	{
		return _runKernelThread(kernel, numDimensions, globalSizes, localSizes,
				globalIds, localIds);
	}
}

int _runKernelThread(void(*kernel)(), unsigned int numDimensions,
		unsigned int *globalSizes, unsigned int *localSizes,
		unsigned int *globalIds, unsigned int *localIds)
{
	unsigned int threadId = _getWorkGroupThreadId(numDimensions, localSizes,
			localIds);

	printf("start kernel thread %2i: ", threadId);
	for (unsigned int dim = 0; dim < numDimensions; ++dim)
	{
		if (dim > 0)
		{
			printf(",");
		}
		printf("%i", globalIds[dim]);
	}
	printf(" / ");
	for (unsigned int dim = 0; dim < numDimensions; ++dim)
	{
		if (dim > 0)
		{
			printf(",");
		}
		printf("%i", localIds[dim]);
	}
	printf("\n");

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
		return THREADING_FAILURE;
	}
	if (_kernelThreads[threadId] == 0)
	{
		fprintf(stderr, "ERROR!!!\n");
	}

	return SUCCESS;
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
