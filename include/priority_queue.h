/*
 * Priority Queue
 */

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stddef.h> /* size_t */

#include "sorted_linked_list.h"

typedef struct pqueue pqueue_t;

/******************************************************************************/

/*
 * PQueue Create: Creates a new priority queue
 * Return: Pointer to the priority queue
 * Receive: Priority check function to give out the priorities
 * Time Complexity: O(1)
 */
pqueue_t *PQueueCreate(int (*priority_check)(const void *, const void *));

/*
 * PQueue Destroy: Frees all the memory that was used
 * Recieve: Pointer to the priority queue
 * Time Complexity: O(n)
 */
void PQueueDestroy(pqueue_t *pqueue);

/*
 * Pqueue Enqueu: Inserts a new element into the priority queue
 * Return: 0 for success, 1 for failure
 * Recieve:
 * - Pointer to the priority queue
 * - Pointer to the data to put in the queue
 * Time Complexity: O(1)
 */
int PQueueEnqueue(pqueue_t *pqueue, void *data);

/*
 * PQueue Dequeue: Removes the most prioritised element from the queue
 * Recieve: Pointer to the priority queue
 * Time Complexity: O(1)
 */
void PQueueDequeue(pqueue_t *pqueue);

/*
 * PQueue Peek: Gets the data of the most prioritised element in the queue
 * Return: Pointer to the requasted data
 * Receive: Pointer to the priority queue
 * Time Complexity: O(1)
 */
void *PQueuePeek(const pqueue_t *pqueue);

/*
 * PQueue Is Empty: Checks if the priority queue is empty or not
 * Return: 1 if it is empty, 0 if isn't
 * Recieve: Pointer to the priority queue
 * Time Complexity: O(1)
 */
int PQueueIsEmpty(const pqueue_t *pqueue);

/*
 * PQueue Size: Gets the amount of elements in the priority queue
 * Return: The amount of elements in the priority queue
 * Recieve: Pointer to the priority queue
 * Time Complexity: O(n)
 */
size_t PQueueSize(const pqueue_t *pqueue);

/*
 * PQueue Clear: Removes all the elements in the priority queue without
 * 				 destorying the queue
 * Recieve: Pointer to the priority queue
 * Time Complexity: O(n)
 */
void PQueueClear(pqueue_t *pqueue);

/*
 * PQueue Clear: Removes the first element that answers a certain condition
 * Return: 0 if found and removed, 1 if weren't found
 * Recieve:
 * - Pointer to the priorit queue
 * - Pointer to function used to determain the wanted condition
 * - Pointer to a parameter used by the function
 * Time Complexity: O(n)
 */
int PQueueErase(pqueue_t *pqueue,
				 int (*condition_func)(const void *, const void *),
				 const void *param);

#endif /* PRIORITY_QUEUE_H */

/*****************************************************************************/
/*
 * 1) A priority queue is a queue that has some kind of a priority check which
 *    can decide what data has more priority, and so the data that has the
 *	  highest priority will be the first one out
 * 2) It can be used for downloading stuff - we get to change priorities and
 *    download in diffrent order.
 * 3) As usuall, we wouldn't want to do that in case we would like to make
 *	  changes in the future, and wouldn't want to be bound to the sorted list.
 */










