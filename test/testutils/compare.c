/*
 * compare.cpp
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

#include "compare.h"

float absS(float f)
{
	if (f < 0.0)
	{
		return -f;
	}
	return f;
}

double absD(double d)
{
	if (d < 0.0)
	{
		return -d;
	}
	return d;
}

int compareMatrixS(const MatrixOrder order, const int m, const int n, float *a,
		const int lda, float *b, const int ldb, float accuracy)
{
	for (int _m = 0; _m < m; ++_m)
	{
		for (int _n = 0; _n < n; ++_n)
		{
			float difference;
			if (order == ColumnMajor)
			{
				difference = a[_n * lda + _m] != b[_n * ldb + _m];
			}
			else
			{
				difference = a[_m * lda + _n] != b[_m * ldb + _n];
			}
			if (absD(difference) > accuracy)
			{
				return 1;
			}
		}
	}
	return 0;
}

int compareMatrixD(const MatrixOrder order, const int m, const int n,
		double *a, const int lda, double *b, const int ldb, double accuracy)
{
	for (int _m = 0; _m < m; ++_m)
	{
		for (int _n = 0; _n < n; ++_n)
		{
			double difference;
			if (order == ColumnMajor)
			{
				difference = a[_n * lda + _m] != b[_n * ldb + _m];
			}
			else
			{
				difference = a[_m * lda + _n] != b[_m * ldb + _n];
			}
			if (absD(difference) > accuracy)
			{
				return 1;
			}
		}
	}
	return 0;
}
