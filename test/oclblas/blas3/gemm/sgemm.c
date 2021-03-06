/*
 * TrimpDgemm.c
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

#include "sgemm.h"

int testSgemmColMajorNoTransNoTrans_3x3()
{
	/*
	 * Performs:
	 *
	 * / 1 4 7 \   / 1 4 7 \   / 30 66 102 \
     * | 2 5 8 | * | 2 5 8 | = | 36 81 126 |
	 * \ 3 6 9 /   \ 3 6 9 /   \ 42 96 150 /
	 */

	float *a = malloc(9 * sizeof(float));
	float *b = malloc(9 * sizeof(float));
	float *c = malloc(9 * sizeof(float));
	float *e = malloc(9 * sizeof(float));

	a[0] = 1.0;
	a[1] = 2.0;
	a[2] = 3.0;
	a[3] = 4.0;
	a[4] = 5.0;
	a[5] = 6.0;
	a[6] = 7.0;
	a[7] = 8.0;
	a[8] = 9.0;

	b[0] = 1.0;
	b[1] = 2.0;
	b[2] = 3.0;
	b[3] = 4.0;
	b[4] = 5.0;
	b[5] = 6.0;
	b[6] = 7.0;
	b[7] = 8.0;
	b[8] = 9.0;

	trimp_sgemm(ColumnMajor, NoTranspose, NoTranspose, 3, 3, 3, 1.0, a, 3, b,
			3, 0.0, e, 3);

	printf("TEST: testDgemmColMajorNoTransNoTrans_3x3()\n");
	printf("A =\n");
	printMatrixS(ColumnMajor, 3, 3, a, 3);
	printf("B =\n");
	printMatrixS(ColumnMajor, 3, 3, b, 3);

	printf("C = A * B =\n");
	printf("(Expected)\n");
	printMatrixS(ColumnMajor, 3, 3, e, 3);

	opencl_sgemm(ColumnMajor, NoTranspose, NoTranspose, 3, 3, 3, 1.0, a, 3, b,
			3, 0.0, c, 3);

	printf("(Actual)\n");
	printMatrixS(ColumnMajor, 3, 3, c, 3);

	int result = compareMatrixS(ColumnMajor, 3, 3, c, 3, e, 3, 1e-9);

	free(a);
	free(b);
	free(c);
	free(e);
	return result;
}

int testSgemmColMajorTransNoTrans_3x3()
{
	/*
	 * Performs:
	 *
	 * / 1 4 7 \ T   / 1 4 7 \   / 14  32  50 \
   * | 2 5 8 |   * | 2 5 8 | = | 32  77 122 |
	 * \ 3 6 9 /     \ 3 6 9 /   \ 50 122 194 /
	 */

	float *a = malloc(9 * sizeof(float));
	float *b = malloc(9 * sizeof(float));
	float *c = malloc(9 * sizeof(float));
	float *e = malloc(9 * sizeof(float));

	a[0] = 1.0;
	a[1] = 2.0;
	a[2] = 3.0;
	a[3] = 4.0;
	a[4] = 5.0;
	a[5] = 6.0;
	a[6] = 7.0;
	a[7] = 8.0;
	a[8] = 9.0;

	b[0] = 1.0;
	b[1] = 2.0;
	b[2] = 3.0;
	b[3] = 4.0;
	b[4] = 5.0;
	b[5] = 6.0;
	b[6] = 7.0;
	b[7] = 8.0;
	b[8] = 9.0;

	trimp_sgemm(ColumnMajor, Transpose, NoTranspose, 3, 3, 3, 1.0, a, 3, b, 3,
			0.0, e, 3);

	printf("TEST: testDgemmColMajorTransNoTrans_3x3()\n");
	printf("A =\n");
	printMatrixS(ColumnMajor, 3, 3, a, 3);
	printf("B =\n");
	printMatrixS(ColumnMajor, 3, 3, b, 3);

	printf("C = transposed(A) * B =\n");
	printf("(Expected)\n");
	printMatrixS(ColumnMajor, 3, 3, e, 3);

	opencl_sgemm(ColumnMajor, Transpose, NoTranspose, 3, 3, 3, 1.0, a, 3, b, 3,
			0.0, c, 3);

	printf("(Actual)\n");
	printMatrixS(ColumnMajor, 3, 3, c, 3);

	int result = compareMatrixS(ColumnMajor, 3, 3, c, 3, e, 3, 1e-9);

	free(a);
	free(b);
	free(c);
	free(e);
	return result;
}

int testSgemmColMajorTransNoTrans_3x3_with_lda()
{
	/*
	 * Performs:
	 *
	 * / 1 4 7 \ T   / 1 4 7 \   / 14  32  50 \
   * | 2 5 8 |   * | 2 5 8 | = | 32  77 122 |
	 * \ 3 6 9 /     \ 3 6 9 /   \ 50 122 194 /
	 */

	float *a = malloc(16 * sizeof(float));
	float *b = malloc(16 * sizeof(float));
	float *c = malloc(16 * sizeof(float));
	float *e = malloc(9 * sizeof(float));

	a[0] = 1.0;
	a[1] = 2.0;
	a[2] = 3.0;
	a[3] = 0.0;
	a[4] = 4.0;
	a[5] = 5.0;
	a[6] = 6.0;
	a[7] = 0.0;
	a[8] = 7.0;
	a[9] = 8.0;
	a[10] = 9.0;
	a[11] = 0.0;
	a[12] = 0.0;
	a[13] = 0.0;
	a[14] = 0.0;
	a[15] = 0.0;

	b[0] = 1.0;
	b[1] = 2.0;
	b[2] = 3.0;
	b[3] = 0.0;
	b[4] = 4.0;
	b[5] = 5.0;
	b[6] = 6.0;
	b[7] = 0.0;
	b[8] = 7.0;
	b[9] = 8.0;
	b[10] = 9.0;
	b[11] = 0.0;
	b[12] = 0.0;
	b[13] = 0.0;
	b[14] = 0.0;
	b[15] = 0.0;

	trimp_sgemm(ColumnMajor, Transpose, NoTranspose, 3, 3, 3, 1.0, a, 4, b, 4,
			0.0, e, 3);

	printf("TEST: testSgemmColMajorTransNoTrans_3x3_with_lda()\n");
	printf("A =\n");
	printMatrixS(ColumnMajor, 3, 3, a, 4);
	printf("B =\n");
	printMatrixS(ColumnMajor, 3, 3, b, 4);

	printf("C = transposed(A) * B =\n");
	printf("(Expected)\n");
	printMatrixS(ColumnMajor, 3, 3, e, 3);

	opencl_sgemm(ColumnMajor, Transpose, NoTranspose, 3, 3, 3, 1.0, a, 4, b, 4,
			0.0, c, 4);

	printf("(Actual)\n");
	printMatrixS(ColumnMajor, 3, 3, c, 4);

	int result = compareMatrixS(ColumnMajor, 3, 3, c, 4, e, 3, 1e-9);

	free(a);
	free(b);
	free(c);
	free(e);
	return result;
}

int testSgemmColMajorTransNoTrans_2x3_with_lda()
{
	/*
	 * Performs:
	 *
	 * / 1 4 \ T   / 1 4 \   / 14  32 \
   * | 2 5 |   * | 2 5 | = \ 32  77 /
	 * \ 3 6 /     \ 3 6 /
	 */

	float *a = malloc(8 * sizeof(float));
	float *b = malloc(6 * sizeof(float));
	float *c = malloc(4 * sizeof(float));
	float *e = malloc(4 * sizeof(float));

	a[0] = 1.0;
	a[1] = 2.0;
	a[2] = 3.0;
	a[3] = 0.0;
	a[4] = 4.0;
	a[5] = 5.0;
	a[6] = 6.0;
	a[7] = 0.0;

	b[0] = 1.0;
	b[1] = 2.0;
	b[2] = 3.0;
	b[3] = 4.0;
	b[4] = 5.0;
	b[5] = 6.0;

	trimp_sgemm(ColumnMajor, Transpose, NoTranspose, 2, 2, 3, 1.0, a, 4, b, 3,
			0.0, e, 2);

	printf("TEST: testSgemmColMajorTransNoTrans_2x3_with_lda()\n");
	printf("A =\n");
	printMatrixS(ColumnMajor, 3, 2, a, 4);
	printf("B =\n");
	printMatrixS(ColumnMajor, 3, 2, b, 3);

	printf("C = transposed(A) * B =\n");
	printf("(Expected)\n");
	printMatrixS(ColumnMajor, 2, 2, e, 2);

	opencl_sgemm(ColumnMajor, Transpose, NoTranspose, 2, 2, 3, 1.0, a, 4, b, 3,
			0.0, c, 2);

	printf("(Actual)\n");
	printMatrixS(ColumnMajor, 2, 2, c, 2);

	int result = compareMatrixS(ColumnMajor, 2, 2, c, 2, e, 2, 1e-9);

	free(a);
	free(b);
	free(c);
	free(e);
	return result;
}

int testSgemmColMajorTransNoTrans_2x3_with_lda_RowMajor()
{
	/*
	 * Performs:
	 *
	 * / 1 4 \ T   / 1 2 \   / 22 28 \
     * | 2 5 |   * | 3 4 | = \ 49 64 /
	 * \ 3 6 /     \ 5 6 /
	 *
	 * This time the matrices are given row major!
	 */

	float *a = malloc(6 * sizeof(float));
	float *b = malloc(6 * sizeof(float));
	float *c = malloc(4 * sizeof(float));
	float *e = malloc(4 * sizeof(float));

	a[0] = 1.0;
	a[1] = 4.0;
	a[2] = 2.0;
	a[3] = 5.0;
	a[4] = 3.0;
	a[5] = 6.0;

	b[0] = 1.0;
	b[1] = 2.0;
	b[2] = 3.0;
	b[3] = 4.0;
	b[4] = 5.0;
	b[5] = 6.0;

	trimp_sgemm(RowMajor, Transpose, NoTranspose, 2, 2, 3, 1.0, a, 2, b, 2,
			0.0, e, 2);

	printf("TEST: testSgemmColMajorTransNoTrans_2x3_with_lda_RowMajor()\n");
	printf("A =\n");
	printMatrixS(RowMajor, 3, 2, a, 2);
	printf("B =\n");
	printMatrixS(RowMajor, 3, 2, b, 2);

	printf("C = transposed(A) * B =\n");
	printf("(Expected)\n");
	printMatrixS(RowMajor, 2, 2, e, 2);

	opencl_sgemm(RowMajor, Transpose, NoTranspose, 2, 2, 3, 1.0, a, 2, b, 2,
			0.0, c, 2);

	printf("(Actual)\n");
	printMatrixS(RowMajor, 2, 2, c, 2);

	int result = compareMatrixS(RowMajor, 2, 2, c, 2, e, 2, 1e-9);

	free(a);
	free(b);
	free(c);
	free(e);
	return result;
}
