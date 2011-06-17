/*
 * opencl_test.c
 *
 *  Created on: Apr 25, 2011
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

#include <opencl/opencl_utils.h>
#include <opencl/opencl.h>

int main(int argc, char **argv)
{
	char str[64];
	getErrorMessage(CL_OUT_OF_HOST_MEMORY, 64, str);
	/*	printf("%s --> %s\n", "out of host memory", str);*/
	if (strncmp(str, "out of host memory", 64) != 0)
	{
		//free(str);
		return 1;
	}
	//free(str);
	return 0;
}
