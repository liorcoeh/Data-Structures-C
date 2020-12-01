/*
 * Scheduler - Test File
 */

#include <stdio.h>	/* printf */
#include <assert.h> /* assert */
#include <unistd.h> /* getuid, sleep */
#include <time.h>	/* time, time_t, ctime */

#include "scheduler.h"

#define TIMEFUNC_INTERVAL (3)
#define UIDFUNC_INTERVAL (5)
#define FIVEPLUSFUNC_INTERVAL (0)

struct to_remove
{
	scheduler_t *sched;
	Uid_t uid;
};

/* Test Functions: */
int BasicTests();
int AdvencedTests();

/* Sample Operation Functions */
/* basic: */
int PrintFivePlus(void *param);
int PrintUID(void *param);
int PrintTime(void *param);

/* advenced: */
int AddFuncsAndPrint(void *param);
int CountAndRemove(void *param);
int StopScheduler(void *param);

int main()
{
	assert(BasicTests() == 0);
	assert(AdvencedTests() == 0);

	return (0);
}

/* Test Functions: */
int BasicTests()
{
	scheduler_t *my_sched = SchedulerCreate();
	int num = 20;
	int status = 0;
	Uid_t task1 = UIDGetBadUID();
	Uid_t task2 = UIDGetBadUID();
	Uid_t task3 = UIDGetBadUID();

	/* check size & IsEmpty when empty: */
	assert(SchedulerIsEmpty(my_sched));
	assert(SchedulerSize(my_sched) == 0);

	/* inserting tasks: */
	task1 = SchedulerInsertTask(my_sched, TIMEFUNC_INTERVAL, PrintTime, my_sched);
	task2 = SchedulerInsertTask(my_sched, UIDFUNC_INTERVAL, PrintUID, NULL);
	task3 = SchedulerInsertTask(my_sched, FIVEPLUSFUNC_INTERVAL, PrintFivePlus, &num);

	/* check size & IsEmpty when full: */
	assert(!SchedulerIsEmpty(my_sched));
	assert(SchedulerSize(my_sched) == 3);

	/* running the scheduler: */
	printf("* expecting PrintTime every 3 sec, PrintUID every 5 sec, and \n");
	printf("* one time of PrintFivePlus. scheduler will stop after 6 times \n");
	printf("* of PrintTime: \n\n");

	status = SchedulerRun(my_sched);
	assert(0 == status);
	/* validate that exited by command */

	/* check SchedulerRemoveTask */
	SchedulerRemoveTask(my_sched, task2);
	assert(SchedulerSize(my_sched) == 1); /* 1 element went out when ran, 1 we removed*/

	printf("\n* Runnig again: expecting PrintTime every 5 sec, no Print UID, \n");
	printf("* one time of PrintFivePlus. scheduler will stop after 6 times \n");
	printf("* of PrintTime: \n\n");
	task3 = SchedulerInsertTask(my_sched, 0, PrintFivePlus, &num);
	status = SchedulerRun(my_sched); /* run it again without PrintUID */
	assert(0 == status);			 /* validate that exited by command */

	/* check SchedulerClear */
	SchedulerClear(my_sched);
	assert(SchedulerIsEmpty(my_sched));
	assert(SchedulerSize(my_sched) == 0);

	/* check return status is 1 when scheduler empty */
	status = SchedulerRun(my_sched);
	assert(status == 1);

	SchedulerDestroy(my_sched);

	return (0);
}

int AdvencedTests()
{
	scheduler_t *my_sched = SchedulerCreate();
	Uid_t task1 = UIDGetBadUID();
	Uid_t task2 = UIDGetBadUID();
	int status = 0;
	struct to_remove remove_item;

	task1 = SchedulerInsertTask(my_sched, 3, AddFuncsAndPrint, my_sched);
	remove_item.sched = my_sched;
	remove_item.uid = task1;
	task2 = SchedulerInsertTask(my_sched, 5, CountAndRemove, &remove_item);

	printf("\n* Runnig Advenced Tests: expecting AddFuncsAndPrint 4 times,\n");
	printf("* CountAndRemove 3 and than remove AddFuncsAndPrint and stop. \n");
	printf("* PrintUID should continue for 10 seconds and then stop \n\n");
	status = SchedulerRun(my_sched);
	printf("exited with status %d\n", status);

	SchedulerDestroy(my_sched);
	return (0);
}

/* Sample Operation Functions */
int PrintFivePlus(void *param)
{
	int var = *(int *)param;

	printf("5 + %d = %d\n\n", var, 5 + var);

	return (1);
}

int PrintUID(void *param)
{
	(void)param;

	printf("Current Proccess PID: %d\n\n", getpid());

	return (0);
}

int PrintTime(void *param)
{
	time_t current = time(NULL);
	static int count = 0;
	scheduler_t *my_sched = (scheduler_t *)param;

	printf("PrintTime function count %d\n", count);
	printf("Current Time: %s", ctime(&current));
	printf("Current Scheduler size: %ld\n", SchedulerSize(my_sched));
	printf("Is Empty? %d\n", SchedulerIsEmpty(my_sched));

	if (count == 5)
	{
		printf("Stopping the scheduler with SchedulerStop!\n");
		SchedulerStop(my_sched);

		count = 0;
	}
	else
	{
		++count;
	}

	printf("\n");
	return (0);
}

int AddFuncsAndPrint(void *param)
{
	scheduler_t *my_sched = NULL;
	static int count = 0;
	Uid_t task1 = UIDGetBadUID();

	my_sched = (scheduler_t *)param;
	printf("AddFuncsAndPrint!\n");
	printf("Current Scheduler size: %ld, after adding function: %ld\n\n", SchedulerSize(my_sched), SchedulerSize(my_sched) + 1);

	task1 = SchedulerInsertTask(my_sched, 7 - count, PrintUID, my_sched);

	if (count == 10)
	{
		count = 0;
	}
	else
	{
		++count;
	}

	return (0);
}

int CountAndRemove(void *param)
{
	struct to_remove *things = (struct to_remove *)param;
	static int count = 0;

	printf("CountAndRemove!\n");

	if (count == 2)
	{
		SchedulerRemoveTask(things->sched, things->uid);
		printf("Removing AddFuncsAndPrint!\n");
		SchedulerInsertTask(things->sched, 1, StopScheduler, things->sched);
		return (1);
	}
	else
	{
		++count;
	}

	printf("\n");

	return (0);
}

int StopScheduler(void *param)
{
	scheduler_t *my_sched = (scheduler_t *)param;
	static int count = 0;

	if (count == 9)
	{
		SchedulerStop(my_sched);
		return (1);
	}
	else
	{
		++count;
	}

	return (0);
}

