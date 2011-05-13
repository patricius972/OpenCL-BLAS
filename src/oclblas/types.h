/*
 * ocltypes.h
 *
 *  Created on: Apr 29, 2011
 *      Author: ludwig
 */

#ifndef OCLBTYPES_H_
#define OCLBTYPES_H_

#include <oclconfig.h>

typedef enum
{
	ColumnMajor, RowMajor
} OCLBMatrixOrder;

typedef enum
{
	NO, YES
} OCLBTranspose;

const char *opencl_types;

#endif /* OCLTYPES_H_ */
