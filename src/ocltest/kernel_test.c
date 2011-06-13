/*
 * kernel_test.c
 *
 *  Created on: Jun 13, 2011
 *      Author: ludwig
 */

#include "kernel_test.h"

int testKernel(void *kernel(), size_t numSizes, size_t *globalSize,
		size_t *localSize)
{
	if (numSizes == 1)
	{
		return testKernel(kernel, globalSize[0], 1, 1, localSize[0], 1, 1);
	}
	else if (numSizes == 2)
	{
		return testKernel(kernel, globalSize[0], globalSize[1], 1,
				localSize[0], localSize[1], 1);
	}
	else if (numSizes == 3)
	{
		return testKernel(kernel, globalSize[0], globalSize[1], globalSize[2],
				localSize[0], localSize[1], localSize[2]);
	}
	return INVALID_PROBLEM_DIMENSION;
}

int _testKernel(void *kernel(), size_t globalSize1, size_t globalSize2,
		size_t globalSize3, size_t localSize1, size_t localSize2,
		size_t localSize3)
{
	int globalSteps1 = globalSize1 % localSize1 == 0 ? globalSize1 / localSize1
			: globalSize1 / localSize1 + 1;
	int globalSteps2 = globalSize2 % localSize2 == 0 ? globalSize2 / localSize2
			: globalSize2 / localSize2 + 1;
	int globalSteps3 = globalSize3 % localSize3 == 0 ? globalSize3 / localSize3
			: globalSize3 / localSize3 + 1;
	for (int globalPos1 = 0; globalPos1 < globalSteps1; ++globalPos1)
	{
		for (int globalPos2 = 0; globalPos2 < globalSteps2; ++globalPos2)
		{
			for (int globalPos3 = 0; globalPos3 < globalSteps3; ++globalPos3)
			{
				int result = _runKernel(kernel, globalPos1, globalPos2,
						globalPos3, globalSize1, globalSize2, globalSize3,
						localSize1, localSize2, localSize3);
				if (result != SUCCESS)
				{
					return result;
				}
			}
		}
	}
	return SUCCESS;
}

int _runKernel(void *kernel(), int globalPos1, int globalPos2, int globalPos3,
		size_t globalSize1, size_t globalSize2, size_t globalSize3,
		size_t localSize1, size_t localSize2, size_t localSize3)
{
	for (int localPos1 = 0; localPos1 < localSize1; ++localPos1)
	{
		if (globalPos1 * localSize1 + localPos1 >= globalSize1)
		{
			continue;
		}
		for (int localPos2 = 0; localPos2 < localSize; ++localPos2)
		{
			if (globalPos2 * localSize2 + localPos2 >= globalSize2)
			{
				continue;
			}
			for (int localPos3 = 0; localPos3 < localSize; ++localPos3)
			{
				if (globalPos3 * localSize3 + localPos3 >= globalSize3)
				{
					continue;
				}
				int _startKernelThread(kernel, globalPos1, globalPos2, globalPos3, localPos1, localPos2, localPos3) {

				}

				// TODO create thread and run it
			}
		}
	}
}
