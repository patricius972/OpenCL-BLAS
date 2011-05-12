/*
 * opencl_blas3_gemm.h
 *
 *  Created on: Apr 15, 2011
 *      Author: ludwig
 */

#ifndef OPENCL_BLAS3_GEMM_H_
#define OPENCL_BLAS3_GEMM_H_

#include <stdio.h>

#include <time.h>

#include <uplabase/types.h>

/* ATLAS Blas as fallback for double routines on non supporting devices */
#include <atlas/atlas_blas.h>

#include <opencl/opencl.h>

#define opencl_sgemm_effort() n_3
#define opencl_dgemm_effort() n_3
#define opencl_cgemm_effort() n_3
#define opencl_zgemm_effort() n_3

#define opencl_sgemm_problem_size(order, transposeA, transposeB, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc) (double)(m * n * k)
#define opencl_dgemm_problem_size(order, transposeA, transposeB, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc) (double)(m * n * k)
#define opencl_cgemm_problem_size(order, transposeA, transposeB, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc) (double)(m * n * k)
#define opencl_zgemm_problem_size(order, transposeA, transposeB, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc) (double)(m * n * k)

UplaStatus opencl_sgemm(const MatrixOrder order, const Transpose transposeA,
		const Transpose transposeB, const int m, const int n, const int k,
		const float alpha, float *a, const int lda, float *b, const int ldb,
		const float beta, float *c, const int ldc);

UplaStatus opencl_dgemm(const MatrixOrder order, const Transpose transposeA,
		const Transpose transposeB, const int m, const int n, const int k,
		const double alpha, double *a, const int lda, double *b, const int ldb,
		const double beta, double *c, const int ldc);

UplaStatus opencl_cgemm(const MatrixOrder order, const Transpose transposeA,
		const Transpose transposeB, const int m, const int n, const int k,
		const void *alpha, void *a, const int lda, void *b, const int ldb,
		const void *beta, void *c, const int ldc);

UplaStatus opencl_zgemm(const MatrixOrder order, const Transpose transposeA,
		const Transpose transposeB, const int m, const int n, const int k,
		const void *alpha, void *a, const int lda, void *b, const int ldb,
		const void *beta, void *c, const int ldc);

#endif /* CUBLAS_BLAS3_GEMM_H_ */
