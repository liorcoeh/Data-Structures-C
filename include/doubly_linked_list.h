/*
 * Doubly Linked List
 */

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stddef.h> /* size_t */

/* Doubly Linked List type */
typedef struct doubly_linked_list dll_t;

/* iterator type */
typedef struct dll_node *dll_iter_t;

/* 
* Doubly Linked List Create: allocate memory and create manager struct		
* Return: pointer to a new dll_t struct			  
* Errors: return NULL if can't allocate memory 		    	  
* Time Complexity: O(1) 
*/
dll_t *DLLCreate();

/* 
* Doubly Linked List Destroy: destroy the list and free its memory
* Receive: 1. dll_t *list which points to dll_t manager struct 	
* Time Complexity: O(n) 
*/
void DLLDestroy(dll_t *list);

/* 
* Doubly Linked List Get Data: get data from iterator
* Recieve: 1. dll_iter_t iter that points at an element from the list
* Return: void * pointer to the data from iter
* Time Complexity: O(1) 
*/
void *DLLGetData(const dll_iter_t iter);

/* 
* Doubly Linked List Set Data: set data to iterator
* Recieve: 1. dll_iter_t iter that points at an element from the list
* 		   2. void *data to set the iterator to
* Time Complexity: O(1) 
*/
void DLLSetData(dll_iter_t iter, const void *data);

/* 
* Doubly Linked List Next:
* Recieve: 1. dll_iter_t iter that points at an element from the list
* Return: the next iterator from the list
* Time Complexity: O(1) 
*/
dll_iter_t DLLNext(const dll_iter_t iter);

/* 
* Doubly Linked List Prev:
* Recieve: 1. dll_iter_t iter that points at an element from the list
* Return: the previous iterator from the list
* Time Complexity: O(1) 
*/
dll_iter_t DLLPrev(const dll_iter_t iter);

/* 
* Doubly Linked List Is Empty: check if the list is empty
* Recieve: 1. dll_t *list which points to dll_t manager struct 	
* Return: 1 if empty, 0 if not
* Time Complexity: O(1) 
*/
int DLLIsEmpty(const dll_t *list);

/* 
* Doubly Linked List Remove: removes an element from the list
* Recieve: 1. dll_iter_t iter that points at an element to remove
* Return: dll_iter_t that points at the next iterator from the list
* Time Complexity: O(1) 
*/
dll_iter_t DLLRemove(dll_iter_t iter);

/* 
* Doubly Linked List Insert: inserts an element to the list
* Recieve: 1. dll_iter_t iter that points at an element to insert before it
*		   2. void *data to insert to the new element
* Return: dll_iter_t that points to the new element from the list
* Errors: if can't insert returns iterator at the end of the list -
*		  O(n) complexity
* Time Complexity: O(1) 
*/
dll_iter_t DLLInsert(dll_iter_t iter, const void *data);

/* 
* Doubly Linked List Size: 
* Recieve: 1. dll_t *list which points to dll_t manager struct
* Return: size_t with current size of the list
* Time Complexity: O(n) 
*/
size_t DLLSize(const dll_t *list);

/* 
* Doubly Linked List Begin:
* Recieve: 1. dll_t *list which points to dll_t manager struct
* Return: dll_iter_t that points to the first element from the list
*		  when the list is empty it returns the tail element which can be 
		  retrivied with DSLLEnd
* Time Complexity: O(1) 
*/
dll_iter_t DLLBegin(const dll_t *list);

/* 
* Doubly Linked List End: returns the last element in the list - a dummy element
*						  that its data is undefined.
* Recieve: 1. dll_t *list which points to dll_t manager struct
* Return: dll_iter_t that points to the last dummy element from the list
* Time Complexity: O(1) 
*/
dll_iter_t DLLEnd(const dll_t *list);

/* 
* Doubly Linked List Is Same Iter: 
* Recieve: 1. 2 dll_iter_t iter1 and iter2 to check if they are the same
* Return: 1 if the iterators are the same, 0 if not
* Time Complexity: O(1) 
*/
int DLLIsSameIter(const dll_iter_t iter1, const dll_iter_t iter2);

/* 
* Doubly Linked List Find: find an element in the list
* Recieve: 1. dll_iter_t from that sets the start point of the function
*		   2. dll_iter_t to	that sets the end point of the function
*		   3. const void *data to find in the list
*		   4. match_func function that recieves two pointers to void, compares
*		      their content, and if they are equal return 1, if not returns 0;
* Return: dll_iter_t that points to an element if found, iterator at end if not
* Time Complexity: O(n) 
*/
dll_iter_t DLLFind(const dll_iter_t from, const dll_iter_t to,
                   int (*match_func)(const void *, const void *),
                   const void *data);

/* 
* Doubly Linked List For Each: commit an action on every list element
* Recieve: 1. dll_iter_t from that sets the start point of the function
*		   2. dll_iter_t to	that sets the end point of the function
*		   3. action_func function that recieves pointer to void data and 
*		      pointer to void param, and commits an action on the data with the 
*		      param. it returns 0 for success and any other number if else
*		   4. void *param for the use of action_func
* Return: 0 if completed successfuly, the number that returned from action_func
* 		  if the loop stopped by it
* Time Complexity: O(n) 
*/
int DLLForEach(const dll_iter_t from, const dll_iter_t to,
               int (*action_func)(void *data, const void *param),
               const void *param);

/* 
* Doubly Linked List Pop Back: removes the last element in list
* Recieve: 1. dll_t *list which points to dll_t manager struct
* Return: void * with the data of the element that poped
* Time Complexity: O(1) 
*/
void *DLLPopBack(dll_t *list);

/* 
* Doubly Linked List Push Back: insert element at the end of the list
* Recieve: 1. dll_t *list which points to dll_t manager struct
* 		   2. void *data to insert the new element
* Return: dll_iter_t that points to the new element from the list
* Errors: if can't insert returns iterator at the end of the list
* Time Complexity: O(1) 
*/
dll_iter_t DLLPushBack(dll_t *list, const void *data);

/* 
* Doubly Linked List Pop Front: removed the first element in list
* Recieve: 1. dll_t *list which points to dll_t manager struct
* Return: void * with the data of the element that poped
* Time Complexity: O(1) 
*/
void *DLLPopFront(dll_t *list);

/* 
* Doubly Linked List Push Front: insert element at the head of the list
* Recieve: 1. dll_t *list which points to dll_t manager struct
* 		   2. void *data to insert the new element
* Return: dll_iter_t that points to the new element from the list
* Errors: if can't insert returns iterator at the end of the list o(n)
* Time Complexity: O(1) 
*/
dll_iter_t DLLPushFront(dll_t *list, const void *data);

/* 
* Doubly Linked List Splice: inserts a slice from one list into another one,
*							 and connects the first list to itself without the
*							 elements cropped.
* Recieve: 1. dll_iter_t cut_from that sets the start point of the crop
* 		   2. dll_iter_t cut_to that sets the end point of the crop exclusive
*		   3. dll_iter_t paste_to to insert the slice before it
* Return: iterator at the last element copied
* Time Complexity: O(n) 
*/
dll_iter_t DLLSplice(dll_iter_t cut_from, dll_iter_t cut_to,
                     dll_iter_t paste_to);

/* 
* Doubly Linked List Multi Find: find elements that match and add them to a new
*								 list
* Recieve: 1. const dll_iter_t from to start search from
* 		   2. const dll_iter_t to to end the search at
*		   3. const void *data to match with
*		   4. match_func function that recieves two pointers to void, compares
*		      their content, and if they are equal return 1, if not returns 0.
*		   5. dll_t *dest to insert the matched elements into.
* Return: number of elements inserted to dll_t *dest
* Time Complexity: O(n) 
*/
size_t DLLMultiFind(const dll_iter_t from, const dll_iter_t to,
                    int (*match_func)(const void *, const void *),
                    const void *data, dll_t *dest);

#endif /* DOUBLY_LINKED_LIST_H */

