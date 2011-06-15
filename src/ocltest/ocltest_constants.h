/*
 * constants.h
 *
 *  Created on: Jun 13, 2011
 *      Author: ludwig
 */

#ifndef OCLTEST_CONSTANTS_H_
#define OCLTEST_CONSTANTS_H_

typedef enum
{
	ocltest_success,
	ocltest_invalid_problem_dimension,
	ocltest_invalid_local_size,
	ocltest_invalid_number_of_dimensions,
	ocltest_threading_failure,
	ocltest_failure_in_kernel_run
} OpenCLTestStatus;

#endif /* CONSTANTS_H_ */
