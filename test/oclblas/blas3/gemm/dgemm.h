/*
 * TrimpDgemm.h
 *
 *  Created on: Apr 15, 2011
 *      Author: ludwig
 */

#ifndef CUBLAS_DGEMM_H
#define CUBLAS_DGEMM_H

#include <stdlib.h>

#include <trimp/trimpblas.h>

#include <oclblas/oclblas.h>
#include <oclblas/output.h>

#include <testutils/compare.h>

int
testDgemmColMajorNoTransNoTrans_3x3();

int
testDgemmColMajorTransNoTrans_3x3();

int
testDgemmColMajorTransNoTrans_3x3_with_lda();

int
testDgemmColMajorTransNoTrans_2x3_with_lda();

int
testDgemmColMajorTransNoTrans_2x3_with_lda_RowMajor();

#endif
