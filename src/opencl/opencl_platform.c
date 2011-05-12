/*
 * opencl_platform.c
 *
 *  Created on: Apr 25, 2011
 *      Author: ludwig
 */

#include "opencl_platform.h"

unsigned int getPlatformNum()
{
	unsigned int num;
	if (clGetPlatformIDs(0, NULL, &num) == CL_SUCCESS)
	{
		return num;
	}
	return 0;
}

unsigned int getDeviceNum(cl_platform_id platformId, cl_device_type type)
{
	unsigned int num;
	if (clGetDeviceIDs(platformId, type, 0, NULL, &num) == CL_SUCCESS)
	{
		return num;
	}
	return 0;
}

char *getPlaformInformationString(cl_platform_id platformId,
		cl_platform_info info)
{
	char *str = malloc(1024 * sizeof(char));
	if (clGetPlatformInfo(platformId, info, 1024, str, NULL) == CL_SUCCESS)
	{
		return str;
	}
	free(str);
	return NULL;
}

char *getPlatformName(cl_platform_id platformId)
{
	return getPlaformInformationString(platformId, CL_PLATFORM_NAME);
}

char *getPlatformVersion(cl_platform_id platformId)
{
	return getPlaformInformationString(platformId, CL_PLATFORM_VERSION);
}

char *getPlatformVendor(cl_platform_id platformId)
{
	return getPlaformInformationString(platformId, CL_PLATFORM_VENDOR);
}

char *getPlatformProfile(cl_platform_id platformId)
{
	return getPlaformInformationString(platformId, CL_PLATFORM_PROFILE);
}

char *getPlatformExtensions(cl_platform_id platformId)
{
	return getPlaformInformationString(platformId, CL_PLATFORM_EXTENSIONS);
}

void printPlatformInformation(cl_platform_id platformId, FILE *output,
		char *leading_comment)
{
	char *name = getPlatformName(platformId);
	char *version = getPlatformName(platformId);
	char *vendor = getPlatformName(platformId);
	char *profile = getPlatformName(platformId);
	char *extensions = getPlatformName(platformId);

	fprintf(output, "=====================================\n");
	fprintf(output, "INFORMATION for PLATFORM %s\n", name);
	fprintf(output, "=====================================\n");
	if (strlen(leading_comment) > 0)
	{
		fprintf(output, "%s\n", leading_comment);
	}
	fprintf(output, "Name: %s\n", name);
	fprintf(output, "Version: %s\n", version);
	fprintf(output, "Vendor: %s\n", vendor);
	fprintf(output, "Profile: %s\n", profile);
	fprintf(output, "Extensions: %s\n", extensions);

	free(name);
	free(version);
	free(vendor);
	free(profile);
	free(extensions);
}
