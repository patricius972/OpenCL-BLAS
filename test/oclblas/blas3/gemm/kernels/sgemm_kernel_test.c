/*
 * sgemm_kernel_test.c
 *
 *  Created on: Jun 13, 2011
 *      Author: ludwig
 */

#include <ocltest/ocltest.h>
#include <oclblas/output.h>
#include <testutils/compare.h>

#include <trimp/trimpblas.h>

#define SUBMATRIX_SIZE 16

#include <oclblas/kernels/FloatMatrix.ocl>
#include <oclblas/kernels/GetMatrixFloat.ocl>
#include <oclblas/kernels/SetMatrixFloat.ocl>
#include <oclblas/blas3/gemm/kernels/SGEMM.ocl>

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
float* e; /* for expectation */

void kernelCallback()
{
	sgemm(colMajor, transa, transb, m, n, k, alpha, a, lda, b, ldb, beta, c,
			ldc, SUBMATRIX_SIZE, bufferA, bufferB);
}

int testSgemmColMajorNoTransNoTrans_3x3()
{
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
	e = malloc(9 * sizeof(float));

	/*
	 * Performs:
	 *
	 * / 1 4 7 \   / 1 4 7 \   / 30 66 102 \
     * | 2 5 8 | * | 2 5 8 | = | 36 81 126 |
	 * \ 3 6 9 /   \ 3 6 9 /   \ 42 96 150 /
	 */

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

	trimp_sgemm(ColumnMajor, NO, NO, 3, 3, 3, 1.0, a, 3, b, 3, 0.0, e, 3);

	printf("TEST: testDgemmColMajorNoTransNoTrans_3x3()\n");
	printf("A =\n");
	printMatrixS(ColumnMajor, 3, 3, a, 3);
	printf("B =\n");
	printMatrixS(ColumnMajor, 3, 3, b, 3);

	printf("C = A * B =\n");
	printf("(Expected)\n");
	printMatrixS(ColumnMajor, 3, 3, e, 3);

	unsigned int globalSizes[] =
	{ SUBMATRIX_SIZE, SUBMATRIX_SIZE };
	unsigned int localSizes[] =
	{ SUBMATRIX_SIZE, SUBMATRIX_SIZE };

	ocltest_runKernel(kernelCallback, 2, globalSizes, localSizes);

	printf("(Actual)\n");
	printMatrixS(ColumnMajor, 3, 3, c, 3);

	int result = compareMatrixS(ColumnMajor, 3, 3, c, 3, e, 3, 1e-9);

	free(a);
	free(b);
	free(c);
	free(bufferA);
	free(bufferB);
	free(e);

	return result;
}

int testSgemmColMajorTransNoTrans_2x3_with_lda_RowMajor()
{
	colMajor = 0;
	transa = 1;
	transb = 0;
	m = 2;
	n = 2;
	k = 3;
	alpha = 1.0;
	a = malloc(6 * sizeof(float));
	lda = 2;
	b = malloc(6 * sizeof(float));
	ldb = 2;
	beta = 0.0;
	c = malloc(4 * sizeof(float));
	ldc = 2;
	bufferA = malloc(SUBMATRIX_SIZE * SUBMATRIX_SIZE * sizeof(float));
	bufferB = malloc(SUBMATRIX_SIZE * SUBMATRIX_SIZE * sizeof(float));
	e = malloc(4 * sizeof(float));

	/*
	 * Performs:
	 *
	 * / 1 4 \ T   / 1 2 \   / 22 28 \
     * | 2 5 |   * | 3 4 | = \ 49 64 /
	 * \ 3 6 /     \ 5 6 /
	 *
	 * This time the matrices are given row major!
	 */

	a[0] = 1.0;
	a[1] = 4.0;
	a[2] = 2.0;
	a[3] = 5.0;
	a[4] = 3.0;
	a[5] = 6.0;

	b[0] = 1.0;
	b[1] = 2.0;
	b[2] = 3.0;
	b[3] = 4.0;
	b[4] = 5.0;
	b[5] = 6.0;

	trimp_sgemm(RowMajor, YES, NO, 2, 2, 3, 1.0, a, 2, b, 2, 0.0, e, 2);

	printf("TEST: testSgemmColMajorTransNoTrans_2x3_with_lda_RowMajor()\n");
	printf("A =\n");
	printMatrixS(RowMajor, 3, 2, a, 2);
	printf("B =\n");
	printMatrixS(RowMajor, 3, 2, b, 2);

	printf("C = transposed(A) * B =\n");
	printf("(Expected)\n");
	printMatrixS(RowMajor, 2, 2, e, 2);

	unsigned int globalSizes[] =
	{ SUBMATRIX_SIZE, SUBMATRIX_SIZE };
	unsigned int localSizes[] =
	{ SUBMATRIX_SIZE, SUBMATRIX_SIZE };

	ocltest_runKernel(kernelCallback, 2, globalSizes, localSizes);

	printf("(Actual)\n");
	printMatrixS(RowMajor, 2, 2, c, 2);

	int result = compareMatrixS(RowMajor, 2, 2, c, 2, e, 2, 1e-9);

	free(a);
	free(b);
	free(c);
	free(bufferA);
	free(bufferB);
	free(e);

	return result;
}

int main(int args, char **argv)
{
	ocltest_init();

	if (testSgemmColMajorNoTransNoTrans_3x3() != 0)
	{
		ocltest_drop();
		return 1;
	}

	if (testSgemmColMajorTransNoTrans_2x3_with_lda_RowMajor() != 0)
	{
		ocltest_drop();
		return 1;
	}

	ocltest_drop();
	return 0;
}
