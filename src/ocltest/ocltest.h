/*
 * ocltest.h
 *
 *  Created on: Jun 13, 2011
 *      Author: ludwig
 */

#ifndef OCLTEST_H_
#define OCLTEST_H_

#include "kernel_functions.h"
#include "kernel_test.h"

#define __kernel
#define __global
#define __local
#define __private

int initialized;

void ocltest_init();
void ocltest_drop();
int ocltest_isInitialized();

#endif /* OCLTEST_H_ */
