/*
 * Binary Search Tree - Test File
 */

#include <stdio.h> /* printf() */
#include <time.h>	/* time()	*/
#include <stdlib.h> /* srand(), rand() */
#include <assert.h> /* assert() */

#include "binary_search_tree.h"

#define NUMBERS (50)

/**************************** User Functions *********************************/

/*
 * Cmp Func: Function to determine where each new node will be inserted
 * Return:
 * - 0 If the new data will be lower than the existing one
 * - 1 If the new data will be higher than the existing one
 * - -1 If both datas are the same
 * - Recieve:
 * - const void * - Pointer to the data that will be inserted
 * - const void * - Pointer to the data to compare to
 * - const void * - Pointer to a parameter which can be used in the function
 * Time Complexity: O(1)
 */
int CmpFunc(const void *data1, const void *data2, const void *param);

/*
 * Ope Func: Function that changes data inside an element
 * Return: 0 for success, 1 for failure
 * Receive:
 * - const void * - Pointer to the data that will be changed
 * - const void * - Pointer to a parameter which can be used in the function
 * Time Complexity: O(1)
 */
int OprFunc(const void *data, const void *param);

/*************************** Utility Functions *******************************/

/*
 * Function to use inside qsort later
 */
int rand_comparison(const void *a, const void *b);
 /*
  * Function that changes the order of elements in an array
  */
void shuffle(void *base, size_t nmemb, size_t size);

/*
 * Function that initialize an array to hold numbers from 1 - size
 */
void ArrInit(int arr[], size_t size);

/*
 * Function that prints out an array
 */
void PrintArr(int arr[], size_t size);

/*
 * Function that prints out the elemtnts of the tree using BSTNext
 */
void PrintTreeSmallToBig(bst_t *tree);

/*
 * Function that returns iterator to the last real element
 */
bst_iter_t LastRealElement(bst_t *tree, size_t size);

/*****************************************************************************/
/*****************************************************************************/

int main()
{
	int arr[NUMBERS] = {0};
	int root = 0;
	size_t i = 0;
	size_t size = 0;
	size_t counter = 0;

	int param = 2;
	int found = 130;
	
	bst_iter_t iter = NULL;
	bst_iter_t to_remove = NULL;
	bst_iter_t last_one = NULL; 
	
	bst_t *main_tree = BSTCreate(CmpFunc, &param);
	bst_t *copy_tree = BSTCreate(CmpFunc, &param);
	
	/* Initializing random numbers to insert in the tree, printing the	*/
	/* the oreder they will be inserted									*/
	ArrInit(arr, NUMBERS);
	srand(time(0));
	shuffle(arr, NUMBERS, sizeof(int));
	PrintArr(arr, NUMBERS);
	
	/* Checking that the tree is created and it's empty */
	printf("The tree is empty (1): %d\n", BSTIsEmpty(main_tree));
	
	printf("Size is (0): %ld\n", BSTSize(main_tree));
	
	/* Inserting the numbers into the tree */
	for (i = 0; i < NUMBERS; ++i)
	{
		BSTInsert(main_tree, &arr[i]);
		BSTInsert(copy_tree, &arr[i]);
	}
	
	printf("After insert the tree is NOT empty (0): %d\n", BSTIsEmpty(main_tree));
	size = BSTSize(main_tree);
	printf("And it's size is (50): %ld\n", size);
	
	
	iter = BSTPrev(BSTEnd(main_tree));
	
	for (iter = BSTPrev(BSTEnd(main_tree)); !BSTIsEqual(iter, BSTBegin(main_tree));
		 iter = BSTPrev(iter))
	{
		printf("%d, ", *((int *)BSTGetData(iter)));
	}

	
	printf("The last element is: %d\n\n", *((int *)BSTGetData(iter)));
	
	last_one = LastRealElement(main_tree, size);
	printf("The last element is: %d\n\n", *((int *)BSTGetData(last_one)));
	
	iter = BSTBegin(main_tree);
	printf("The smallest element is (1): %d\n\n", *((int *)BSTGetData(iter)));
	
	printf("The elements from smallest to largest are:\n");
	PrintTreeSmallToBig(main_tree);
	
	printf("The elements according to post-order traversal are\n");
	root = PrintTreePostOrder(copy_tree);
	
	printf("The root is: %d\n\n", root);
	
	printf("After adding 2 to each element - the min will be (3) and ");
	printf("the max will be %ld. Observe:\n", NUMBERS + 2);
	BSTForEach(BSTBegin(main_tree), BSTEnd(main_tree), OprFunc, &param);
	PrintTreeSmallToBig(main_tree);
	
	/* Removing elements from the tree */
	for (i = 0; i < (NUMBERS / 5); ++i)
	{
		iter = BSTBegin(main_tree);
		iter = BSTNext(BSTNext(BSTNext(BSTNext(iter))));
		to_remove = iter;
		iter = BSTNext(iter);
		BSTRemove(to_remove);
		
		iter = BSTNext(BSTNext(BSTNext(BSTNext(iter))));
		to_remove = iter;
		iter = BSTNext(iter);
		BSTRemove(to_remove);
		counter += 2;
	}
	
	printf("After removing %ld elements, the size is: ", counter);
	size = BSTSize(main_tree);
	printf("%ld\n", size);
	
	last_one = LastRealElement(main_tree, size);
	
	printf("Because of the adding before, now the last one is (%ld): ", NUMBERS + 2);
	printf("%d\n\n", *((int *)BSTGetData(last_one)));
	
	BSTDestroy(main_tree);
	
	return (0);
}

/*****************************************************************************/
/*****************************************************************************/
int CmpFunc(const void *data1, const void *data2, const void *param)	
{
	if (*(int *)data1 < *(int *)data2)
	{
		return (0); /* Will go left */
	}
	else if (*(int *)data1 > *(int *)data2)
	{
		return (1); /* Will go right */
	}
	else
	{
		return (-1);
	}
}

/*****************************************************************************/	
	
int OprFunc(const void *data, const void *param)
{
	*(int *)data += *(int *)param;

	return (1);
}	

/*****************************************************************************/

int rand_comparison(const void *a, const void *b)
{
    (void)a; (void)b;

    return rand() % 2 ? +1 : -1;
}

/*****************************************************************************/

void shuffle(void *base, size_t nmemb, size_t size)
{
    qsort(base, nmemb, size, rand_comparison);
}

/*****************************************************************************/

void ArrInit(int arr[], size_t size)
{
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		arr[i] = i + 1;
	};
}

/*****************************************************************************/

void PrintArr(int arr[], size_t size)
{
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		printf("%d, ", arr[i]);
	}
	printf("\n\n");
}	

/*****************************************************************************/

void PrintTreeSmallToBig(bst_t *tree)
{
	bst_iter_t iter = NULL;
	
	assert(tree);
	
	iter = BSTBegin(tree);
	
	for (iter = BSTBegin(tree); !BSTIsEqual(iter, BSTEnd(tree));
		 iter = BSTNext(iter))
	{
		printf("%d, ", *((int *)BSTGetData(iter)));
	}
	printf("\n\n");
}

/*****************************************************************************/

void PrintTreeBigToSmall(bst_t *tree)
{
	bst_iter_t iter = NULL;
	
	assert(tree);
	
	iter = BSTPrev(BSTEnd(tree));
	
	for (iter = BSTPrev(BSTEnd(tree)); !BSTIsEqual(iter, BSTBegin(tree));
		 iter = BSTPrev(iter))
	{
		printf("%d, ", *((int *)BSTGetData(iter)));
	}
	printf("\n\n");
}

/*****************************************************************************/

bst_iter_t LastRealElement(bst_t *tree, size_t size)
{
	bst_iter_t iter = NULL;
	size_t i = 0;
	
	assert(tree);
	
	iter = BSTBegin(tree);
	
	for (i = 0; i < size - 1; ++i)
	{
		iter = BSTNext(iter);
	}
	
	return (iter);
}	

	
	
	
	
	
	
