/*
 * Priority Queue - Functions Definitions
 */

#include <stdlib.h> /* malloc(), free() */
#include <assert.h> /* assert() */
#include <stdio.h>	/* printf() */

#include "priority_queue.h"

struct pqueue
{
	dsll_t *list;
	int (*priority_check)(const void *, const void *);
};

/******************************************************************************/

pqueue_t *PQueueCreate(int (*priority_check)(const void *data1,
					   const void *data2))
{
	pqueue_t *new_pqueue = NULL;
	dsll_t *new_list = NULL;

	assert(priority_check);

	new_pqueue = (pqueue_t *)malloc(sizeof(pqueue_t));

	if (!new_pqueue)
	{
		return (NULL);
	}

	new_list = DSLLCreate(priority_check);

	if (!new_list)
	{
		free(new_pqueue);
		return (NULL);
	}

	new_pqueue->list = new_list;
	new_pqueue->priority_check = priority_check;

	return (new_pqueue);
}

/******************************************************************************/

void PQueueDestroy(pqueue_t *pqueue)
{
	DSLLDestroy(pqueue->list);
	free(pqueue);
	pqueue = NULL;
}

/******************************************************************************/

int PQueueEnqueue(pqueue_t *pqueue, void *data)
{
	dsll_iter_t check = NULL;
	
	assert(pqueue);
	assert(data);
	
	check = DSLLInsert(pqueue->list, data);
	
	return (DSLLEnd(pqueue->list) == check);
}

/******************************************************************************/

void PQueueDequeue(pqueue_t *pqueue)
{
	DSLLRemove(DSLLBegin(pqueue->list));
}

/******************************************************************************/

void PQueueClear(pqueue_t *pqueue)
{
	dsll_iter_t start = DSLLBegin(pqueue->list);
	dsll_iter_t to_delete = start;

	while (!DSLLIsEqual(start,DSLLEnd(pqueue->list)))
	{
		to_delete = start;
		start = DSLLNext(start);
		DSLLRemove(to_delete);
	}
}

/******************************************************************************/

int PQueueErase(pqueue_t *pqueue,
				 int (*condition_func)(const void *, const void *),
				 const void *param)
{
	dsll_iter_t found = NULL;

	assert(pqueue);
	assert(condition_func);

	found = DSLLFindIf(pqueue->list, condition_func, param);

	if (found == DSLLEnd(pqueue->list))
	{
		return (1);
	}

	DSLLRemove(found);
	return (0);
}

/******************************************************************************/

int PQueueIsEmpty(const pqueue_t *pqueue)
{
	return (DSLLIsEmpty(pqueue->list));
}

/******************************************************************************/

size_t PQueueSize(const pqueue_t *pqueue)
{
	return (DSLLSize(pqueue->list));
}

/******************************************************************************/

void *PQueuePeek(const pqueue_t *pqueue)
{
	return (DSLLGetData(DSLLBegin(pqueue->list)));
}

/******************************************************************************/

void PrintList(pqueue_t *pqueue)
{
	dsll_iter_t from = DSLLBegin(pqueue->list);
	dsll_iter_t to = DSLLEnd(pqueue->list);
	
	for (from = DSLLBegin(pqueue->list); !DLLIsSameIter(from, to);
		 from = DSLLNext(from))
	{
		printf("%d->", *(int *)DSLLGetData(from));
	}
	printf("NULL");
	printf("\n\n");
}











