/*
 * Queue - Functions Definitions
 */


#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "queue.h"
#include "singly_linked_list.h"


struct queue
{
	sll_t *list;	/* typedef struct singly_linked_list sll_t */
};

/*****************************************************************************/

queue_t *QueueCreate()
{
	sll_t *new_list = SLLCreate();
	queue_t *new_queue = (queue_t *)malloc(sizeof(queue_t));

	/* handle memory allocation errors */
	if (!new_list)
	{
		return (NULL);
	}
	else if (!new_queue)
	{
		SLLDestroy(new_list);
		return (NULL);
	}
	new_queue->list = new_list;

	return (new_queue);
}

/*****************************************************************************/

void QueueDestroy(queue_t *queue)
{
	assert(NULL != queue);
	SLLDestroy(queue->list);

	free(queue);
	queue = NULL;
}

/*****************************************************************************/

int QueueEnqueue(queue_t *queue, void *data)
{
	iterator_t end = SLLEnd(queue->list);
	iterator_t check = SLLInsert(end, data);
	
	if (SLLIsSameIter(end, check))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/*****************************************************************************/

void QueueDequeue(queue_t *queue)
{
	assert(NULL != queue);
	
	SLLRemove(SLLBegin(queue->list));
}

/*****************************************************************************/

void *QueuePeek(queue_t *queue)
{
	iterator_t start = SLLBegin(queue->list);
	
	return (SLLGetData(start));
}

/*****************************************************************************/

size_t QueueSize(queue_t *queue)
{
	return (SLLCount(queue->list));
}

/*****************************************************************************/

void QueueAppend(queue_t *queue1, queue_t *queue2)
{
	SLLAppend(queue1->list, queue2->list);
	
	free(queue2);
	queue2 = NULL;
}

/*****************************************************************************/

int QueueIsEmpty(queue_t *queue)
{
	if (0 == SLLCount(queue->list))
	{
		return (1);
	}
	
	return (0);
}












