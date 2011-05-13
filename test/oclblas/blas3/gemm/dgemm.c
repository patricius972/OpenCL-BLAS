/*
 * TrimpDgemm.c
 *
 *  Created on: Apr 15, 2011
 *      Author: ludwig
 */

#include "dgemm.h"

int testDgemmColMajorNoTransNoTrans_3x3()
{
	/*
	 * Performs:
	 *
	 * / 1 4 7 \   / 1 4 7 \   / 30 66 102 \
   * | 2 5 8 | * | 2 5 8 | = | 36 81 126 |
	 * \ 3 6 9 /   \ 3 6 9 /   \ 42 96 150 /
	 */

	double *a = malloc(9 * sizeof(double));
	double *b = malloc(9 * sizeof(double));
	double *c = malloc(9 * sizeof(double));
	double *e = malloc(9 * sizeof(double));

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

	trimp_dgemm(ColumnMajor, NO, NO, 3, 3, 3, 1.0, a, 3, b, 3, 0.0, e, 3);

	printf("TEST: testDgemmColMajorNoTransNoTrans_3x3()\n");
	printf("A =\n");
	printMatrixD(ColumnMajor, 3, 3, a, 3);
	printf("B =\n");
	printMatrixD(ColumnMajor, 3, 3, b, 3);

	printf("C = A * B =\n");
	printf("(Expected)\n");
	printMatrixD(ColumnMajor, 3, 3, e, 3);

	opencl_dgemm(ColumnMajor, NO, NO, 3, 3, 3, 1.0, a, 3, b, 3, 0.0, c, 3);

	printf("(Actual)\n");
	printMatrixD(ColumnMajor, 3, 3, c, 3);

	int result = compareMatrixD(ColumnMajor, 3, 3, c, 3, e, 3, 1e-9);

	free(a);
	free(b);
	free(c);
	free(e);
	return result;
}

int testDgemmColMajorTransNoTrans_3x3()
{
	/*
	 * Performs:
	 *
	 * / 1 4 7 \ T   / 1 4 7 \   / 14  32  50 \
   * | 2 5 8 |   * | 2 5 8 | = | 32  77 122 |
	 * \ 3 6 9 /     \ 3 6 9 /   \ 50 122 194 /
	 */

	double *a = malloc(9 * sizeof(double));
	double *b = malloc(9 * sizeof(double));
	double *c = malloc(9 * sizeof(double));
	double *e = malloc(9 * sizeof(double));

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

	trimp_dgemm(ColumnMajor, YES, NO, 3, 3, 3, 1.0, a, 3, b, 3, 0.0, e, 3);

	printf("TEST: testDgemmColMajorTransNoTrans_3x3()\n");
	printf("A =\n");
	printMatrixD(ColumnMajor, 3, 3, a, 3);
	printf("B =\n");
	printMatrixD(ColumnMajor, 3, 3, b, 3);

	printf("C = transposed(A) * B =\n");
	printf("(Expected)\n");
	printMatrixD(ColumnMajor, 3, 3, e, 3);

	opencl_dgemm(ColumnMajor, YES, NO, 3, 3, 3, 1.0, a, 3, b, 3, 0.0, c, 3);

	printf("(Actual)\n");
	printMatrixD(ColumnMajor, 3, 3, c, 3);

	int result = compareMatrixD(ColumnMajor, 3, 3, c, 3, e, 3, 1e-9);

	free(a);
	free(b);
	free(c);
	free(e);
	return result;
}

int testDgemmColMajorTransNoTrans_3x3_with_lda()
{
	/*
	 * Performs:
	 *
	 * / 1 4 7 \ T   / 1 4 7 \   / 14  32  50 \
   * | 2 5 8 |   * | 2 5 8 | = | 32  77 122 |
	 * \ 3 6 9 /     \ 3 6 9 /   \ 50 122 194 /
	 */

	double *a = malloc(16 * sizeof(double));
	double *b = malloc(16 * sizeof(double));
	double *c = malloc(16 * sizeof(double));
	double *e = malloc(9 * sizeof(double));

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

	trimp_dgemm(ColumnMajor, YES, NO, 3, 3, 3, 1.0, a, 4, b, 4, 0.0, e, 3);

	printf("TEST: testDgemmColMajorTransNoTrans_3x3_with_lda()\n");
	printf("A =\n");
	printMatrixD(ColumnMajor, 3, 3, a, 4);
	printf("B =\n");
	printMatrixD(ColumnMajor, 3, 3, b, 4);

	printf("C = transposed(A) * B =\n");
	printf("(Expected)\n");
	printMatrixD(ColumnMajor, 3, 3, e, 3);

	opencl_dgemm(ColumnMajor, YES, NO, 3, 3, 3, 1.0, a, 4, b, 4, 0.0, c, 4);

	printf("(Actual)\n");
	printMatrixD(ColumnMajor, 3, 3, c, 4);

	int result = compareMatrixD(ColumnMajor, 3, 3, c, 4, e, 3, 1e-9);

	free(a);
	free(b);
	free(c);
	free(e);
	return result;
}

int testDgemmColMajorTransNoTrans_2x3_with_lda()
{
	/*
	 * Performs:
	 *
	 * / 1 4 \ T   / 1 4 \   / 14  32 \
   * | 2 5 |   * | 2 5 | = \ 32  77 /
	 * \ 3 6 /     \ 3 6 /
	 */

	double *a = malloc(8 * sizeof(double));
	double *b = malloc(6 * sizeof(double));
	double *c = malloc(4 * sizeof(double));
	double *e = malloc(4 * sizeof(double));

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

	trimp_dgemm(ColumnMajor, YES, NO, 2, 2, 3, 1.0, a, 4, b, 3, 0.0, e, 2);

	printf("TEST: testDgemmColMajorTransNoTrans_2x3_with_lda()\n");
	printf("A =\n");
	printMatrixD(ColumnMajor, 3, 2, a, 4);
	printf("B =\n");
	printMatrixD(ColumnMajor, 3, 2, b, 3);

	printf("C = transposed(A) * B =\n");
	printf("(Expected)\n");
	printMatrixD(ColumnMajor, 2, 2, e, 2);

	opencl_dgemm(ColumnMajor, YES, NO, 2, 2, 3, 1.0, a, 4, b, 3, 0.0, c, 2);

	printf("(Actual)\n");
	printMatrixD(ColumnMajor, 2, 2, c, 2);

	int result = compareMatrixD(ColumnMajor, 2, 2, c, 2, e, 2, 1e-9);

	free(a);
	free(b);
	free(c);
	free(e);
	return result;
}

int testDgemmColMajorTransNoTrans_2x3_with_lda_RowMajor()
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

	double *a = malloc(9 * sizeof(double));
	double *b = malloc(6 * sizeof(double));
	double *c = malloc(4 * sizeof(double));
	double *e = malloc(4 * sizeof(double));

	a[0] = 1.0;
	a[1] = 4.0;
	a[2] = 0.0;
	a[3] = 2.0;
	a[4] = 5.0;
	a[5] = 0.0;
	a[6] = 3.0;
	a[7] = 6.0;
	a[8] = 0.0;

	b[0] = 1.0;
	b[1] = 2.0;
	b[2] = 3.0;
	b[3] = 4.0;
	b[4] = 5.0;
	b[5] = 6.0;

	trimp_dgemm(RowMajor, YES, NO, 2, 2, 3, 1.0, a, 3, b, 2, 0.0, e, 2);

	printf("TEST: testDgemmColMajorTransNoTrans_2x3_with_lda_RowMajor()\n");
	printf("A =\n");
	printMatrixD(RowMajor, 3, 2, a, 3);
	printf("B =\n");
	printMatrixD(RowMajor, 3, 2, b, 2);

	printf("C = transposed(A) * B =\n");
	printf("(Expected)\n");
	printMatrixD(RowMajor, 2, 2, e, 2);

	opencl_dgemm(RowMajor, YES, NO, 2, 2, 3, 1.0, a, 3, b, 2, 0.0, c, 2);

	printf("(Actual)\n");
	printMatrixD(RowMajor, 2, 2, c, 2);

	int result = compareMatrixD(RowMajor, 2, 2, c, 2, e, 2, 1e-9);

	free(a);
	free(b);
	free(c);
	free(e);
	return result;
}
