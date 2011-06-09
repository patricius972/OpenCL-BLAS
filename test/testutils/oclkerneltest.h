/*
 * oclkerneltest.h
 *
 *  Created on: Jun 9, 2011
 *      Author: ludwig
 */

#ifndef OCLKERNELTEST_H_
#define OCLKERNELTEST_H_

#define check(expected, actual) \
	if (expected != actual) { \
		fprintf(stderr, "%s != %s in %s:%i!\n", #expected, #actual, __FILE__, __LINE__); \
		exit(1); \
	}

#endif /* OCLKERNELTEST_H_ */
