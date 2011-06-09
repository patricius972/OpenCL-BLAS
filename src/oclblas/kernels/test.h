# 1 "SetMatrixFloatComplex.ocl"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "SetMatrixFloatComplex.ocl"
# 1 "SetMatrixTemplate.inc" 1
# 2 "SetMatrixFloatComplex.ocl" 2

void setMatrixFloatComplex(FloatComplex mat, unsigned int row, unsigned int col, float value) { if ((row >= mat.m) || (col >= mat.n)) { return; } if (mat.colMajor == 0) { if (mat.transposed == 0) { mat.data[row * mat.stride + col] = value; } else { mat.data[col * mat.stride + row] = value; } } else { if (mat.transposed == 0) { mat.data[col * mat.stride + row] = value; } else { mat.data[row * mat.stride + col] = value; } } };
