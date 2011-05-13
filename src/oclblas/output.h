/*
 * output.h
 *
 *  Created on: Apr 15, 2011
 *      Author: ludwig
 */

#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>

#include <oclblas/types.h>

void
printMatrixS(const OCLBMatrixOrder order, const int m, const int n, float *a,
		const int lda);

void
printMatrixD(const OCLBMatrixOrder order, const int m, const int n, double *a,
		const int lda);

#endif
