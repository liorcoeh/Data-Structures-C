/*
 * Singly Linked List
 */

#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <stddef.h> /* size_t */

/* Singly Linked List type */
typedef struct singly_linked_list sll_t;

/* iterator type */
typedef struct sll_node *iterator_t;

/* SLL Create: O(1)							    */
/* Return: pointer to a new sll_t struct        */
/* Errors: return NULL if can't allocate memory */
sll_t *SLLCreate();

/* SLL destroy: O(n)							    */
/* Recieve: pointer to sll_t struct 				*/
/* Action: Free the memory allocated for the list   */
void SLLDestroy(sll_t *list);

/* SLL count: O(n) 								 */
/* Recieve: pointer to sll_ struct 		         */
/* Return: the current count of elements in list */
size_t SLLCount(const sll_t *list);

/* SLL Is Empty: O(1)				   */
/* Recieve: pointer to sll_t struct	   */
/* Return: return 1 if empty, 0 if not */
int SLLIsEmpty(const sll_t *list);

/* SLL Find: O(n) 														   */
/* Recieve: "from" iterator, "to" iterator, pointer to data to search, and */
/* match function to check if data is equal                        		   */
/* Return: iterator where data found, iterator at end if not			   */
/* found                                                                   */
iterator_t SLLFind(const iterator_t from,
				   const iterator_t to,
				   const void *data,
                   int (*match_func)(void *, void *));

/* SLL ForEach: O(n) 														*/
/* Recieve: "from" iterator, "to" iterator, pointer to action function that */
/*          receives pointer to void data and manipulate it. 				*/
/* Action: invokes the functions on each element in the list (callback)	    */
/* Return: 0 if operation succeed, 1 if not                                 */
int SLLForEach(iterator_t from,
			   iterator_t to,
			   void *param,
			   int (*action_func)(void *param, void *data));

/* SLL Begin: O(1) 												  */
/* Recieve: pointer to sll_t struct 							  */
/* Return: iterator at the beginnig of the list, if the list is   */
/* empty return iterator at end									  */
iterator_t SLLBegin(const sll_t *list);

/* SLL End: O(1)							 */
/* Recieve: pointer to sll_t struct          */
/* Return: iterator at the end of the list	 */
iterator_t SLLEnd(const sll_t *list);

/* SLL Next: O(1)								 */
/* Recieve: current iterator 					 */
/* Return: iterator at the next element in list  */
iterator_t SLLNext(const iterator_t current);

/* SLL Remove: O(1)								 */
/* Recieve: current iterator 					 */
/* Action: remove current element 				 */
/* Return: iterator at the next element in list  */
iterator_t SLLRemove(iterator_t who);

/* SLL Set Data: O(1)								*/
/* Recieve: current iterator, pointer to void data  */
/* Action: set the new data to the element      	*/
void SetData(iterator_t iter, const void *data);

/* SLL Insert: O(1)														   */
/* Recieve: iterator to insert element before it, pointer to void data     */
/* Action: insert new element with data before the iterator                */
/* Return: iterator at the new element in list                             */
/* Errors: return iterator at end if fails                                 */
iterator_t SLLInsert(iterator_t where, void *data);

/* SLL Get Data: O(1) 										 */
/* Recieve: current iterator  	                             */
/* Return: pointer to void data where the iterator points to */
void *SLLGetData(const iterator_t where);

/* SLL Same Iterator: O(1)								*/
/* Recieve: two iterators     	                        */
/* Return: 1 if the iterators are identical, 0 if not   */
int SLLIsSameIter(const iterator_t iter1, const iterator_t iter2);

/* SLL Append: O(1)															*/
/* Recieve: two pointers to two lists										*/
/* Action: connects (appends) the second list to the end of the first one	*/
void SLLAppend(sll_t *list1, sll_t *list2);

/* SLL Flip List O(n)						*/
/* Recieve: pointer to sll_t struct			*/
/* Action: Flips the direction of the list	*/
void SLLFlip(sll_t *list);

/* SLL Has a Loop O(n)						*/
/* Recieve: pointer to sll_t struct			*/
/* Return: 1 if there is a loop, 0 if not	*/
int SLLHasLoop(const sll_t *list);

/* SLL Find Intersection O(n)												*/
/* Recieve: two pointers to two sll_t structs								*/
/* Return: the iterator for the intersection								*/
/* Will return the iterator to the end of list1 if there is no intersection */
iterator_t SLLFindIntersection(sll_t *list1, sll_t *list2);




#endif /* SINGLY_LINKED_LIST_H */




















