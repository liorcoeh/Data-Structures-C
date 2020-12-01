/*
 * Priority Queue - Based on a Heap - Test File
 */

#include <stdio.h>	/* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */

#include "priority_queue_heap.h"

#define TEST (30)

/******************************************************************************/

int IntCompare(const void *data1, const void *data2);

static int IsDividedBy(int divided, int by);

int IntIsGreaterThanAndDestroy(const void *param, const void *data1);

int FindTwelve(const void *data, const void *param);

int BasicTests();
int ClearTests();
int EraseTests();

/******************************************************************************/

int main()
{
	assert(0 == BasicTests());
	assert(0 == ClearTests());
	assert(0 == EraseTests());

	return (0);
}

/******************************************************************************/

int BasicTests()
{
	pqueue_heap_t *my_queue = PQueueHeapCreate(IntCompare);
	int i = 0;
	int status = 0;
	int *num = NULL;

	assert(0 == PQueueHeapSize(my_queue));
	assert(PQueueHeapIsEmpty(my_queue));

	printf("*** priority is: divided by 5, and after that smaller than 20: ***\n\n");
	printf(">> writing elemnts, check that the address of those is the first when dequeing:\n\n");
	for (i = 0; i < TEST; ++i)
	{
		int *var = (int *)malloc(sizeof(int));
		*var = i;
		printf("%d, %p written\n", i, (void *)var);
		status = PQueueHeapEnqueue(my_queue, var);
	}
	assert(TEST == PQueueHeapSize(my_queue));
	assert(!PQueueHeapIsEmpty(my_queue));

	for (i = 0; i < TEST; ++i)
	{
		int *var = (int *)malloc(sizeof(int));
		*var = i;
		status = PQueueHeapEnqueue(my_queue, var);
	}

	assert(TEST * 2 == PQueueHeapSize(my_queue));

	printf("\n\n>> peeking and dequinig:\n\n");
	for (i = 0; i < (TEST * 2); ++i)
	{
		num = (int *)PQueueHeapPeek(my_queue);
		printf("%d: %d, %p\n", i, *num, (void *)num);
		PQueueHeapDequeue(my_queue);
		free(num);
	}

	assert(PQueueHeapIsEmpty(my_queue));
	PQueueHeapDestroy(my_queue);

	return (0);
}

int ClearTests()
{
	pqueue_heap_t *my_queue = PQueueHeapCreate(IntCompare);
	int var1 = 1;
	int var2 = 2;
	int var3 = 3;

	printf("\n\n>> clear test:\n\n");

	PQueueHeapEnqueue(my_queue, &var1);
	PQueueHeapEnqueue(my_queue, &var2);
	PQueueHeapEnqueue(my_queue, &var3);

	assert(PQueueHeapSize(my_queue) == 3);

	PQueueHeapClear(my_queue);

	assert(PQueueHeapIsEmpty(my_queue) == 1);

	PQueueHeapDestroy(my_queue);

	return (0);
}

int EraseTests()
{
	pqueue_heap_t *my_queue = PQueueHeapCreate(IntCompare);
	int i = 0;
	int status = 0;
	int var1 = TEST - 2;

	printf("\n\n>> erase test:\n\n");

	for (i = 0; i < TEST; ++i)
	{
		int *var = (int *)malloc(sizeof(int));
		*var = i;
		status = PQueueHeapEnqueue(my_queue, var);
	}
	assert(PQueueHeapSize(my_queue) == TEST);

	PQueueHeapErase(my_queue, IntIsGreaterThanAndDestroy, &var1);

	assert(PQueueHeapSize(my_queue) == TEST - 1);

	PQueueHeapErase(my_queue, FindTwelve, NULL);

	assert(PQueueHeapSize(my_queue) == TEST - 2);

	for (i = 0; i < (TEST - 2); ++i)
	{
		free(PQueueHeapPeek(my_queue));
		PQueueHeapDequeue(my_queue);
	}

	PQueueHeapDestroy(my_queue);

	return (0);
}

int IntCompare(const void *data1, const void *data2)
{
	int da1 = *(int *)data1;
	int da2 = *(int *)data2;

	if ((IsDividedBy(da1, 5) && IsDividedBy(da2, 5)) || ((!IsDividedBy(da1, 5) && !IsDividedBy(da2, 5))))
	{
		return (0);
	}
	else if (IsDividedBy(da1, 5))
	{
		return (1);
	}
	else
	{
		return (-1);
	}
}

static int IsDividedBy(int divided, int by)
{
	return (0 == divided % by);
}

int IntIsGreaterThanAndDestroy(const void *data1, const void *param)
{
	if (*(int *)data1 > *(int *)param)
	{
		free((void *)data1);
		return (1);
	}
	else
	{
		return (0);
	}
}

int FindTwelve(const void *data, const void *param)
{
	(void)param;
	return (*(int *)data == 12);
}







