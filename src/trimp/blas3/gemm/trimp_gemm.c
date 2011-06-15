/*
 * trimp_blas3_gemm.c
 *
 *  Created on: Apr 15, 2011
 *      Author: ludwig
 */

#include "trimp_gemm.h"

OpenCLStatus trimp_sgemm(const OCLBMatrixOrder order, OCLBTranspose transposeA,
		OCLBTranspose transposeB, const int m, const int n, const int k,
		const float alpha, const float *a, const int lda, const float *b,
		const int ldb, const float beta, float *c, const int ldc)
{
	if (order == RowMajor)
	{
		transposeA = (transposeA == NO ? YES : NO);
		transposeB = (transposeB == NO ? YES : NO);
	}
	for (int _m = 0; _m < m; _m++)
	{
		for (int _n = 0; _n < n; _n++)
		{
			float value = 0.0;
			for (int _k = 0; _k < k; _k++)
			{
				float _a = (transposeA == NO) ? a[_k * lda + _m] : a[_m * lda
						+ _k];
				float _b = (transposeB == NO) ? b[_n * ldb + _k] : b[_k * ldb
						+ _n];
				value += _a * _b;
			}
			if (order == ColumnMajor)
			{
				c[_n * ldc + _m] = value;
			}
			else
			{
				c[_m * ldc + _n] = value;
			}
		}
	}
	return opencl_success;
}

OpenCLStatus trimp_dgemm(const OCLBMatrixOrder order, OCLBTranspose transposeA,
		OCLBTranspose transposeB, const int m, const int n, const int k,
		const double alpha, const double *a, const int lda, const double *b,
		const int ldb, const double beta, double *c, const int ldc)
{
	if (order == RowMajor)
	{
		transposeA = (transposeA == NO ? YES : NO);
		transposeB = (transposeB == NO ? YES : NO);
	}
	for (int _m = 0; _m < m; _m++)
	{
		for (int _n = 0; _n < n; _n++)
		{
			double value = 0.0;
			for (int _k = 0; _k < k; _k++)
			{
				double _a = (transposeA == NO) ? a[_k * lda + _m] : a[_m * lda
						+ _k];
				double _b = (transposeB == NO) ? b[_n * ldb + _k] : b[_k * ldb
						+ _n];
				value += _a * _b;
			}
			if (order == ColumnMajor)
			{
				c[_n * ldc + _m] = value;
			}
			else
			{
				c[_m * ldc + _n] = value;
			}
		}
	}
	return opencl_success;
}

OpenCLStatus trimp_cgemm(const OCLBMatrixOrder order,
		const OCLBTranspose transposeA, const OCLBTranspose transposeB,
		const int m, const int n, const int k, const void *alpha,
		const void *a, const int lda, const void *b, const int ldb,
		const void *beta, void *c, const int ldc)
{
	return opencl_not_implemented;
}

OpenCLStatus trimp_zgemm(const OCLBMatrixOrder order,
		const OCLBTranspose transposeA, const OCLBTranspose transposeB,
		const int m, const int n, const int k, const void *alpha,
		const void *a, const int lda, const void *b, const int ldb,
		const void *beta, void *c, const int ldc)
{
	return opencl_not_implemented;
}
