/*
 * TrimpDgemm.h
 *
 *  Created on: Apr 15, 2011
 *      Author: ludwig
 */

#ifndef TRIMPDGEMM_H
#define TRIMPDGEMM_H

#include <stdlib.h>

#include <uplabase/output.h>
#include <uplabase/compare.h>

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
