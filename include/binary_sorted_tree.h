/*
 * Binary AVL Tree
 */

#ifndef BINARY_SORTED_TREE_H
#define BINARY_SORTED_TREE_H

#include "doubly_linked_list.h"

typedef struct avl_tree avl_t;

typedef int (*avl_operation_t)(void *data, const void *arg);

/******************************************************************************/

/*
 * AVL Create: Creates the AVL manager struct and the first node, the root
 * Return: Pointer to the new AVL struct, in case of error will return NULL
 * Receive:
 * - int (*cmp_func) - Function that will decide where to put new nodes
 *					   The function receive two pointers to datas
 *					   Will return 0 for left, 1 for right -1 if equal
 * Time Complexity: O(log n)
 */
avl_t *AVLCreate(int (*cmp_func)(const void *first, const void *second));

/*
 * AVL Destroy: Frees all the memory used by the AVL
 * Receive: avl_t * - Pointer to the tree
 * Time Complexity: O(n)
 */
void AVLDestroy(avl_t *tree);

/*
 * AVL Insert: Inserts new node into the right place in the tree
 * Return: 0 if it was succsefull, 1 if there was an error
 * Receive:
 * - avl_t * - Pointer to the tree
 * - void * - Pointer to the data to put inside the tree
 * Time Complexity: O(log n)
 */
int AVLInsert(avl_t *tree, const void *data);

/*
 * AVL Remove: Removes a node from the tree
 * Receive:
 * - avl_t * - Pointer to the tree
 * - const void * - Pointer to the data to be removed
 * Time Complexity: O(log n)
 */ 
void AVLRemove(avl_t *tree, const void *data);

/*
 * AVL Is Empty: Checks if the tree is empty or not
 * Return: 1 if the tree is empty, 0 if it's not
 * Receive: const avl_t * - Pointer to tree
 * Time Complexity: O(1)
 */
int AVLIsEmpty(const avl_t *tree);/*done*/

/*
 * AVL Count: Gets the amount of nodes in the tree
 * Return: The amount of nodes in the tree
 * Receive: const avl_t * - Pointer to the tree
 * Time Complexity: O(n)
 */
size_t AVLCount(const avl_t *tree);/*done*/

/*
 * AVL Height: Gets the height of the tree
 * Return: The height of the tree
 * Receive: const avl_t * - Pointer to the tree
 * Time Complexity: O(1)
 */
size_t AVLHeight(const avl_t *tree);/*done*/

/*
 * AVL For Each: A function that does something to each node in the tree
 *				 It will work in one of three ways according to the function
 *				 it receives
 * Return: 0 if it was succesful, 1 if there was an error
 * Receive:
 * - avl_t * - Pointer to tree
 * - avl_operation_t - Function that travers the tree in one of three ways
 					   and does what needs to be done
 * - void * - Pointer to parameter to be used by the avl_operation_func
 * Time Complexity: O(n)
 */
int AVLForEach(avl_t *tree, avl_operation_t operation, const void *arg);

/*
 * AVL Find: Finds if certain data is in the tree
 * Return: Pointer to the node where the data was found, if no such node was
 *		   found, will return NULL
 * Receive:
 * - avl_t * - Pointer to the tree
 * - const void * - Pointer to the data being searched
 * Time Complexity: O(log n)
 */
void *AVLFind(const avl_t *tree, const void *data);


/***** Advanced *****/

/*
 * AVL Tree Remove Multiple: Function that removes several elements out of the
 * tree, according to a certain function that decides which one should be
 * Receive:
 * - avl_t * - Pointer to the tree
 * - int * - Pointer to the deciding function. This function receieve pointer
 			 to data and pointer to argumnet to be used
 * - void * - Pointer to an argument to be used in the deciding function
 * Time Complexity: O(n)
 */
 void AVLTreeRemoveMultiple(avl_t *tree,
						   int (*should_remove)(void *data, void *arg),
						   void *arg);

/*
 * AVL Tree Multi Find: Uses a help funtion to find certain criteria and than
 *						puts that information into a doubly linked list
 * Receive:
 * - avl_t * - Pointer to the tree
 * - int * - Pointer to the function to determain the criteria. This function
 *			 receives pointer to data and pointer to argument to be used
 * - void * - Pointer to the argument to be use by the function
 * - dll_t * - Pointer to the doubly linked list to put the data inside it
 * Time Complexity: O(n)
 */
void AVLTreeMultiFind(avl_t *tree,
					  int (*is_match)(void *data, void *arg),
					  void *arg,
					  dll_t *list);







#endif /* BINARY_SORTED_TREE_H */

















