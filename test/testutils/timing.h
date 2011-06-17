/*
 * timing.h
 *
 *  Created on: Apr 16, 2011
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
