/*
 * TrimpDgemm.h
 *
 *  Created on: Apr 15, 2011
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

#ifndef TRIMPSGEMM_H
#define TRIMPSGEMM_H

#include <stdlib.h>

#include <oclblas/output.h>
#include <oclblas/types.h>

#include <testutils/compare.h>

#include <trimp/trimpblas.h>

int
testSgemmColMajorNoTransNoTrans_3x3();

int
testSgemmColMajorTransNoTrans_3x3();

int
testSgemmColMajorTransNoTrans_3x3_with_lda();

int
testSgemmColMajorTransNoTrans_2x3_with_lda();

int
testSgemmColMajorTransNoTrans_2x3_with_lda_RowMajor();

#endif
