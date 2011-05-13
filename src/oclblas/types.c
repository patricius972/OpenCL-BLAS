/*
 * ocltypes.c
 *
 *  Created on: Apr 29, 2011
 *      Author: ludwig
 */

#include "types.h"

const char *opencl_types = ""
#if OCL_DOUBLE_SUPPORTED == 1
		"#pragma OPENCL EXTENSION cl_khr_fp64: enable                         \n"
#endif
			"                                                                     \n"
			"typedef struct {                                                     \n"
			"    float real;                                                      \n"
			"    float imag;                                                      \n"
			"} FloatComplex;                                                      \n"
			"                                                                     \n"
#if OCL_DOUBLE_SUPPORTED == 1
		"typedef struct {                                                     \n"
		"    double real;                                                     \n"
		"    double imag;                                                     \n"
		"} DoubleComplex;                                                     \n"
#endif
		"                                                                     \n"
		"typedef struct {                                                     \n"
		"    unsigned int m;                                                  \n"
		"    unsigned int n;                                                  \n"
		"    int colMajor;                                                    \n"
		"    int transposed;                                                  \n"
		"    int stride;                                                      \n"
		"    __global float *data;                                            \n"
		"} FloatMatrix;                                                       \n"
		"                                                                     \n"
#if OCL_DOUBLE_SUPPORTED == 1
		"typedef struct {                                                     \n"
		"    unsigned int m;                                                  \n"
		"    unsigned int n;                                                  \n"
		"    int colMajor;                                                    \n"
		"    int transposed;                                                  \n"
		"    int stride;                                                      \n"
		"    __global double *data;                                           \n"
		"} DoubleMatrix;                                                      \n"
#endif
		"                                                                     \n"
		"typedef struct {                                                     \n"
		"    unsigned int m;                                                  \n"
		"    unsigned int n;                                                  \n"
		"    int colMajor;                                                    \n"
		"    int transposed;                                                  \n"
		"    int stride;                                                      \n"
		"    __global FloatComplex *data;                                     \n"
		"} FloatComplexMatrix;                                                \n"
		"                                                                     \n"
#if OCL_DOUBLE_SUPPORTED == 1
		"typedef struct {                                                     \n"
		"    unsigned int m;                                                  \n"
		"    unsigned int n;                                                  \n"
		"    int colMajor;                                                    \n"
		"    int transposed;                                                  \n"
		"    int stride;                                                      \n"
		"    __global DoubleComplex *data;                                    \n"
		"} DoubleComplexMatrix;                                               \n"
#endif
		"                                                                     \n"
		"float getMatrixFloat(FloatMatrix mat, unsigned int row,              \n"
		"                     unsigned int col)                               \n"
		"{                                                                    \n"
		"    if ((row >= mat.m) || (col >= mat.n))                            \n"
		"    {                                                                \n"
		"        return 0.0;                                                  \n"
		"    }                                                                \n"
		"    if (mat.colMajor == 0)                                           \n"
		"    {                                                                \n"
		"        /* row major data access */                                  \n"
		"        if (mat.transposed == 0)                                     \n"
		"        {                                                            \n"
		"            /* non-transposed row major data access */               \n"
		"            return mat.data[row * mat.stride + col];                 \n"
		"        }                                                            \n"
		"        else                                                         \n"
		"        {                                                            \n"
		"            /* transposed column major data access */                \n"
		"            return mat.data[col * mat.stride + row];                 \n"
		"        }                                                            \n"
		"    }                                                                \n"
		"    else                                                             \n"
		"    {                                                                \n"
		"        /* column major data access */                               \n"
		"        if (mat.transposed == 0)                                     \n"
		"        {                                                            \n"
		"            /* non-transposed column major data access */            \n"
		"            return mat.data[col * mat.stride + row];                 \n"
		"        }                                                            \n"
		"        else                                                         \n"
		"        {                                                            \n"
		"            /* transposed column major data access */                \n"
		"            return mat.data[row * mat.stride + col];                 \n"
		"        }                                                            \n"
		"    }                                                                \n"
		"}                                                                    \n"
		"                                                                     \n"
		"void setMatrixFloat(FloatMatrix mat, unsigned int row,               \n"
		"                     unsigned int col, float value)                  \n"
		"{                                                                    \n"
		"    if ((row >= mat.m) || (col >= mat.n))                            \n"
		"    {                                                                \n"
		"        return;                                                      \n"
		"    }                                                                \n"
		"    if (mat.colMajor == 0)                                           \n"
		"    {                                                                \n"
		"        /* row major data access */                                  \n"
		"        if (mat.transposed == 0)                                     \n"
		"        {                                                            \n"
		"            /* non-transposed row major data access */               \n"
		"            mat.data[row * mat.stride + col] = value;                \n"
		"        }                                                            \n"
		"        else                                                         \n"
		"        {                                                            \n"
		"            /* transposed column major data access */                \n"
		"            mat.data[col * mat.stride + row] = value;                \n"
		"        }                                                            \n"
		"    }                                                                \n"
		"    else                                                             \n"
		"    {                                                                \n"
		"        /* column major data access */                               \n"
		"        if (mat.transposed == 0)                                     \n"
		"        {                                                            \n"
		"            /* non-transposed column major data access */            \n"
		"            mat.data[col * mat.stride + row] = value;                \n"
		"        }                                                            \n"
		"        else                                                         \n"
		"        {                                                            \n"
		"            /* transposed column major data access */                \n"
		"            mat.data[row * mat.stride + col] = value;                \n"
		"        }                                                            \n"
		"    }                                                                \n"
		"}                                                                    \n"
		"                                                                     \n"
#if OCL_DOUBLE_SUPPORTED == 1
		"double getMatrixDouble(DoubleMatrix mat, unsigned int row,           \n"
		"                     unsigned int col)                               \n"
		"{                                                                    \n"
		"    if ((row >= mat.m) || (col >= mat.n))                            \n"
		"    {                                                                \n"
		"        return 0.0;                                                  \n"
		"    }                                                                \n"
		"    if (mat.colMajor == 0)                                           \n"
		"    {                                                                \n"
		"        /* row major data access */                                  \n"
		"        if (mat.transposed == 0)                                     \n"
		"        {                                                            \n"
		"            /* non-transposed row major data access */               \n"
		"            return mat.data[row * mat.stride + col];                 \n"
		"        }                                                            \n"
		"        else                                                         \n"
		"        {                                                            \n"
		"            /* transposed column major data access */                \n"
		"            return mat.data[col * mat.stride + row];                 \n"
		"        }                                                            \n"
		"    }                                                                \n"
		"    else                                                             \n"
		"    {                                                                \n"
		"        /* column major data access */                               \n"
		"        if (mat.transposed == 0)                                     \n"
		"        {                                                            \n"
		"            /* non-transposed column major data access */            \n"
		"            return mat.data[col * mat.stride + row];                 \n"
		"        }                                                            \n"
		"        else                                                         \n"
		"        {                                                            \n"
		"            /* transposed column major data access */                \n"
		"            return mat.data[row * mat.stride + col];                 \n"
		"        }                                                            \n"
		"    }                                                                \n"
		"}                                                                    \n"
		"                                                                     \n"
		"void setMatrixDouble(DoubleMatrix mat, unsigned int row,             \n"
		"                     unsigned int col, double value)                 \n"
		"{                                                                    \n"
		"    if ((row >= mat.m) || (col >= mat.n))                            \n"
		"    {                                                                \n"
		"        return;                                                      \n"
		"    }                                                                \n"
		"    if (mat.colMajor == 0)                                           \n"
		"    {                                                                \n"
		"        /* row major data access */                                  \n"
		"        if (mat.transposed == 0)                                     \n"
		"        {                                                            \n"
		"            /* non-transposed row major data access */               \n"
		"            mat.data[row * mat.stride + col] = value;                \n"
		"        }                                                            \n"
		"        else                                                         \n"
		"        {                                                            \n"
		"            /* transposed column major data access */                \n"
		"            mat.data[col * mat.stride + row] = value;                \n"
		"        }                                                            \n"
		"    }                                                                \n"
		"    else                                                             \n"
		"    {                                                                \n"
		"        /* column major data access */                               \n"
		"        if (mat.transposed == 0)                                     \n"
		"        {                                                            \n"
		"            /* non-transposed column major data access */            \n"
		"            mat.data[col * mat.stride + row] = value;                \n"
		"        }                                                            \n"
		"        else                                                         \n"
		"        {                                                            \n"
		"            /* transposed column major data access */                \n"
		"            mat.data[row * mat.stride + col] = value;                \n"
		"        }                                                            \n"
		"    }                                                                \n"
		"}                                                                    \n"
#endif
		"                                                                     \n"
		"FloatComplex getMatrixFloatComplex(FloatComplexMatrix mat,           \n"
		"                     unsigned int row, unsigned int col)             \n"
		"{                                                                    \n"
		"    if ((row >= mat.m) || (col >= mat.n))                            \n"
		"    {                                                                \n"
		"        FloatComplex result = {0.0, 0.0};                            \n"
		"        return result;                                               \n"
		"    }                                                                \n"
		"    if (mat.colMajor == 0)                                           \n"
		"    {                                                                \n"
		"        /* row major data access */                                  \n"
		"        if (mat.transposed == 0)                                     \n"
		"        {                                                            \n"
		"            /* non-transposed row major data access */               \n"
		"            return mat.data[row * mat.stride + col];                 \n"
		"        }                                                            \n"
		"        else                                                         \n"
		"        {                                                            \n"
		"            /* transposed column major data access */                \n"
		"            return mat.data[col * mat.stride + row];                 \n"
		"        }                                                            \n"
		"    }                                                                \n"
		"    else                                                             \n"
		"    {                                                                \n"
		"        /* column major data access */                               \n"
		"        if (mat.transposed == 0)                                     \n"
		"        {                                                            \n"
		"            /* non-transposed column major data access */            \n"
		"            return mat.data[col * mat.stride + row];                 \n"
		"        }                                                            \n"
		"        else                                                         \n"
		"        {                                                            \n"
		"            /* transposed column major data access */                \n"
		"            return mat.data[row * mat.stride + col];                 \n"
		"        }                                                            \n"
		"    }                                                                \n"
		"}                                                                    \n"
		"                                                                     \n"
		"void setMatrixFloatComplex(FloatComplexMatrix mat,                   \n"
		"                     unsigned int row, unsigned int col,             \n"
		"                     FloatComplex value)                             \n"
		"{                                                                    \n"
		"    if ((row >= mat.m) || (col >= mat.n))                            \n"
		"    {                                                                \n"
		"        return;                                                      \n"
		"    }                                                                \n"
		"    if (mat.colMajor == 0)                                           \n"
		"    {                                                                \n"
		"        /* row major data access */                                  \n"
		"        if (mat.transposed == 0)                                     \n"
		"        {                                                            \n"
		"            /* non-transposed row major data access */               \n"
		"            mat.data[row * mat.stride + col] = value;                \n"
		"        }                                                            \n"
		"        else                                                         \n"
		"        {                                                            \n"
		"            /* transposed column major data access */                \n"
		"            mat.data[col * mat.stride + row] = value;                \n"
		"        }                                                            \n"
		"    }                                                                \n"
		"    else                                                             \n"
		"    {                                                                \n"
		"        /* column major data access */                               \n"
		"        if (mat.transposed == 0)                                     \n"
		"        {                                                            \n"
		"            /* non-transposed column major data access */            \n"
		"            mat.data[col * mat.stride + row] = value;                \n"
		"        }                                                            \n"
		"        else                                                         \n"
		"        {                                                            \n"
		"            /* transposed column major data access */                \n"
		"            mat.data[row * mat.stride + col] = value;                \n"
		"        }                                                            \n"
		"    }                                                                \n"
		"}                                                                    \n"
		"                                                                     \n"
#if OCL_DOUBLE_SUPPORTED == 1
		"DoubleComplex getMatrixDoubleComplex(DoubleComplexMatrix mat,        \n"
		"                     unsigned int row, unsigned int col)             \n"
		"{                                                                    \n"
		"    if ((row >= mat.m) || (col >= mat.n))                            \n"
		"    {                                                                \n"
		"        DoubleComplex result = {0.0, 0.0};                           \n"
		"        return result;                                               \n"
		"    }                                                                \n"
		"    if (mat.colMajor == 0)                                           \n"
		"    {                                                                \n"
		"        /* row major data access */                                  \n"
		"        if (mat.transposed == 0)                                     \n"
		"        {                                                            \n"
		"            /* non-transposed row major data access */               \n"
		"            return mat.data[row * mat.stride + col];                 \n"
		"        }                                                            \n"
		"        else                                                         \n"
		"        {                                                            \n"
		"            /* transposed column major data access */                \n"
		"            return mat.data[col * mat.stride + row];                 \n"
		"        }                                                            \n"
		"    }                                                                \n"
		"    else                                                             \n"
		"    {                                                                \n"
		"        /* column major data access */                               \n"
		"        if (mat.transposed == 0)                                     \n"
		"        {                                                            \n"
		"            /* non-transposed column major data access */            \n"
		"            return mat.data[col * mat.stride + row];                 \n"
		"        }                                                            \n"
		"        else                                                         \n"
		"        {                                                            \n"
		"            /* transposed column major data access */                \n"
		"            return mat.data[row * mat.stride + col];                 \n"
		"        }                                                            \n"
		"    }                                                                \n"
		"}                                                                    \n"
		"                                                                     \n"
		"void setMatrixDoubleComplex(DoubleComplexMatrix mat,                 \n"
		"                      unsigned int row, unsigned int col,            \n"
		"                      DoubleComplex value)                           \n"
		"{                                                                    \n"
		"    if ((row >= mat.m) || (col >= mat.n))                            \n"
		"    {                                                                \n"
		"        return;                                                      \n"
		"    }                                                                \n"
		"    if (mat.colMajor == 0)                                           \n"
		"    {                                                                \n"
		"        /* row major data access */                                  \n"
		"        if (mat.transposed == 0)                                     \n"
		"        {                                                            \n"
		"            /* non-transposed row major data access */               \n"
		"            mat.data[row * mat.stride + col] = value;                \n"
		"        }                                                            \n"
		"        else                                                         \n"
		"        {                                                            \n"
		"            /* transposed column major data access */                \n"
		"            mat.data[col * mat.stride + row] = value;                \n"
		"        }                                                            \n"
		"    }                                                                \n"
		"    else                                                             \n"
		"    {                                                                \n"
		"        /* column major data access */                               \n"
		"        if (mat.transposed == 0)                                     \n"
		"        {                                                            \n"
		"            /* non-transposed column major data access */            \n"
		"            mat.data[col * mat.stride + row] = value;                \n"
		"        }                                                            \n"
		"        else                                                         \n"
		"        {                                                            \n"
		"            /* transposed column major data access */                \n"
		"            mat.data[row * mat.stride + col] = value;                \n"
		"        }                                                            \n"
		"    }                                                                \n"
		"}                                                                    \n"
#endif
		"                                                                     \n"
		"                                                                     \n"
		"                                                                     \n"
		"                                                                     \n"
		"                                                                     \n"
		"                                                                     \n"
		"                                                                     \n"
		"                                                                     \n"
		"                                                                     \n";
