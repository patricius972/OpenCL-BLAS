#include <oclblas/oclblas.h>

#include <testutils/oclkerneltest.h>

#include <oclblas/kernels/FloatMatrix.ocl>
#include <oclblas/kernels/GetMatrixFloat.ocl>

void testColumnMajorUntransposed()
{
	float testData[12];
	testData[0] = 1;
	testData[1] = 2;
	testData[2] = 3;
	testData[3] = 0;
	testData[4] = 4;
	testData[5] = 5;
	testData[6] = 6;
	testData[7] = 0;
	testData[8] = 0;
	testData[9] = 0;
	testData[10] = 0;
	testData[11] = 0;
	FloatMatrix matrix =
	{ 3, 2, 1, 0, 4, testData };

	check(1, getMatrixFloat(matrix, 0, 0));
	check(2, getMatrixFloat(matrix, 1, 0));
	check(3, getMatrixFloat(matrix, 2, 0));
	check(0, getMatrixFloat(matrix, 3, 0));
	check(0, getMatrixFloat(matrix, 4, 0));
	check(4, getMatrixFloat(matrix, 0, 1));
	check(5, getMatrixFloat(matrix, 1, 1));
	check(6, getMatrixFloat(matrix, 2, 1));
	check(0, getMatrixFloat(matrix, 3, 1));
	check(0, getMatrixFloat(matrix, 4, 1));
	check(0, getMatrixFloat(matrix, 0, 2));
}

void testColumnMajorTransposed()
{
	float testData[12];
	testData[0] = 1;
	testData[1] = 2;
	testData[2] = 3;
	testData[3] = 0;
	testData[4] = 4;
	testData[5] = 5;
	testData[6] = 6;
	testData[7] = 0;
	testData[8] = 0;
	testData[9] = 0;
	testData[10] = 0;
	testData[11] = 0;
	FloatMatrix matrix =
	{ 2, 3, 1, 1, 4, testData };

	check(1, getMatrixFloat(matrix, 0, 0));
	check(4, getMatrixFloat(matrix, 1, 0));
	check(0, getMatrixFloat(matrix, 2, 0));
	check(2, getMatrixFloat(matrix, 0, 1));
	check(5, getMatrixFloat(matrix, 1, 1));
	check(0, getMatrixFloat(matrix, 2, 1));
	check(3, getMatrixFloat(matrix, 0, 2));
	check(6, getMatrixFloat(matrix, 1, 2));
	check(0, getMatrixFloat(matrix, 2, 2));
	check(0, getMatrixFloat(matrix, 0, 3));
	check(0, getMatrixFloat(matrix, 1, 3));
}

void testRowMajorUntransposed()
{
	float testData[12];
	testData[0] = 1;
	testData[1] = 4;
	testData[2] = 0;
	testData[3] = 2;
	testData[4] = 5;
	testData[5] = 0;
	testData[6] = 3;
	testData[7] = 6;
	testData[8] = 0;
	testData[9] = 0;
	testData[10] = 0;
	testData[11] = 0;
	FloatMatrix matrix =
	{ 3, 2, 0, 0, 3, testData };

	check(1, getMatrixFloat(matrix, 0, 0));
	check(2, getMatrixFloat(matrix, 1, 0));
	check(3, getMatrixFloat(matrix, 2, 0));
	check(0, getMatrixFloat(matrix, 3, 0));
	check(0, getMatrixFloat(matrix, 4, 0));
	check(4, getMatrixFloat(matrix, 0, 1));
	check(5, getMatrixFloat(matrix, 1, 1));
	check(6, getMatrixFloat(matrix, 2, 1));
	check(0, getMatrixFloat(matrix, 3, 1));
	check(0, getMatrixFloat(matrix, 4, 1));
	check(0, getMatrixFloat(matrix, 0, 2));
}

void testRowMajorTransposed()
{
	float testData[12];
	testData[0] = 1;
	testData[1] = 2;
	testData[2] = 3;
	testData[3] = 0;
	testData[4] = 4;
	testData[5] = 5;
	testData[6] = 6;
	testData[7] = 0;
	testData[8] = 0;
	testData[9] = 0;
	testData[10] = 0;
	testData[11] = 0;
	FloatMatrix matrix =
	{ 2, 3, 1, 1, 4, testData };

	check(1, getMatrixFloat(matrix, 0, 0));
	check(4, getMatrixFloat(matrix, 1, 0));
	check(0, getMatrixFloat(matrix, 2, 0));
	check(2, getMatrixFloat(matrix, 0, 1));
	check(5, getMatrixFloat(matrix, 1, 1));
	check(0, getMatrixFloat(matrix, 2, 1));
	check(3, getMatrixFloat(matrix, 0, 2));
	check(6, getMatrixFloat(matrix, 1, 2));
	check(0, getMatrixFloat(matrix, 2, 2));
	check(0, getMatrixFloat(matrix, 0, 3));
	check(0, getMatrixFloat(matrix, 1, 3));
}

int main(int args, char **argv)
{
	testColumnMajorUntransposed();
	testColumnMajorTransposed();
	testRowMajorUntransposed();
	testRowMajorTransposed();
	return 0;
}
