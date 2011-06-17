/*
 * ocltest_test.c
 *
 *  Created on: Jun 13, 2011
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

#include <stdlib.h>

#include <ocltest/ocltest.h>

#define GLOBAL_SIZE_1 8
#define GLOBAL_SIZE_2 8

/* int results[GLOBAL_SIZE_1][GLOBAL_SIZE_2]; */
unsigned int counter = 0;

void sampleKernel()
{
	++counter;
	printf("%ix KERNEL! \n", counter);
/*	results[get_global_id(0) * get_local_size(0) + get_local_id(0)][get_global_id(
			1) * get_local_size(1) + get_local_id(1)];*/
}

int main(int argc, char **argv)
{
	if (ocltest_isInitialized())
	{
		return 1;
	}
	ocltest_init();
	if (!ocltest_isInitialized())
	{
		return 1;
	}
	unsigned int numDimensions = 2;
	unsigned int globalSizes[] =
	{ 8, 8 };
	unsigned int localSizes[] =
	{ 4, 2 };
	ocltest_runKernel(sampleKernel, numDimensions, globalSizes, localSizes);
	ocltest_drop();
	if (ocltest_isInitialized())
	{
		return 1;
	}
	if (counter != 64)
	{
		return 1;
	}
	return 0;
}
