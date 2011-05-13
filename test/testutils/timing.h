/*
 * timing.h
 *
 *  Created on: Apr 16, 2011
 *      Author: ludwig
 */

#ifndef TIMING_H
#define TIMING_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define NUM_OF_RUNS 3

struct timeMeasurement
{
	double seconds;
	double sigma;
	unsigned int numRuns;
};

struct timeMeasurement
measureTime(void( func)(unsigned int problemSize), unsigned int problemSize);

unsigned int
getStandardProblemSizes(unsigned int **sizes);

void
printTimingStart(const char *platformName, const char *routineName);

void
printTiming(const unsigned int problemSize, const struct timeMeasurement *time);

void
printTimingEnd(const char *platformName, const char *routineName);

#endif
