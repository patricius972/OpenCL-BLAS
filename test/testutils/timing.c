/*
 * timing.c
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

#include "timing.h"

struct timeMeasurement measureTime(void( func)(unsigned int problemSize),
		unsigned int problemSize)
{
	struct timeMeasurement result;
	result.seconds = 0.0;
	result.numRuns = 0;
	result.sigma = 0.0;
	double seconds[NUM_OF_RUNS];
	while (((result.numRuns < 3) || (result.seconds < 1.0)) && (result.numRuns
			< NUM_OF_RUNS))
	{
		/* This loop runs at least three times or until the total time collected
		 * is 1 second. The total number is not allowed to exceed NUM_OF_RUNS */
		result.numRuns++;

		struct timespec start;
		struct timespec stop;

		clock_gettime(CLOCK_REALTIME, &start);
		func(problemSize);
		clock_gettime(CLOCK_REALTIME, &stop);

		seconds[result.numRuns - 1] = (double) (stop.tv_sec - start.tv_sec)
				+ (double) (stop.tv_nsec - start.tv_nsec) / 1e9;
		result.seconds += seconds[result.numRuns - 1];
	}
	result.seconds /= (double) result.numRuns;
	for (unsigned int i = 0; i < result.numRuns; i++)
	{
		result.sigma += (seconds[i] - result.seconds) * (seconds[i]
				- result.seconds);
	}
	result.sigma /= (double) (result.numRuns - 1);
	result.sigma = sqrt(result.sigma);
	return result;
}

unsigned int getStandardProblemSizes(unsigned int **sizes)
{
	if (*sizes != NULL)
	{
		free(*sizes);
	}
	const unsigned int number = 23;
	*sizes = malloc(number * sizeof(unsigned int));

	(*sizes)[0] = 1;
	(*sizes)[1] = 2;
	(*sizes)[2] = 3;
	(*sizes)[3] = 4;
	(*sizes)[4] = 5;
	(*sizes)[5] = 6;
	(*sizes)[6] = 7;
	(*sizes)[7] = 8;
	(*sizes)[8] = 9;
	(*sizes)[9] = 10;
	(*sizes)[10] = 20;
	(*sizes)[11] = 30;
	(*sizes)[12] = 40;
	(*sizes)[13] = 50;
	(*sizes)[14] = 60;
	(*sizes)[15] = 70;
	(*sizes)[16] = 80;
	(*sizes)[17] = 90;
	(*sizes)[18] = 100;
	(*sizes)[19] = 200;
	(*sizes)[20] = 300;
	(*sizes)[21] = 400;
	(*sizes)[22] = 500;

	return number;
}

void printTimingStart(const char *platformName, const char *routineName)
{
	printf(
			"Start timing measurement for function ' %s ' in platform ' %s '...\n",
			routineName, platformName);
}

void printTiming(const unsigned int problemSize,
		const struct timeMeasurement *time)
{
	printf("%i\t%E\t%E\t%i\n", problemSize, time->seconds, time->sigma,
			time->numRuns);
}

void printTimingEnd(const char *platformName, const char *routineName)
{
	printf(
			"Finished timing measurement for function ' %s ' in platform ' %s '...\n",
			routineName, platformName);
}
