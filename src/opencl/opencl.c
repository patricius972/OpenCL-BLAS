/*
 * opencl.c
 *
 *  Created on: Apr 22, 2011
 *      Author: ludwig
 */

#include "opencl.h"

OpenCLStatus opencl_initPlatform()
{
	OpenCLStatus status = opencl_failure;

	numPlatforms = getPlatformNum();
	platformIds = malloc(numPlatforms * sizeof(*platformIds));
	numDevices = malloc(numPlatforms * sizeof(*numDevices));
	deviceIds = malloc(numPlatforms * sizeof(*deviceIds));

	/* fprintf(stdout, "%i OpenCL Platforms are available\n", getPlatformNum()); */

	ERROR_HANDLER(clGetPlatformIDs(numPlatforms, platformIds, NULL));

	for (unsigned int platform = 0; platform < numPlatforms; ++platform)
	{
		numDevices[platform] = getDeviceNum(platformIds[platform],
				CL_DEVICE_TYPE_ALL);
		deviceIds[platform]
				= malloc(numDevices[platform] * sizeof(**deviceIds));
		ERROR_HANDLER(clGetDeviceIDs(platformIds[platform], CL_DEVICE_TYPE_ALL,
						numDevices[platform], deviceIds[platform], NULL));
		/*
		 printPlatformInformation(platformIds[platform], stdout, "");
		 for (unsigned int device = 0; device < numDevices[platform]; ++device)
		 {
		 printDeviceInformation(deviceIds[platform][device]);
		 }
		 */
	}
	status = opencl_success;
	FINISH: return status;
}

OpenCLStatus opencl_dropPlatform()
{
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
	return opencl_success;
}
