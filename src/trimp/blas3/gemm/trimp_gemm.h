/*
 * trimp_blas3_gemm.h
 *
 *  Created on: Apr 15, 2011
 *      Author: ludwig
 */

/*
 Copyright 2011 PureSol Technologies

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#ifndef TRIMP_GEMM_H_
#define TRIMP_GEMM_H_

#include <opencl/opencl_types.h>

OpenCLStatus
trimp_sgemm(const MatrixOrder order, TransposeMatrix transposeA,
		TransposeMatrix transposeB, const int m, const int n, const int k,
		const float alpha, const float *a, const int lda, const float *b,
		const int ldb, const float beta, float *c, const int ldc);

OpenCLStatus
trimp_dgemm(const MatrixOrder order, TransposeMatrix transposeA,
		TransposeMatrix transposeB, const int m, const int n, const int k,
		const double alpha, const double *a, const int lda, const double *b,
		const int ldb, const double beta, double *c, const int ldc);

OpenCLStatus
trimp_cgemm(const MatrixOrder order, TransposeMatrix transposeA,
		TransposeMatrix transposeB, const int m, const int n, const int k,
		const void *alpha, const void *a, const int lda, const void *b,
		const int ldb, const void *beta, void *c, const int ldc);

OpenCLStatus
trimp_zgemm(const MatrixOrder order, TransposeMatrix transposeA,
		TransposeMatrix transposeB, const int m, const int n, const int k,
		const void *alpha, const void *a, const int lda, const void *b,
		const int ldb, const void *beta, void *c, const int ldc);

#endif /* CUBLAS_BLAS3_GEMM_H_ */
