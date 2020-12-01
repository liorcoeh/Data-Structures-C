/*
 * Heap
 */

#ifndef HEAP_H
#define HEAP_H

#include <stddef.h> /* size_t */

typedef struct heap_s heap_t;

/******************************************************************************/

/* 
* Heap Create: create new heap managing struct
* Receive: cmp_func
*               * Receive: data1, data2 - data to compare
*               * Return: 1 if data1 is closer to the root than data2
*                         0 if they equal
*                        -1 if data2 is farer from the root than data1
* Return: pointer to a new heap_t struct			  
* Errors: return NULL if error
* Time Complexity: O(1) 
*/
heap_t *HeapCreate(int (*cmp_func)(const void *data1, const void *data2));

/* 
* Heap Destroy: destroy heap managing struct
* Receive: heap - heap_t struct to destroy
* Time Complexity: O(1) 
*/
void HeapDestroy(heap_t *heap);

/* 
* Heap Push: push new element to the heap
* Receive: heap - heap_t struct to push into
*          data - data to push
* Return: 0 if succeed, any other number if not		  
* Time Complexity: O(1) 
*/
int HeapPush(heap_t *heap, const void *data);

/* 
* Heap Pop: pop element from the heap
* Receive: heap - heap_t struct to pop from
* Time Complexity: O(1) 
*/
void HeapPop(heap_t *heap);

/* 
* Heap Peek: peek element from heap
* Receive: heap - heap_t struct to push into
* Return: pointer to void data
* Time Complexity: O(1) 
*/
void *HeapPeek(const heap_t *heap);

/* 
* Heap Size: get the size of the heap
* Receive: heap - heap_t struct to push into
* Return: size_t with the size of the heap
* Time Complexity: O(1) 
*/
size_t HeapSize(const heap_t *heap);

/* 
* Heap Is Empty: check if the heap is empty
* Receive: heap - heap_t struct to push into
* Return: 1 if empty, 0 if not
* Time Complexity: O(1) 
*/
int HeapIsEmpty(const heap_t *heap);

/* 
* Heap Remove: remove element from the 
* Receive: heap - heap_t struct to push into
*          cond_func
*               * Receive: data - to check
*                          param - for the function to work with
*               * Return: 1 if data is match the condition, 0 if not
* Return: pointer to the data of the element deleted, NULL if no element found
* Time Complexity: O(1) 
*/
void *HeapRemove(heap_t *heap,
                 int (*cond_func)(const void *data, const void *param),
                 const void *param);

#endif /* HEAP_H */











