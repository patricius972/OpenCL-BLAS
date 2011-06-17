/*
 * compare.h
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

#ifndef COMPARE_H
#define COMPARE_H

#include <opencl/opencl.h>

#include <math.h>

int
compareMatrixS(const MatrixOrder order, const int m, const int n, float *a,
		const int lda, float *b, const int ldb, float accuracy);

int
compareMatrixD(const MatrixOrder order, const int m, const int n, double *a,
		const int lda, double *b, const int ldb, double accuracy);

#endif
