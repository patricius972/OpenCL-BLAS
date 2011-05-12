#ifndef UPLABASE_TYPES_H
#define UPLABASE_TYPES_H

typedef enum
{
	SUCCESS, NOT_IMPLEMENTED, FAILURE, ARCHITECTURE_MISMATCH
} UplaStatus;

typedef enum
{
	ColumnMajor, RowMajor
} MatrixOrder;

typedef enum
{
	NO, YES
} Transpose;

#endif
