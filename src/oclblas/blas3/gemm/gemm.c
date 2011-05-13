/*
 * opencl_blas3_gemm.c
 *
 *  Created on: Apr 15, 2011
 *      Author: ludwig
 */

#include "gemm.h"

OpenCLStatus opencl_sgemm(const OCLBMatrixOrder order,
		const OCLBTranspose transposeA, const OCLBTranspose transposeB,
		const int m, const int n, const int k, const float alpha, float *a,
		const int lda, float *b, const int ldb, const float beta, float *c,
		const int ldc)
{
	cl_int ret;
	OpenCLStatus status = FAILURE;

	cl_device_id usedDevice = deviceIds[1][0];
	fprintf(stdout, "SELECTED DEVICE:\n");
	printDeviceInformation(usedDevice);

	cl_context usedContext = clCreateContext(NULL, 1, &usedDevice, NULL, NULL,
			&ret);
	ERROR_HANDLER(ret);

	cl_command_queue usedCommandQueue = clCreateCommandQueue(usedContext,
			usedDevice, 0, &ret);
	ERROR_HANDLER(ret);

	/* Create Kernel Program from the source */

	const int SUBMATRIX_SIZE = 16;

	char definitions[256];
	sprintf(definitions, "#define SUBMATRIX_SIZE %i\n", SUBMATRIX_SIZE);
	fprintf(stdout, "%s", definitions);

	const size_t sizes[] =
	{ strlen(definitions), strlen(opencl_types), strlen(opencl_sgemm_kernel) };
	const char *sources[] =
	{ definitions, opencl_types, opencl_sgemm_kernel };
	cl_program program = clCreateProgramWithSource(usedContext, 3, sources,
			sizes, &ret);
	ERROR_HANDLER(ret);

	/* Build Kernel Program */
	ret = clBuildProgram(program, 1, &usedDevice, NULL, NULL, NULL);
	if (ret != CL_SUCCESS)
	{
		printProgramBuildInfo(ret, program, usedDevice);
		ERROR_HANDLER(ret);
	}

	cl_mem memA = NULL;
	cl_mem memB = NULL;
	cl_mem memC = NULL;

	cl_kernel kernel = clCreateKernel(program, "sgemm", &ret);
	ERROR_HANDLER(ret);

	/* Create Memory Buffer */
	memA = clCreateBuffer(usedContext, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
			lda * k * sizeof(float), a, &ret);
	ERROR_HANDLER(ret);
	memB = clCreateBuffer(usedContext, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
			ldb * n * sizeof(float), b, &ret);
	ERROR_HANDLER(ret);
	if (beta != 0.0)
	{
		memC = clCreateBuffer(usedContext, CL_MEM_READ_WRITE
				| CL_MEM_COPY_HOST_PTR, ldc * n * sizeof(float), c, &ret);
	}
	else
	{
		memC = clCreateBuffer(usedContext, CL_MEM_WRITE_ONLY, ldc * n
				* sizeof(float), NULL, &ret);
	}
	ERROR_HANDLER(ret);

	/* Set OpenCL Kernel Arguments */
	int colMajor = order == ColumnMajor ? 1 : 0;
	int transa = transposeA == NO ? 0 : 1;
	int transb = transposeB == NO ? 0 : 1;
	ERROR_HANDLER(clSetKernelArg(kernel, 0, sizeof(int), (void *) &colMajor));
	ERROR_HANDLER(clSetKernelArg(kernel, 1, sizeof(int), (void *) &transa));
	ERROR_HANDLER(clSetKernelArg(kernel, 2, sizeof(int), (void *) &transb));
	ERROR_HANDLER(clSetKernelArg(kernel, 3, sizeof(int), (void *) &m));
	ERROR_HANDLER(clSetKernelArg(kernel, 4, sizeof(int), (void *) &n));
	ERROR_HANDLER(clSetKernelArg(kernel, 5, sizeof(int), (void *) &k));
	ERROR_HANDLER(clSetKernelArg(kernel, 6, sizeof(float), (void *) &alpha));
	ERROR_HANDLER(clSetKernelArg(kernel, 7, sizeof(cl_mem), (void *) &memA));
	ERROR_HANDLER(clSetKernelArg(kernel, 8, sizeof(int), (void *) &lda));
	ERROR_HANDLER(clSetKernelArg(kernel, 9, sizeof(cl_mem), (void *) &memB));
	ERROR_HANDLER(clSetKernelArg(kernel, 10, sizeof(int), (void *) &ldb));
	ERROR_HANDLER(clSetKernelArg(kernel, 11, sizeof(float), (void *) &beta));
	ERROR_HANDLER(clSetKernelArg(kernel, 12, sizeof(cl_mem), (void *) &memC));
	ERROR_HANDLER(clSetKernelArg(kernel, 13, sizeof(int), (void *) &ldc));

	/* Execute OpenCL Kernel */
	size_t global_item_size[2];
	global_item_size[0] = m % SUBMATRIX_SIZE == 0 ? m
			: (m / SUBMATRIX_SIZE + 1) * SUBMATRIX_SIZE;
	global_item_size[1] = n % SUBMATRIX_SIZE == 0 ? n
			: (n / SUBMATRIX_SIZE + 1) * SUBMATRIX_SIZE;
	size_t local_item_size[2];
	local_item_size[0] = SUBMATRIX_SIZE;
	local_item_size[1] = SUBMATRIX_SIZE;

	ret = clEnqueueNDRangeKernel(usedCommandQueue, kernel, 2, NULL,
			global_item_size, local_item_size, 0, NULL, NULL);
	ERROR_HANDLER(ret);

	/* Finalization */
	clFlush(usedCommandQueue);
	clFinish(usedCommandQueue);

	/* Copy results from the memory buffer */
	ret = clEnqueueReadBuffer(usedCommandQueue, memC, CL_TRUE, 0, ldc * n
			* sizeof(float), c, 0, NULL, NULL);
	ERROR_HANDLER(ret);

	status = SUCCESS;

	FINISH:

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

	if (memA != NULL)
	{
		clReleaseMemObject(memA);
	}
	if (memB != NULL)
	{
		clReleaseMemObject(memB);
	}
	if (memC != NULL)
	{
		clReleaseMemObject(memC);
	}

	return status;
}

OpenCLStatus opencl_dgemm(const OCLBMatrixOrder order,
		const OCLBTranspose transposeA, const OCLBTranspose transposeB,
		const int m, const int n, const int k, const double alpha, double *a,
		const int lda, double *b, const int ldb, const double beta, double *c,
		const int ldc)
{
#if OCL_DOUBLE_SUPPORTED == 1
	cl_int ret;

	/* Create Memory Buffer */
	cl_mem memA = clCreateBuffer(usedContext, CL_MEM_READ_WRITE, lda * k
			* sizeof(float), NULL, &ret);
	if (ret != 0)
	{
		fprintf(stderr, "Could not create buffer for A!\n");
		return FAILURE;
	}
	cl_mem memB = clCreateBuffer(usedContext, CL_MEM_READ_WRITE, ldb * n
			* sizeof(float), NULL, &ret);
	if (ret != 0)
	{
		fprintf(stderr, "Could not create buffer for B!\n");
		return FAILURE;
	}
	cl_mem memC = clCreateBuffer(usedContext, CL_MEM_READ_WRITE, ldc * n
			* sizeof(float), NULL, &ret);
	if (ret != 0)
	{
		fprintf(stderr, "Could not create buffer for C!\n");
		return FAILURE;
	}

	ret = clEnqueueWriteBuffer(usedCommandQueue, memA, CL_TRUE, 0, lda * k
			* sizeof(float), a, 0, NULL, NULL);
	if (ret != 0)
	{
		fprintf(stderr, "Could not write buffer for A!\n");
		return FAILURE;
	}
	ret = clEnqueueWriteBuffer(usedCommandQueue, memB, CL_TRUE, 0, ldb * n
			* sizeof(float), b, 0, NULL, NULL);
	if (ret != 0)
	{
		fprintf(stderr, "Could not write buffer for B!\n");
		return FAILURE;
	}
	ret = clEnqueueWriteBuffer(usedCommandQueue, memC, CL_TRUE, 0, ldc * n
			* sizeof(float), c, 0, NULL, NULL);
	if (ret != 0)
	{
		fprintf(stderr, "Could not write buffer for C!\n");
		return FAILURE;
	}

	/* Set OpenCL Kernel Arguments */
	int colMajor = order == ColumnMajor ? 1 : 0;
	int transa = transposeA == NO ? 0 : 1;
	int transb = transposeB == NO ? 0 : 1;
	ret = clSetKernelArg(dgemmKernel, 0, sizeof(int), (void *) &colMajor);
	if (ret != 0)
	{
		fprintf(stderr, "Could not set transpose A!\n");
		return FAILURE;
	}
	ret = clSetKernelArg(dgemmKernel, 1, sizeof(int), (void *) &transa);
	if (ret != 0)
	{
		fprintf(stderr, "Could not set transpose A!\n");
		return FAILURE;
	}
	ret = clSetKernelArg(dgemmKernel, 2, sizeof(int), (void *) &transb);
	if (ret != 0)
	{
		fprintf(stderr, "Could not set transpose B!\n");
		return FAILURE;
	}
	ret = clSetKernelArg(dgemmKernel, 3, sizeof(int), (void *) &m);
	if (ret != 0)
	{
		fprintf(stderr, "Could not set m!\n");
		return FAILURE;
	}
	ret = clSetKernelArg(dgemmKernel, 4, sizeof(int), (void *) &n);
	if (ret != 0)
	{
		fprintf(stderr, "Could not set n!\n");
		return FAILURE;
	}
	ret = clSetKernelArg(dgemmKernel, 5, sizeof(int), (void *) &k);
	if (ret != 0)
	{
		fprintf(stderr, "Could not set k!\n");
		return FAILURE;
	}
	ret = clSetKernelArg(dgemmKernel, 6, sizeof(float), (void *) &alpha);
	if (ret != 0)
	{
		fprintf(stderr, "Could not set alpha!\n");
		return FAILURE;
	}
	ret = clSetKernelArg(dgemmKernel, 7, sizeof(cl_mem), (void *) &memA);
	if (ret != 0)
	{
		fprintf(stderr, "Could not set mem A!\n");
		return FAILURE;
	}
	ret = clSetKernelArg(dgemmKernel, 8, sizeof(int), (void *) &lda);
	if (ret != 0)
	{
		fprintf(stderr, "Could not set lda!\n");
		return FAILURE;
	}
	ret = clSetKernelArg(dgemmKernel, 9, sizeof(cl_mem), (void *) &memB);
	if (ret != 0)
	{
		fprintf(stderr, "Could not set mem B!\n");
		return FAILURE;
	}
	ret = clSetKernelArg(dgemmKernel, 10, sizeof(int), (void *) &ldb);
	if (ret != 0)
	{
		fprintf(stderr, "Could not set ldb!\n");
		return FAILURE;
	}
	ret = clSetKernelArg(dgemmKernel, 11, sizeof(float), (void *) &beta);
	if (ret != 0)
	{
		fprintf(stderr, "Could not set alpha!\n");
		return FAILURE;
	}
	ret = clSetKernelArg(dgemmKernel, 12, sizeof(cl_mem), (void *) &memC);
	if (ret != 0)
	{
		fprintf(stderr, "Could not set mem C!\n");
		return FAILURE;
	}
	ret = clSetKernelArg(dgemmKernel, 13, sizeof(int), (void *) &ldc);
	if (ret != 0)
	{
		fprintf(stderr, "Could not set ldc!\n");
		return FAILURE;
	}

	/* Execute OpenCL Kernel */
	size_t global_item_size[2];
	global_item_size[0] = m % 8 == 0 ? m : (m / 8 + 1) * 8;
	global_item_size[1] = n % 8 == 0 ? n : (n / 8 + 1) * 8;
	size_t local_item_size[3];
	local_item_size[0] = 8;
	local_item_size[1] = 8;

	ret = clEnqueueNDRangeKernel(usedCommandQueue, dgemmKernel, 2, NULL,
			global_item_size, local_item_size, 0, NULL, NULL);
	if (ret != 0)
	{
		fprintf(stderr, "Could not enqueue nd range kernel (%i). Abort!\n", ret);
		return FAILURE;
	}

	/* Copy results from the memory buffer */
	ret = clEnqueueReadBuffer(usedCommandQueue, memC, CL_TRUE, 0, ldc * n
			* sizeof(float), c, 0, NULL, NULL);
	if (ret != 0)
	{
		char str[64];
		getErrorMessage(ret, 64, str);
		fprintf(stderr, "Could not read buffer (%s). Abort!\n", str);
		return FAILURE;
	}

	/* Finalization */
	ret = clFlush(usedCommandQueue);
	ret = clFinish(usedCommandQueue);
	ret = clReleaseMemObject(memA);
	ret = clReleaseMemObject(memB);
	ret = clReleaseMemObject(memC);

	return SUCCESS;
#else
	return ARCHITECTURE_MISMATCH;
#endif
}

OpenCLStatus opencl_cgemm(const OCLBMatrixOrder order,
		const OCLBTranspose transposeA, const OCLBTranspose transposeB,
		const int m, const int n, const int k, const void *alpha, void *a,
		const int lda, void *b, const int ldb, const void *beta, void *c,
		const int ldc)
{
	return NOT_IMPLEMENTED;
}

OpenCLStatus opencl_zgemm(const OCLBMatrixOrder order,
		const OCLBTranspose transposeA, const OCLBTranspose transposeB,
		const int m, const int n, const int k, const void *alpha, void *a,
		const int lda, void *b, const int ldb, const void *beta, void *c,
		const int ldc)
{
	return NOT_IMPLEMENTED;
}
