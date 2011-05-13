/*
 * trimp_blas3_gemm.h
 *
 *  Created on: Apr 15, 2011
 *      Author: ludwig
 */

#ifndef TRIMP_BLAS3_GEMM_H_
#define TRIMP_BLAS3_GEMM_H_

#include <uplabase/types.h>

UplaStatus
trimp_sgemm(const MatrixOrder order, Transpose transposeA,
		Transpose transposeB, const int m, const int n, const int k,
		const float alpha, const float *a, const int lda, const float *b,
		const int ldb, const float beta, float *c, const int ldc);

UplaStatus
trimp_dgemm(const MatrixOrder order, Transpose transposeA,
		Transpose transposeB, const int m, const int n, const int k,
		const double alpha, const double *a, const int lda, const double *b,
		const int ldb, const double beta, double *c, const int ldc);

UplaStatus
trimp_cgemm(const MatrixOrder order, Transpose transposeA,
		Transpose transposeB, const int m, const int n, const int k,
		const void *alpha, const void *a, const int lda, const void *b,
		const int ldb, const void *beta, void *c, const int ldc);

UplaStatus
trimp_zgemm(const MatrixOrder order, Transpose transposeA,
		Transpose transposeB, const int m, const int n, const int k,
		const void *alpha, const void *a, const int lda, const void *b,
		const int ldb, const void *beta, void *c, const int ldc);

#endif /* CUBLAS_BLAS3_GEMM_H_ */
