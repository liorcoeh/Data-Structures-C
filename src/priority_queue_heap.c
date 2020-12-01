/*
 * Priority Queue - Based on a Heap - Functions Definitions
 */

#include <stdlib.h>
#include <assert.h>

#include "priority_queue_heap.h"
#include "heap.h"

/******************************************************************************/

struct priority_queue_heap
{
	heap_t *pqueue_heap;
}; /* pqueue_t */

/******************************************************************************/
/******************************************************************************
								 MAIN FUNCTIONS
						   *************************/

pqueue_heap_t *PQueueHeapCreate(int (*compare_func)(const void *data1,
													const void *data2))
{
	pqueue_heap_t *new_pqueue = NULL;
	assert(compare_func);

	new_pqueue = (pqueue_heap_t *)malloc(sizeof(pqueue_heap_t));

	if (!new_pqueue)
	{
		return (NULL);
	}

	new_pqueue->pqueue_heap = HeapCreate(compare_func);

	if (!new_pqueue->pqueue_heap)
	{
		free(new_pqueue);
		new_pqueue = NULL;

		return (NULL);
	}

	return (new_pqueue);
}

/******************************************************************************/

void PQueueHeapDestroy(pqueue_heap_t *pqueue)
{
	assert(pqueue);
	HeapDestroy(pqueue->pqueue_heap);

	free(pqueue);
	pqueue = NULL;
}

/******************************************************************************/

int PQueueHeapEnqueue(pqueue_heap_t *pqueue, const void *data)
{
	assert(pqueue);

	return (HeapPush(pqueue->pqueue_heap, data));
}

/******************************************************************************/

void PQueueHeapDequeue(pqueue_heap_t *pqueue)
{
	assert(pqueue);

	HeapPop(pqueue->pqueue_heap);
}

/******************************************************************************/

void *PQueueHeapPeek(const pqueue_heap_t *pqueue)
{
	assert(pqueue);

	return (HeapPeek(pqueue->pqueue_heap));
}

/******************************************************************************/

size_t PQueueHeapSize(const pqueue_heap_t *pqueue)
{
	assert(pqueue);

	return (HeapSize(pqueue->pqueue_heap));
}

/******************************************************************************/

int PQueueHeapIsEmpty(const pqueue_heap_t *pqueue)
{
	assert(pqueue);

	return (HeapIsEmpty(pqueue->pqueue_heap));
}

/******************************************************************************/

void PQueueHeapClear(pqueue_heap_t *pqueue)
{
	assert(pqueue);

	while (!HeapIsEmpty(pqueue->pqueue_heap))
	{
		HeapPop(pqueue->pqueue_heap);
	}
}

/******************************************************************************/

int PQueueHeapErase(pqueue_heap_t *pqueue,
					int (*cond_func)(const void *data, const void *param),
					const void *param)
{
	assert(pqueue);
	assert(cond_func);

	return (HeapRemove(pqueue->pqueue_heap, cond_func, param) != NULL ? 0 : 1);
}










