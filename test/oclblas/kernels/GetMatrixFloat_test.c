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

#include <oclblas/oclblas.h>

#include <ocltest/ocltest.h>

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

	float testData2[6];
	testData2[0] = 1;
	testData2[1] = 2;
	testData2[2] = 3;
	testData2[3] = 4;
	testData2[4] = 5;
	testData2[5] = 6;
	FloatMatrix matrix2 =
	{ 3, 2, 0, 0, 2, testData2 };

	check(1, getMatrixFloat(matrix2, 0, 0));
	check(2, getMatrixFloat(matrix2, 0, 1));
	check(3, getMatrixFloat(matrix2, 1, 0));
	check(4, getMatrixFloat(matrix2, 1, 1));
	check(5, getMatrixFloat(matrix2, 2, 0));
	check(6, getMatrixFloat(matrix2, 2, 1));
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
