/*
 * opencl.h
 *
 *  Created on: Apr 22, 2011
 *      Author: ludwig
 */

#ifndef OPENCL_H
#define OPENCL_H

#include <string.h>
#include <stdio.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#include <blas3/gemm/gemm_kernels.h>

#include "opencl_utils.h"
#include "opencl_platform.h"
#include "opencl_device.h"
#include "opencl_kernel.h"
#include "opencl_types.h"

cl_uint numPlatforms;
cl_platform_id *platformIds;

cl_uint *numDevices;
cl_device_id **deviceIds;

void getErrorMessage(cl_int returnValue, size_t maxLength, char *msg);

OpenCLStatus
opencl_initPlatform();

OpenCLStatus
opencl_dropPlatform();

#endif /* OPENCL_H_ */
