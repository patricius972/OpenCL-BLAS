/*
 * sgemm_kernel_test.c
 *
 *  Created on: Jun 13, 2011
 *      Author: ludwig
 */

#include <ocltest/ocltest.h>

#define SUBMATRIX_SIZE 8

#include <oclblas/kernels/FloatMatrix.ocl>
#include <oclblas/kernels/GetMatrixFloat.ocl>
#include <oclblas/kernels/SetMatrixFloat.ocl>
#include <oclblas/blas3/gemm/kernels/SGEMM.ocl>

#include <oclblas/output.h>

int colMajor;
int transa;
int transb;
unsigned int m;
unsigned int n;
unsigned int k;
float alpha;
float* a;
int lda;
float* b;
int ldb;
float beta;
float* c;
int ldc;
float *bufferA;
float *bufferB;

void kernelCall()
{
	sgemm(colMajor, transa, transb, m, n, k, alpha, a, lda, b, ldb, beta, c,
			ldc, SUBMATRIX_SIZE, bufferA, bufferB);
}

int main(int args, char **argv)
{
	ocltest_init();

	colMajor = 1;
	transa = 0;
	transb = 0;
	m = 3;
	n = 3;
	k = 3;
	alpha = 1.0;
	a = malloc(m * k * sizeof(float));
	lda = 3;
	b = malloc(k * n * sizeof(float));
	ldb = 3;
	beta = 0.0;
	c = malloc(m * n * sizeof(float));
	ldc = 3;
	bufferA = malloc(SUBMATRIX_SIZE * SUBMATRIX_SIZE * sizeof(float));
	bufferB = malloc(SUBMATRIX_SIZE * SUBMATRIX_SIZE * sizeof(float));

	a[0] = 1.0;
	a[1] = 2.0;
	a[2] = 3.0;
	a[3] = 4.0;
	a[4] = 5.0;
	a[5] = 6.0;
	a[6] = 7.0;
	a[7] = 8.0;
	a[8] = 9.0;

	b[0] = 1.0;
	b[1] = 2.0;
	b[2] = 3.0;
	b[3] = 4.0;
	b[4] = 5.0;
	b[5] = 6.0;
	b[6] = 7.0;
	b[7] = 8.0;
	b[8] = 9.0;

	c[0] = 1.0;
	c[1] = 2.0;
	c[2] = 3.0;
	c[3] = 4.0;
	c[4] = 5.0;
	c[5] = 6.0;
	c[6] = 7.0;
	c[7] = 8.0;
	c[8] = 9.0;

	unsigned int globalSizes[] =
	{ SUBMATRIX_SIZE, SUBMATRIX_SIZE };
	unsigned int localSizes[] =
	{ SUBMATRIX_SIZE, SUBMATRIX_SIZE };
	ocltest_runKernel(kernelCall, 2, globalSizes, localSizes);

	printMatrixS(colMajor, m, n, c, 3);

	free(a);
	free(b);
	free(c);
	free(bufferA);
	free(bufferB);

	ocltest_drop();
}
