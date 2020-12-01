/*
 * Scheduler - Functions Definitions
 */

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <unistd.h> /* sleep, time, time_t */

#include "priority_queue_heap.h"
#include "task.h"
#include "scheduler.h"

/* scheduler managing struct */
struct scheduler
{
	pqueue_heap_t *queue;
	task_t *current_task;
	int to_stop;
};

/******************************************************************************/
/******************************************************************************
								UTILITY FUNCTIONS
							*************************/

/* A wrapper for TaskTimeCompare to make it valid for PQueueHeap */
static int TimeCompare(const void *data1, const void *data2);

/* A valid cond_func for PQueueHeapErase that also destroy the task if found */
static int EqualAndDestroyUIDs(const void *data1, const void *param);

/******************************************************************************/
/******************************************************************************
								 MAIN FUNCTIONS
						   *************************/
						   
scheduler_t *SchedulerCreate()
{
	scheduler_t *new_sched = NULL;
	pqueue_heap_t *new_pqueue = NULL;

	new_sched = (scheduler_t *)malloc(sizeof(scheduler_t));

	if (!new_sched)
	{
		return (NULL);
	}

	new_pqueue = PQueueHeapCreate(TimeCompare);

	if (!new_pqueue)
	{
		free(new_sched);
		new_sched = NULL;
		return (NULL);
	}

	new_sched->queue = new_pqueue;
	new_sched->current_task = NULL;
	new_sched->to_stop = 0;

	return (new_sched);
}

/******************************************************************************/

void SchedulerDestroy(scheduler_t *schd)
{
	assert(schd);

	/* empty and free the scheduler */
	SchedulerClear(schd);

	/* destroy its queue */
	PQueueHeapDestroy(schd->queue);

	free(schd);
	schd = NULL;
}

/******************************************************************************/

Uid_t SchedulerInsertTask(scheduler_t *schd,
						  size_t interval,
						  int (*operation_func)(void *param),
						  void *param)
{
	task_t *new_task = NULL;
	int status = 0;

	assert(schd);
	assert(operation_func);

	/* create new task structure */
	new_task = TaskCreate(interval, operation_func, param);

	if (!new_task)
	{
		return (UIDGetBadUID());
	}

	/* enqueuing the new task */
	status = PQueueHeapEnqueue(schd->queue, new_task);

	if (status != 0)
	{
		TaskDestroy(new_task);

		return (UIDGetBadUID());
	}

	return (TaskGetUID(new_task));
}

/******************************************************************************/

int SchedulerRun(scheduler_t *schd)
{
	int status = 0;
	schd->to_stop = 0;

	assert(schd);

	/* run until had to stop by to_stop or by emptiness */
	while (!schd->to_stop && !SchedulerIsEmpty(schd))
	{
		/* peeking next task */
		schd->current_task = (task_t *)PQueueHeapPeek(schd->queue);

		/* check the timing and set sleep delay if needed */
		if (TaskGetOperationTime(schd->current_task) > time(NULL))
		{
			sleep(TaskGetOperationTime(schd->current_task) - time(NULL));
		}

		PQueueHeapDequeue(schd->queue);

		status = TaskExecute(schd->current_task);

		/* if task's status is 0, reenqueue it, if 1 - destroy it */
		if (status != 0)
		{
			TaskDestroy(schd->current_task);
		}
		else
		{
			TaskUpdateTimeToExecute(schd->current_task);
			status = PQueueHeapEnqueue(schd->queue, schd->current_task);

			if (status != 0)
			{
				return (2);
			}
		}
	}

	schd->current_task = NULL;

	/* return 0 if exited by command, 1 if scheduler empty */
	return (SchedulerIsEmpty(schd));
}

/******************************************************************************/

void SchedulerStop(scheduler_t *schd)
{
	assert(schd);

	schd->to_stop = 1;
}

/******************************************************************************/

int SchedulerRemoveTask(scheduler_t *schd, Uid_t uid)
{
	int status = 0;

	assert(schd);
	assert(!UIDIsSame(uid, UIDGetBadUID()));

	status = PQueueHeapErase(schd->queue, EqualAndDestroyUIDs, &uid);
	return (status);
}

void SchedulerClear(scheduler_t *schd)
{
	task_t *current_task = NULL;

	assert(schd);

	while (!PQueueHeapIsEmpty(schd->queue))
	{
		current_task = PQueueHeapPeek(schd->queue);
		TaskDestroy(current_task);

		PQueueHeapDequeue(schd->queue);
	}
}

/******************************************************************************/

int SchedulerIsEmpty(const scheduler_t *schd)
{
	assert(schd);

	/* check if the function called from inside the scheduler */
	if (schd->current_task != NULL)
	{
		return (0);
	}
	else
	{
		return (PQueueHeapIsEmpty(schd->queue));
	}
}

/******************************************************************************/

size_t SchedulerSize(const scheduler_t *schd)
{
	assert(schd);

	/* check if the function called from inside the scheduler */
	if (schd->current_task != NULL)
	{
		return (PQueueHeapSize(schd->queue) + 1);
	}
	else
	{
		return (PQueueHeapSize(schd->queue));
	}
}

/******************************************************************************/
/******************************************************************************
								UTILITY FUNCTIONS
							*************************/

static int TimeCompare(const void *data1, const void *data2)
{
	return (TaskCompareTime((task_t *)data1, (task_t *)data2));
}

/******************************************************************************/

static int EqualAndDestroyUIDs(const void *data1, const void *param)
{
	int is_equal = 0;
	Uid_t uid_param = *(Uid_t *)param;
	task_t *task_data1 = (task_t *)data1;

	is_equal = UIDIsSame(uid_param, TaskGetUID(task_data1));

	if (is_equal)
	{
		TaskDestroy(task_data1);
	}

	return (is_equal);
}

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	








