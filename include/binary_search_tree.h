/*
 * Binary Search Tree
 */

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stddef.h> /* size_t */

/* Doubly Linked List type */
typedef struct binary_search_tree bst_t;
typedef struct bst_node *bst_iter_t;

/*
 * BST Create: Creates BST manager struct
 * Return: Pointer to the new BST struct, in case of error will return NULL
 * Receive:
 * - int (*cmp_func) - Function that will decide where to put new nodes
 *					   The function receive two pointers to data and one
 *					   pointer to a parameter
 *					   Will return 0 for left, 1 for right -1 if equal
 * - const void * - Pointer to the parameter being used by the cmp_func
 * Time Complexity: O(1)
 */
bst_t *BSTCreate(int (*cmp_func)
				(const void *data1, const void *data2, const void *param),
				const void *param);

/*
 * BST Destroy: Frees all the memory used by the BST
 * Receive: bst_t * - Pointer to the tree
 * Time Complexity: O(n)
 */
void BSTDestroy(bst_t *tree);

/*
 * BST Insert: Inserts new node into the right place in the tree
 * Return: Iterator to the new node, in case of error return NULL
 * Receive:
 * - bst_t * - Pointer to the tree
 * - const void * - Pointer to the data to put inside the tree
 * Time Complexity: O(log n)
 */
bst_iter_t BSTInsert(bst_t *tree, const void *data);

/*
 * BST Remove: Removes a node from the tree
 * Receive: bst_iter_t - Iterator to the requested node
 * Time Complexity: O(1)
 */
void BSTRemove(bst_iter_t current);

/*
 * BST Get Data: Gets the data from a requested node
 * Return: Pointer to the data in the requested node
 * Receive: const bst_iter_t - Iterator to the requested node
 * Time Complexity: O(1)
 */
void *BSTGetData(const bst_iter_t current);

/*
 * BST Begin: Finds the first node, the actual root of the tree
 * Return: Iterator to the first node
 * Receive: const bst_t * - Pointer to the tree
 * Time Complexity: O(log n)
 */
bst_iter_t BSTBegin(const bst_t *tree);

/*
 * BST End: Finds the last node in the tree, the lowest one
 * Return: Iterator to the last node
 * Receive: const bst_t * - Pointer to the tree
 * Time Complexity: O(1)
 */
bst_iter_t BSTEnd(const bst_t *tree); /* return NULL iterator */

/*
 * BST Next: Finds the next node in the tree
 * Return: Iterator to the next noded- If it is the largest one, return bst
 * Receive: const bst_iter_t - Iterator to the current node
 * Time Complexity: O(n)
 */
bst_iter_t BSTNext(const bst_iter_t current);

/*
 * BST Prev: Finds the previous node in the tree
 * Return: Iterator to the previous node - If it is the BSTBegin, undefined
 * Receive: const bst_iter_t - Iterator to the current node
 * Time Complexity: O(n)
 */
bst_iter_t BSTPrev(const bst_iter_t current);

/*
 * BST Size: Gets the amount of nodes in the tree
 * Return: The amount of nodes in the tree
 * Receive: const bst_t * - Pointer to the tree
 * Time Complexity: O(n)
 */
size_t BSTSize(const bst_t *tree);

/*
 * BST Is Empty: Checks if the tree is empty or not
 * Return: 1 if the tree is empty, 0 if it's not
 * Receive: const bst_t * - Pointer to tree
 * Time Complexity: O(1)
 */
int BSTIsEmpty(const bst_t *tree);

/*
 * BST Is Equal: Checks if two iterators are the same
 * Return: 0 if they are the same, 1 if not
 * Receive:
 * - const bst_iter_t - The first iterator to check
 * - const bst_iter_t - The second iterator to check
 * Time Complexity: O(1);
 */
int BSTIsEqual(const bst_iter_t iter1, const bst_iter_t iter2);

/*
 * BST Find: Finds if certain data is in the tree
 * Return: Iterator to the node that has the data, if no such node was
 *		   found, will return NULL
 * Receive:
 * - bst_t * - Pointer to the tree
 * - const void * - Pointer to the data being searched
 * Time Complexity: O(log n)
 */
bst_iter_t BSTFind(bst_t *tree, const void *data);

/*
 * BST For Each: A function that does something to each node in a certain range
 * Return: 0 if it was succesful, 1 if there was an error
 * Receive:
 * - const bst_iter_t - Iterator to the first place to start from
 * - const bst iter_t - Iterator to the last place to end at
 * - int (*opr_func) - Function that does what is needed, this function gets
 					   two pointers to data and parameter to be used
 * - void * - Pointer to parameter to be used by the opr_func
 * Time Complexity: O(n)
 */
int BSTForEach(const bst_iter_t from,
			   const bst_iter_t to,
			   int (*opr_func)(const void *, const void *),
			   const void *param);

#endif /* BINARY_SEARCH_TREE_H */
















