/*
 * kernel_functions.c
 *
 *  Created on: Jun 13, 2011
 *      Author: ludwig
 */

#include "kernel_functions.h"

void init_work_group(size_t threads_in_work_group)
{
	pthread_barrier_init(local_mem_fence, NULL, threads_in_work_group);
}

void drop_work_group(size_t threads_in_work_group)
{
	pthread_barrier_destroy(local_mem_fence);
}

int get_global_id(unsigned int dim)
{
	// TODO content here!
	return 0;
}

int get_local_id(unsigned int dim)
{
	// TODO content here!
	return 0;
}

void barrier(unsigned int barrier_type)
{
	if (barrier_type == CLK_LOCAL_MEM_FENCE)
	{
		pthread_barrier_wait(local_mem_fence);
	}
}
