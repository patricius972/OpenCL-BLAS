/*
 * opencl_device.h
 *
 *  Created on: Apr 25, 2011
 *      Author: ludwig
 */

#ifndef OPENCL_DEVICE_H_
#define OPENCL_DEVICE_H_

#include <string.h>
#include <stdio.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

void printDeviceInformation(cl_device_id deviceId);

cl_uint getNumberOfCPUS(cl_device_id device);

#endif /* OPENCL_DEVICE_H_ */
