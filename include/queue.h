/*
 * Queue
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h> /* size_t */

typedef struct queue queue_t;

/* Queue Create: Creates a new queue									*/
/* Return: Pointer to the new queue. In case of error will return NULL	*/
/* Time Complexity: O(1);												*/
queue_t *QueueCreate();

/* Queue Destroy: Frees all the allocated memory for the queue	*/
/* Recieve: Pointer to the queue								*/
/* Time Complexity: O(n)										*/
void QueueDestroy(queue_t *queue);

/* Queue Enqueue: Adds a new element to the queue				*/
/* Return: 0 if succed or 1 if not								*/
/* Recieve: Pointer to the queue and void pointer to the data	*/
/* Time Complexity: O(1)										*/
int QueueEnqueue(queue_t *queue, void *data);

/* Queue Dequeue: Removes an element from the queue	*/
/* Recieve: Pointer to the queue					*/
/* Time complexity: O(1)							*/
void QueueDequeue(queue_t *queue);

/* Queue Peek: Gets the data from the element about to be removed	*/
/* Return: Void pointer to the data requasted						*/
/* Recieve: Pointer to the queue									*/
/* Time complexity: O(1)											*/
void *QueuePeek(queue_t *queue);

/* Queue Size: Gets the amount of element in the queue	*/
/* Return: Size_t amount of elements in the queue		*/
/* Recieve: Pointer to the queue						*/
/* Time complexity: O(n)								*/
size_t QueueSize(queue_t *queue);

/* Queue Append: Appends the second queue to the the end of the first queue	*/
/* Recieve: two pointers to two queues										*/
/* Time complexity: O(1)													*/
void QueueAppend(queue_t *queue1, queue_t *queue2);

/* Queue Is Empty: Checks if the queue has no elements in it	*/
/* Return: 1 if empty and 0 if not empty						*/
/* Recieve: Pointer to the queue								*/
/* Time complexity: O(1)										*/
int QueueIsEmpty(queue_t *queue);

#endif /* QUEUE_H */














