/*
 * TrimpDgemm.h
 *
 *  Created on: Apr 15, 2011
 *      Author: ludwig
 */

#ifndef CUBLAS_SGEMM_H
#define CUBLAS_SGEMM_H

#include <stdlib.h>

#include <trimp/trimp_blas.h>

#include <oclblas/oclblas.h>
#include <oclblas/output.h>

#include <testutils/compare.h>

int
testSgemmColMajorNoTransNoTrans_3x3();

int
testSgemmColMajorTransNoTrans_3x3();

int
testSgemmColMajorTransNoTrans_3x3_with_lda();

int
testSgemmColMajorTransNoTrans_2x3_with_lda();

int
testSgemmColMajorTransNoTrans_2x3_with_lda_RowMajor();

#endif
