/*
 * Task - Functions Definitions
 */

#include <stdlib.h>
#include <assert.h>

#include "task.h"
#include "uid.h"

struct task
{
	Uid_t uid;
	size_t interval;
	time_t next_operation_time;
	int (*operation_func)(void *param);
	void *func_param;
};

/******************************************************************************/
/******************************************************************************
								 MAIN FUNCTIONS
						   *************************/

task_t *TaskCreate(size_t interval, int (*operation_func)(void *param),
				   void *param)
{
	task_t *new_task = NULL;
	assert(operation_func);

	new_task = (task_t *)malloc(sizeof(task_t));
	if (!new_task)
	{
		return (NULL);
	}

	new_task->operation_func = operation_func;
	new_task->interval = interval;
	new_task->func_param = param;
	new_task->uid = UIDCreate();
	TaskUpdateTimeToExecute(new_task);

	return (new_task);
}

/******************************************************************************/

void TaskDestroy(task_t *task)
{
	assert(task);

	free(task);
	task = NULL;
}

/******************************************************************************/

void TaskUpdateTimeToExecute(task_t *task)
{
	assert(task);

	task->next_operation_time = time(NULL) + task->interval;
}

/******************************************************************************/

time_t TaskGetOperationTime(task_t *task)
{
	assert(task);

	return (task->next_operation_time);
}

/******************************************************************************/

Uid_t TaskGetUID(task_t *task)
{
	assert(task);

	return (task->uid);
}

/******************************************************************************/

int TaskExecute(task_t *task)
{
	assert(task);

	return (task->operation_func(task->func_param));
}

/******************************************************************************/

int TaskCompareTime(const task_t *task1, const task_t *task2)
{
	assert(task1);
	assert(task2);

	if (task1->next_operation_time < task2->next_operation_time)
	{
		return (1);
	}
	else if (task1->next_operation_time > task2->next_operation_time)
	{
		return (-1);
	}
	else
	{
		return (0);
	}
}












