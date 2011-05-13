#include <oclblas/oclblas.h>

#include "dgemm.h"

int main(int args, char **argv)
{
	if (opencl_initPlatform() != SUCCESS)
	{
		printf("Could not initialize platform!");
		return 1;
	}

	if (testDgemmColMajorNoTransNoTrans_3x3() != 0)
	{
		opencl_dropPlatform();
		return 1;
	}

	if (testDgemmColMajorTransNoTrans_3x3() != 0)
	{
		opencl_dropPlatform();
		return 1;
	}

	if (testDgemmColMajorTransNoTrans_3x3_with_lda() != 0)
	{
		opencl_dropPlatform();
		return 1;
	}

	if (testDgemmColMajorTransNoTrans_2x3_with_lda() != 0)
	{
		opencl_dropPlatform();
		return 1;
	}

	if (testDgemmColMajorTransNoTrans_2x3_with_lda_RowMajor() != 0)
	{
		opencl_dropPlatform();
		return 1;
	}

	opencl_dropPlatform();

	return 0;
}
