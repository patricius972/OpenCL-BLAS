/*
 * compare.h
 *
 *  Created on: Apr 15, 2011
 *      Author: ludwig
 */

#ifndef COMPARE_H
#define COMPARE_H

#include <math.h>

#include "types.h"

int
compareMatrixS(const MatrixOrder order, const int m, const int n, float *a,
		const int lda, float *b, const int ldb, float accuracy);

int
compareMatrixD(const MatrixOrder order, const int m, const int n, double *a,
		const int lda, double *b, const int ldb, double accuracy);

#endif
