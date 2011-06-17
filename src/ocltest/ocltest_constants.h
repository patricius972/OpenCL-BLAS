/*
 * constants.h
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
