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
	OpenCLStatus status = opencl_failure;

	cl_device_id usedDevice = deviceIds[1][0];

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

	const size_t sizes[] =
	{ strlen(definitions), strlen(oclFloatMatrix), strlen(oclGetMatrixFloat),
			strlen(oclSetMatrixFloat), strlen(oclSGEMM) };
	const char *sources[] =
	{ definitions, oclFloatMatrix, oclGetMatrixFloat, oclSetMatrixFloat,
			oclSGEMM };
	cl_program program = clCreateProgramWithSource(usedContext, 5, sources,
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
	if (order == ColumnMajor)
	{
		if (transposeA == NO)
		{
			memA = clCreateBuffer(usedContext,
					CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
					lda * k * sizeof(float), a, &ret);
			ERROR_HANDLER(ret);
		}
		else
		{
			memA = clCreateBuffer(usedContext,
					CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
					lda * m * sizeof(float), a, &ret);
			ERROR_HANDLER(ret);
		}
		if (transposeB == NO)
		{
			memB = clCreateBuffer(usedContext,
					CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
					ldb * n * sizeof(float), b, &ret);
			ERROR_HANDLER(ret);
		}
		else
		{
			memB = clCreateBuffer(usedContext,
					CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
					ldb * k * sizeof(float), b, &ret);
			ERROR_HANDLER(ret);
		}
		if (beta != 0.0)
		{
			memC = clCreateBuffer(usedContext,
					CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
					ldc * n * sizeof(float), c, &ret);
		}
		else
		{
			memC = clCreateBuffer(usedContext, CL_MEM_WRITE_ONLY,
					ldc * n * sizeof(float), NULL, &ret);
		}
		ERROR_HANDLER(ret);
	}
	else
	{
		if (transposeA == NO)
		{
			memA = clCreateBuffer(usedContext,
					CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
					lda * m * sizeof(float), a, &ret);
			ERROR_HANDLER(ret);
		}
		else
		{
			memA = clCreateBuffer(usedContext,
					CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
					lda * k * sizeof(float), a, &ret);
			ERROR_HANDLER(ret);
		}
		if (transposeB == NO)
		{
			memB = clCreateBuffer(usedContext,
					CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
					ldb * k * sizeof(float), b, &ret);
			ERROR_HANDLER(ret);
		}
		else
		{
			memB = clCreateBuffer(usedContext,
					CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
					ldb * n * sizeof(float), b, &ret);
			ERROR_HANDLER(ret);
		}
		if (beta != 0.0)
		{
			memC = clCreateBuffer(usedContext,
					CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
					ldc * m * sizeof(float), c, &ret);
		}
		else
		{
			memC = clCreateBuffer(usedContext, CL_MEM_WRITE_ONLY,
					ldc * m * sizeof(float), NULL, &ret);
		}
		ERROR_HANDLER(ret);
	}

	/* Set OpenCL Kernel Arguments */
	int colMajor = order == ColumnMajor ? 1 : 0;
	int transa = transposeA == NO ? 0 : 1;
	int transb = transposeB == NO ? 0 : 1;
	unsigned int submatrixSize = SUBMATRIX_SIZE;
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
	ERROR_HANDLER(clSetKernelArg(kernel, 14, sizeof(unsigned int), &submatrixSize));
	ERROR_HANDLER(clSetKernelArg(kernel, 15, sizeof(cl_float) * SUBMATRIX_SIZE * SUBMATRIX_SIZE, NULL));
	ERROR_HANDLER(clSetKernelArg(kernel, 16, sizeof(cl_float) * SUBMATRIX_SIZE * SUBMATRIX_SIZE, NULL));

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
	if (order == ColumnMajor)
	{
		ret = clEnqueueReadBuffer(usedCommandQueue, memC, CL_TRUE, 0,
				ldc * n * sizeof(float), c, 0, NULL, NULL);
	}
	else
	{
		ret = clEnqueueReadBuffer(usedCommandQueue, memC, CL_TRUE, 0,
				ldc * m * sizeof(float), c, 0, NULL, NULL);
	}
	ERROR_HANDLER(ret);
	printMatrixS(order, m, n, c, ldc);

	status = opencl_success;

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
	cl_int ret;
	OpenCLStatus status = opencl_failure;

	cl_device_id usedDevice = deviceIds[1][0];

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

	const size_t sizes[] =
	{ strlen(definitions), strlen(oclDoubleMatrix), strlen(oclGetMatrixDouble),
			strlen(oclSetMatrixDouble), strlen(oclDGEMM) };
	const char *sources[] =
	{ definitions, oclFloatMatrix, oclGetMatrixFloat, oclSetMatrixFloat,
			oclDGEMM };
	cl_program program = clCreateProgramWithSource(usedContext, 5, sources,
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

	cl_kernel kernel = clCreateKernel(program, "dgemm", &ret);
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
		memC = clCreateBuffer(usedContext,
				CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
				ldc * n * sizeof(float), c, &ret);
	}
	else
	{
		memC = clCreateBuffer(usedContext, CL_MEM_WRITE_ONLY,
				ldc * n * sizeof(float), NULL, &ret);
	}
	ERROR_HANDLER(ret);

	/* Set OpenCL Kernel Arguments */
	int colMajor = order == ColumnMajor ? 1 : 0;
	int transa = transposeA == NO ? 0 : 1;
	int transb = transposeB == NO ? 0 : 1;
	unsigned int submatrixSize = SUBMATRIX_SIZE;
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
	ERROR_HANDLER(clSetKernelArg(kernel, 14, sizeof(unsigned int), &submatrixSize));
	ERROR_HANDLER(clSetKernelArg(kernel, 15, sizeof(cl_double) * SUBMATRIX_SIZE * SUBMATRIX_SIZE, NULL));
	ERROR_HANDLER(clSetKernelArg(kernel, 16, sizeof(cl_double) * SUBMATRIX_SIZE * SUBMATRIX_SIZE, NULL));

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
	if (order == ColumnMajor)
	{
		ret = clEnqueueReadBuffer(usedCommandQueue, memC, CL_TRUE, 0,
				ldc * n * sizeof(float), c, 0, NULL, NULL);
	}
	else
	{
		ret = clEnqueueReadBuffer(usedCommandQueue, memC, CL_TRUE, 0,
				ldc * n * sizeof(float), c, 0, NULL, NULL);
	}
	ERROR_HANDLER(ret);

	status = opencl_success;

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

OpenCLStatus opencl_cgemm(const OCLBMatrixOrder order,
		const OCLBTranspose transposeA, const OCLBTranspose transposeB,
		const int m, const int n, const int k, const void *alpha, void *a,
		const int lda, void *b, const int ldb, const void *beta, void *c,
		const int ldc)
{
	return opencl_not_implemented;
}

OpenCLStatus opencl_zgemm(const OCLBMatrixOrder order,
		const OCLBTranspose transposeA, const OCLBTranspose transposeB,
		const int m, const int n, const int k, const void *alpha, void *a,
		const int lda, void *b, const int ldb, const void *beta, void *c,
		const int ldc)
{
#if OCL_DOUBLE_SUPPORTED == 1
	return opencl_not_implemented;
#else
	return opencl_architecture_mismatch;
#endif
}
