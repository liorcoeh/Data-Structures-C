/*
 * Task - Test File
 */

#include <stdio.h>
#include <assert.h>
#include <unistd.h>

#include "task.h"

/******************************************************************************/

int SampleOperation(void *param);
int BasicTests();

/******************************************************************************/

int main()
{
	assert(BasicTests() == 0);
	return (0);
}

/******************************************************************************/

int BasicTests()
{
	int par = 3;
	task_t *my_task = TaskCreate(5, SampleOperation, &par);
	task_t *my_task2 = TaskCreate(5, SampleOperation, &par);

	/* check update time and get operation time */
	time_t current_time = TaskGetOperationTime(my_task);
	sleep(3);
	TaskUpdateTimeToExecute(my_task);
	assert((current_time + 3) == TaskGetOperationTime(my_task));

	/* check task uid: */
	assert(UIDIsSame(TaskGetUID(my_task), TaskGetUID(my_task)));

	/* check task execute: */
	assert(TaskExecute(my_task) == 0);

	/* check task compare: */
	assert(TaskCompareTime(my_task, my_task2) == -1);
	assert(TaskCompareTime(my_task2, my_task) == 1);
	TaskUpdateTimeToExecute(my_task2);
	assert(TaskCompareTime(my_task, my_task2) == 0);

	TaskDestroy(my_task);
	TaskDestroy(my_task2);
	return (0);
}

int SampleOperation(void *param)
{
	int var = *(int *)param;
	printf("5 + %d = %d\n", var, 5 + var);

	return (0);
}
