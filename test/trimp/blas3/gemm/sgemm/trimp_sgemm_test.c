#include "trimp_sgemm.h"

int main(int args, char **argv)
{
	if (testSgemmColMajorNoTransNoTrans_3x3() != 0)
		return 1;

	if (testSgemmColMajorTransNoTrans_3x3() != 0)
		return 1;

	if (testSgemmColMajorTransNoTrans_3x3_with_lda() != 0)
		return 1;

	if (testSgemmColMajorTransNoTrans_2x3_with_lda() != 0)
		return 1;

	if (testSgemmColMajorTransNoTrans_2x3_with_lda_RowMajor() != 0)
		return 1;

	return 0;
}
