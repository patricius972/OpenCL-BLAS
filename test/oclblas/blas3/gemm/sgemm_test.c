#include <oclblas/oclblas.h>

#include "sgemm.h"

int main(int args, char **argv)
{
	if (opencl_initPlatform() != opencl_success)
	{
		printf("Could not initialize platform!");
		return 1;
	}

	if (testSgemmColMajorNoTransNoTrans_3x3() != 0)
	{
		opencl_dropPlatform();
		return 1;
	}

	if (testSgemmColMajorTransNoTrans_3x3() != 0)
	{
		opencl_dropPlatform();
		return 1;
	}

	if (testSgemmColMajorTransNoTrans_3x3_with_lda() != 0)
	{
		opencl_dropPlatform();
		return 1;
	}

	if (testSgemmColMajorTransNoTrans_2x3_with_lda() != 0)
	{
		opencl_dropPlatform();
		return 1;
	}

	if (testSgemmColMajorTransNoTrans_2x3_with_lda_RowMajor() != 0)
	{
		opencl_dropPlatform();
		return 1;
	}

	opencl_dropPlatform();

	return 0;
}
