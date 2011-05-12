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

#include <uplabase/types.h>

#include <oclblas/oclutils/ocltypes.h>
#include <oclblas/blas3/gemm_kernels.h>

#include "opencl_utils.h"
#include "opencl_platform.h"
#include "opencl_device.h"
#include "opencl_kernel.h"

cl_uint numPlatforms;
cl_platform_id *platformIds;

cl_uint *numDevices;
cl_device_id **deviceIds;

cl_device_id usedDevice;
cl_context usedContext;
cl_command_queue usedCommandQueue;

cl_program program;

void getErrorMessage(cl_int returnValue, size_t maxLength, char *msg);

UplaStatus
opencl_initPlatform();

UplaStatus
opencl_dropPlatform();

#endif /* OPENCL_H_ */
