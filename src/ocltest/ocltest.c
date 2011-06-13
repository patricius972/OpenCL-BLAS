/*
 * ocltest.c
 *
 *  Created on: Jun 13, 2011
 *      Author: ludwig
 */

#include "ocltest.h"

void ocltest_init()
{
	initialized = 1;
}

void ocltest_drop()
{
	initialized = 0;
}

int ocltest_isInitialized()
{
	return initialized;
}
