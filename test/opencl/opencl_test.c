/*
 * opencl_test.c
 *
 *  Created on: Apr 25, 2011
 *      Author: ludwig
 */

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
