/*
 * output.cpp
 *
 *  Created on: Apr 15, 2011
 *      Author: ludwig
 */

#include "output.h"

void outputLeft(unsigned int m, unsigned int maxM)
{
	if (m == 0)
	{
		if (maxM == 1)
		{
			printf("(\t");
		}
		else
		{
			printf("/\t");
		}
	}
	else
	{
		if (m == maxM - 1)
		{
			printf("\\\t");
		}
		else
		{
			printf("|\t");
		}
	}
}

void outputRight(unsigned int m, unsigned int maxM)
{
	if (m == 0)
	{
		if (maxM == 1)
		{
			printf(")\t");
		}
		else
		{
			printf("\\\t");
		}
	}
	else
	{
		if (m == maxM - 1)
		{
			printf("/\t");
		}
		else
		{
			printf("|\t");
		}
	}
	printf("\n");
}

void printMatrixS(const OCLBMatrixOrder order, const int m, const int n, float *a,
		const int lda)
{
	for (int _m = 0; _m < m; ++_m)
	{
		outputLeft(_m, m);
		for (int _n = 0; _n < n; ++_n)
		{
			if (order == ColumnMajor)
			{
				printf("%e\t", a[_n * lda + _m]);
			}
			else
			{
				printf("%e\t", a[_m * lda + _n]);
			}
		}
		outputRight(_m, m);
	}
}

void printMatrixD(const OCLBMatrixOrder order, const int m, const int n, double *a,
		const int lda)
{
	for (int _m = 0; _m < m; ++_m)
	{
		if (_m == 0)
		{
			if (m == 1)
			{
				printf("(\t");
			}
			else
			{
				printf("/\t");
			}
		}
		else
		{
			if (_m == m - 1)
			{
				printf("\\\t");
			}
			else
			{
				printf("|\t");
			}
		}
		for (int _n = 0; _n < n; ++_n)
		{
			if (order == ColumnMajor)
			{
				printf("%e\t", a[_n * lda + _m]);
			}
			else
			{
				printf("%e\t", a[_m * lda + _n]);
			}
		}
		if (_m == 0)
		{
			if (m == 1)
			{
				printf(")\t");
			}
			else
			{
				printf("\\\t");
			}
		}
		else
		{
			if (_m == m - 1)
			{
				printf("/\t");
			}
			else
			{
				printf("|\t");
			}
		}
		printf("\n");
	}
}
