/*
 * opencl_utils.h
 *
 *  Created on: May 2, 2011
 *      Author: ludwig
 */

#ifndef OPENCL_UTILS_H_
#define OPENCL_UTILS_H_

#include <string.h>
#include <stdio.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

/**
 * This macro is for OpenCL error handling. The macro checks the result value
 * of the function and in case of a failure a error message is printed to
 * stderr and a goto is followed to a label FINISH to remove and free all
 * objects allocated.
 */
#define ERROR_HANDLER(function) \
{\
	cl_int returnValue2 = function; \
	if (returnValue2 != CL_SUCCESS) \
	{ \
		printErrorMessage(#function, __FILE__, __LINE__ , returnValue2); \
		goto FINISH; \
	}\
}

void getErrorMessage(cl_int returnValue, size_t maxLength, char *msg);
void printErrorMessage(const char *str, const char *file, int line, cl_int ret);
void printProgramBuildInfo(cl_int ret, cl_program program, cl_device_id device);

#endif /* OPENCL_UTILS_H_ */
