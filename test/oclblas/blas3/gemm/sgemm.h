/*
 * TrimpDgemm.h
 *
 *  Created on: Apr 15, 2011
 *      Author: ludwig
 */

#ifndef CUBLAS_SGEMM_H
#define CUBLAS_SGEMM_H

#include <stdlib.h>

#include <uplabase/output.h>
#include <uplabase/compare.h>

#include <trimp/trimp_blas.h>
#include <oclblas/oclblas.h>

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
