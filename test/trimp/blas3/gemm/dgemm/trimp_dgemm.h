/*
 * TrimpDgemm.h
 *
 *  Created on: Apr 15, 2011
 *      Author: ludwig
 */

#ifndef TRIMPDGEMM_H
#define TRIMPDGEMM_H

#include <stdio.h>
#include <stdlib.h>

#include <oclblas/output.h>

#include <testutils/compare.h>

#include <trimp/trimp_blas.h>

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
