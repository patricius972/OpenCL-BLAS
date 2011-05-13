/*
 * TrimpDgemm.h
 *
 *  Created on: Apr 15, 2011
 *      Author: ludwig
 */

#ifndef TRIMPSGEMM_H
#define TRIMPSGEMM_H

#include <stdlib.h>

#include <oclblas/output.h>
#include <oclblas/types.h>

#include <testutils/compare.h>

#include <trimp/trimpblas.h>

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
