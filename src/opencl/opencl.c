/*
 * opencl.c
 *
 *  Created on: Apr 22, 2011
 *      Author: ludwig
 */

#include "opencl.h"

UplaStatus opencl_initPlatform()
{
	UplaStatus status = FAILURE;

	numPlatforms = getPlatformNum();
	platformIds = malloc(numPlatforms * sizeof(*platformIds));
	numDevices = malloc(numPlatforms * sizeof(*numDevices));
	deviceIds = malloc(numPlatforms * sizeof(*deviceIds));

	fprintf(stdout, "%i OpenCL Platforms are available\n", getPlatformNum());
	ERROR_HANDLER(clGetPlatformIDs(numPlatforms, platformIds, NULL));

	for (unsigned int platform = 0; platform < numPlatforms; ++platform)
	{
		numDevices[platform] = getDeviceNum(platformIds[platform],
				CL_DEVICE_TYPE_ALL);
		deviceIds[platform]
				= malloc(numDevices[platform] * sizeof(**deviceIds));
		ERROR_HANDLER(clGetDeviceIDs(platformIds[platform], CL_DEVICE_TYPE_ALL,
						numDevices[platform], deviceIds[platform], NULL));
		printPlatformInformation(platformIds[platform], stdout, "");
		for (unsigned int device = 0; device < numDevices[platform]; ++device)
		{
			printDeviceInformation(deviceIds[platform][device]);
		}
	}

	usedDevice = deviceIds[1][0];
	fprintf(stdout, "SELECTED DEVICE:\n");
	printDeviceInformation(usedDevice);

	cl_int ret;
	usedContext = clCreateContext(NULL, 1, &usedDevice, NULL, NULL, &ret);
	ERROR_HANDLER(ret)

	usedCommandQueue = clCreateCommandQueue(usedContext, usedDevice, 0, &ret);
	ERROR_HANDLER(ret);

	/* Create Kernel Program from the source */

	char definitions[256];
	sprintf(definitions, "#define SUBMATRIX_SIZE %i\n", SUBMATRIX_SIZE);
	fprintf(stdout, "%s", definitions);

	const size_t sizes[] =
	{ strlen(definitions), strlen(opencl_types), strlen(opencl_sgemm_kernel),
			strlen(opencl_dgemm_kernel) };
	const char *sources[] =
	{ definitions, opencl_types, opencl_sgemm_kernel, opencl_dgemm_kernel };
	program = clCreateProgramWithSource(usedContext, 4, sources, sizes, &ret);
	ERROR_HANDLER(ret);

	/* Build Kernel Program */
	ret = clBuildProgram(program, 1, &usedDevice, NULL, NULL, NULL);
	if (ret != CL_SUCCESS)
	{
		printProgramBuildInfo(ret, program, usedDevice);
		ERROR_HANDLER(ret);
	}

	status = SUCCESS;
	FINISH: return status;
}

UplaStatus opencl_dropPlatform()
{
	clReleaseProgram(program);

	if (usedCommandQueue != NULL)
	{
		clReleaseCommandQueue(usedCommandQueue);
		usedCommandQueue = NULL;
	}
	if (usedContext != NULL)
	{
		clReleaseContext(usedContext);
		usedContext = NULL;
	}
	if (deviceIds != NULL)
	{
		for (unsigned int i = 0; i < numPlatforms; ++i)
		{
			free(deviceIds[i]);
		}
		free(deviceIds);
		deviceIds = NULL;
	}
	if (numDevices != NULL)
	{
		free(numDevices);
		numDevices = NULL;
	}
	if (platformIds != NULL)
	{
		free(platformIds);
		platformIds = NULL;
		numPlatforms = 0;
	}
	return SUCCESS;
}
