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
