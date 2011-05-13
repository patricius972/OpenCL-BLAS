#include "trimp_dgemm.h"

int main(int args, char **argv)
{
	if (testDgemmColMajorNoTransNoTrans_3x3() != 0)
		return 1;

	if (testDgemmColMajorTransNoTrans_3x3() != 0)
		return 1;

	if (testDgemmColMajorTransNoTrans_3x3_with_lda() != 0)
		return 1;

	if (testDgemmColMajorTransNoTrans_2x3_with_lda() != 0)
		return 1;

	if (testDgemmColMajorTransNoTrans_2x3_with_lda_RowMajor() != 0)
		return 1;

	return 0;
}
