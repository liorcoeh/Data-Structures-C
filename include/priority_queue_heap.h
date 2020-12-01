/*
 * Priority Queue - Based on a Heap
 */

#ifndef PRIORITY_QUEUE_HEAP_H
#define PRIORITY_QUEUE_HEAP_H

#include <stddef.h> /* size_t */


typedef struct priority_queue_heap pqueue_heap_t;

/******************************************************************************/

/* 
* Priority Queue Create: allocate memory and create manager struct
* Recieve: pointer to priority_func:
*               * Recieve: 2 pointers to data to compare their priority
*               * Return:  1 if data1's priority is higher than data2
*                          0 if their priority is equal
*                         -1 if data2's priority is higher than data1
* Return: pointer to a new pqueue_heap_t struct			  
* Errors: return NULL if can't allocate memory 		    	  
* Time Complexity: O(1) 
*/
pqueue_heap_t *PQueueHeapCreate(int (*compare_func)(const void *data1,
                                                    const void *data2));

/* 
* Priority Queue Destroy: destroy the queue and free its memory
* Recieve: pointer to pqueue_heap_t struct  	    	  
* Time Complexity: O(n) 
*/
void PQueueHeapDestroy(pqueue_heap_t *pqueue);

/* 
* Priority Queue Enqueue: insert new item to the queue by its priority
* Recieve: pointer to pqueue_heap_t struct
*          pointer to data to insert
* Return: 0 for success, 1 for failure			  	    	  
* Time Complexity: O(n) 
*/
int PQueueHeapEnqueue(pqueue_heap_t *pqueue, const void *data);

/* 
* Priority Queue Dequeue: dequeue the first item from the queue
* Recieve: pointer to pqueue_heap_t struct
* Time Complexity: O(1) 
*/
void PQueueHeapDequeue(pqueue_heap_t *pqueue);

/* 
* Priority Queue Peek: get the data of the first item in the queue
* Recieve: pointer to pqueue_heap_t struct
* Return: pointer to the data of the first item
* Time Complexity: O(1) 
*/
void *PQueueHeapPeek(const pqueue_heap_t *pqueue);

/* 
* Priority Queue Size:
* Recieve: pointer to pqueue_heap_t struct
* Return: size_t with the current size of the queue
* Time Complexity: O(n) 
*/
size_t PQueueHeapSize(const pqueue_heap_t *pqueue);

/* 
* Priority Queue Is Empty:
* Recieve: pointer to pqueue_heap_t struct
* Return: 1 for empty queue, 0 for not empty
* Time Complexity: O(1) 
*/
int PQueueHeapIsEmpty(const pqueue_heap_t *pqueue);

/* 
* Priority Queue Clear: remove and free all the elements from the queue
* Recieve: pointer to pqueue_heap_t struct
* Time Complexity: O(n) 
*/
void PQueueHeapClear(pqueue_heap_t *pqueue);

/* 
* Priority Queue Erase: remove the first element that answers a condition
* Recieve: pointer to pqueue_heap_t struct
*          pointer to cond_func:
*               * Recieve: pointer to data and pointer for parameter
*               * Return: 1 if the condition returns true, 0 if false.
*          pointer to parameter
* Return: 0 if element found and erased, 1 if not found
* Time Complexity: O(n) 
*/
int PQueueHeapErase(pqueue_heap_t *pqueue,
                    int (*cond_func)(const void *data, const void *param),
                    const void *param);

#endif /* PRIORITY_QUEUE_HEAP_H */











