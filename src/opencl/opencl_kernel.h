/*
 * opencl_kernel.h
 *
 *  Created on: May 2, 2011
 *      Author: ludwig
 */

#ifndef OPENCL_KERNEL_H_
#define OPENCL_KERNEL_H_

#include <string.h>
#include <stdio.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#include "opencl_utils.h"

void printKernelWorkGroupInformation(cl_kernel kernel, cl_device_id device);

#endif /* OPENCL_KERNEL_H_ */
