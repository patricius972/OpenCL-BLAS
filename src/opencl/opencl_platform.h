/*
 * opencl_platform.h
 *
 *  Created on: Apr 25, 2011
 *      Author: ludwig
 */

#ifndef OPENCL_PLATFORM_H_
#define OPENCL_PLATFORM_H_

#include <stdio.h>
#include <string.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

unsigned int getPlatformNum();
unsigned int getDeviceNum(cl_platform_id platformId, cl_device_type type);

char *getPlaformInformationString(cl_platform_id platformId,
		cl_platform_info info);
char *getPlatformName(cl_platform_id platformId);
char *getPlatformVersion(cl_platform_id platformId);
char *getPlatformVendor(cl_platform_id platformId);
char *getPlatformProfile(cl_platform_id platformId);
char *getPlatformExtensions(cl_platform_id platformId);

void printPlatformInformation(cl_platform_id platformId, FILE *output,
		char *leading_comment);

#endif /* OPENCL_PLATFORM_H_ */
