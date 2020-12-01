/*
 * Sorted Linked List
 */

#ifndef SORTED_LINKED_LIST_H
#define SORTED_LINKED_LIST_H

#include <unistd.h> /* size_t */

#include "doubly_linked_list.h"

/*****************************************************************************/

typedef struct sorted_linked_list dsll_t;

typedef dll_iter_t dsll_iter_t;

/*****************************************************************************/

/*
 * DSLL Create: Creates a new sorted linked list
 * Return: Pointer to the new sorted linked list
 * Receive: A user function to decide if the the new data supposed to be
 *			before old data or not
 * Time Complexity: O(1)
 */
dsll_t *DSLLCreate(int (*is_before)(const void *data1, const void *data2));

/*
 * DSLL Destroy: Frees all the memory that was used
 * Receive: Pointer to the sorted linked list
 * Time Complexity: O(n)
 */
void DSLLDestroy(dsll_t *list);

/*
 * DSLL Begin: Gets an iterator to the first node in the sorted linked list
 * Return: Iterator to the first node in the sorted linked list
 * Receive: Pointer to the sorted linked list
 * Time Complexity: O(1)
 */
dsll_iter_t DSLLBegin(const dsll_t *list);

/*
 * DSLL Next: Gets the iterator to the next node from the current iterator
 * Return: Iterator to the next node
 * Receive: Current iterator
 * Time Complexity: O(1)
 */
dsll_iter_t DSLLNext(const dsll_iter_t current);

/*
 * DSLL Prev: Gets the previous iterator from the current iterator
 * Return: The previous iterator
 * Receive: Current iterator
 * Time Complexity: O(1)
 */
dsll_iter_t DSLLPrev(const dsll_iter_t current);

/*
 * DSLL End: Gets the iterator to the "tail" of the list
 * Return: Iterator to the tail of the list
 * Receive: Pointer to the sorted linked list
 * Time Complexity: O(1)
 */
dsll_iter_t DSLLEnd(const dsll_t *list);

/*
 * DSLL Size: Gets the amount of nodes in the sorted linked list
 * Return: The amount of node in the sorted linked list
 * Receive: Pointer to the sorted linked list
 * Time Complexity: O(n)
 */
size_t DSLLSize(const dsll_t *list);

/*
 * DSLL Is Empty: Checks if the sorted linked list is empty or not
 * Return: 1 if the sorted linked list is empty, 0 if it's not
 * Receive: Pointer to the sorted linked list
 * Time Complexity: O(1)
 */
int DSLLIsEmpty(const dsll_t *list);

/*
 * DSLL Get Data: Gets the data from a certain node in the list
 * Return: Void pointer to the data from the requested node
 * Receive: Iterator to the requested node
 * Time Complexity: O(1)
 */
void *DSLLGetData(const dsll_iter_t current);

/*
 * DSLL Is Equal: Checks if two datas in two nodes are equal
 * Return: 1 if they are equal, 0 if not
 * Receive: Two iterators to the two nodes to compare
 * Time Complexity: O(1)
 */
int DSLLIsEqual(const dsll_iter_t iter1, const dsll_iter_t iter2);

/*
 * DSLL Insert: Adds a new node in the right place
 * Return: Iterator to the new node
 * Receive:
 * - Pointer to the sorted linked list
 * - Pointer to the data
 * Time Complexity: O(n)
 */
dsll_iter_t DSLLInsert(dsll_t *list, const void *data);

/*
 * DSLL Remove: Removes a node at a requested place
 * Return: Iterator to the next node in the list
 * Receive: Iterator to the node marked for removal
 * Time Complexity: O(1)
 */
dsll_iter_t DSLLRemove(const dsll_iter_t current);

/*
 * DSLL Pop Front: Removes the first node of the sorted linked list
 * Return: Pointer to the data of the first node
 * Receive: Pointer to the sorted linked list
 * Time Complexity: O(1)
 */
void *DSLLPopFront(dsll_t *list);

/*
 * DSLL Pop Back: Removes the last node of the sorted linked list
 * Return: Pointer to the data on the last node
 * Receive: Pointer to the sorted linked list
 * Time Complexity: O(1)
 */
void *DSLLPopBack(dsll_t *list);

/*
 * DSLL Find: Checks if a certain data is in the sorted linked list
 * Return: Iterator to the node where the data was found. If nothing was
 *		   found, return iterator to the end
 * Receive:
 * - Pointer to the sorted linked list
 * - Iterator to start check from
 * - Iterator to stop the check at
 * - Pointer to the data to check for
 * Time Complexity: O(n)
 */
dsll_iter_t DSLLFind(const dsll_t *list, const dsll_iter_t from,
					 const dsll_iter_t to, const void *data);

/*
 * DSLL Find If: Checks if certain conditions exist
 * Return: Iterator to the node where the condition was met. In case there
 * wasn't one, return iterator to the end
 * Receive:
 * - Pointer to the sorted linked list
 * - A conditional function, given by the user
 * - Pointer to the parameter to check the condition for
 * Time Complexity: O(n)
 */
dsll_iter_t DSLLFindIf(const dsll_t *list,
					   int (*cond_func)(const void *data1, const void *data2),
					   const void *param);

/*
 * DSLL For Each: Does a requested function to each element in a range
 * Return: 1 if it worked, 0 if it failed
 * Receive:
 * - Iterator to the node to start from
 * - Iterator to the node to end at
 * - Action function to make the changes
 * - Pointer to a parameter to do the function with
 * Time Complexity: O(n)
 */
int DSLLForEach(const dsll_iter_t from, const dsll_iter_t to,
				int (*action_func)(void *data, const void *param),
				const void *param);
				
/*
 * DSLL Merge: Merges between two sorted linked lists, the second list
 *			   remains empty
 * Receive: Pointers to two sorted linked lists
 * Time Complexity: O(n)
 */
void DSLLMerge(dsll_t *list1, dsll_t *list2);





#endif /* SORTED_LINKED_LIST_H */











