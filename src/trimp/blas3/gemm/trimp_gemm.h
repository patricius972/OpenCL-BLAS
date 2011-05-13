/*
 * trimp_blas3_gemm.h
 *
 *  Created on: Apr 15, 2011
 *      Author: ludwig
 */

#ifndef TRIMP_GEMM_H_
#define TRIMP_GEMM_H_

#include <opencl/opencl_types.h>
#include <oclblas/types.h>

OpenCLStatus
trimp_sgemm(const OCLBMatrixOrder order, OCLBTranspose transposeA,
		OCLBTranspose transposeB, const int m, const int n, const int k,
		const float alpha, const float *a, const int lda, const float *b,
		const int ldb, const float beta, float *c, const int ldc);

OpenCLStatus
trimp_dgemm(const OCLBMatrixOrder order, OCLBTranspose transposeA,
		OCLBTranspose transposeB, const int m, const int n, const int k,
		const double alpha, const double *a, const int lda, const double *b,
		const int ldb, const double beta, double *c, const int ldc);

OpenCLStatus
trimp_cgemm(const OCLBMatrixOrder order, OCLBTranspose transposeA,
		OCLBTranspose transposeB, const int m, const int n, const int k,
		const void *alpha, const void *a, const int lda, const void *b,
		const int ldb, const void *beta, void *c, const int ldc);

OpenCLStatus
trimp_zgemm(const OCLBMatrixOrder order, OCLBTranspose transposeA,
		OCLBTranspose transposeB, const int m, const int n, const int k,
		const void *alpha, const void *a, const int lda, const void *b,
		const int ldb, const void *beta, void *c, const int ldc);

#endif /* CUBLAS_BLAS3_GEMM_H_ */
