/*
 * Binary AVL Tree - Test File
 */

#include <stdio.h> /* printf() */
#include <time.h>	/* time()	*/
#include <stdlib.h> /* srand(), rand() */
#include <assert.h> /* assert() */

#include "binary_sorted_tree.h"

#define NUMBERS (50)
#define BIG_SIZE (50000)

#define PRINT
/*#define BIG_TEST */ /* Take this off if you want to see.. it works */

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
int CmpFunc(const void *first, const void *second);

/*
 * Ope Func: Function that changes data inside an element
 * Return: 0 for success, 1 for failure
 * Receive:
 * - const void * - Pointer to the data that will be changed
 * - const void * - Pointer to a parameter which can be used in the function
 * Time Complexity: O(1)
 */
int OprFunc(void *data, const void *param);

/*
 * Sould Remove: Function to decide if data should be removed
 * It will remove all even numbers (in this case)
 */
int ShouldRemove(void *data, void *arg);

/*
 * Is Match: Function that checks if data is equal to arg
 * It will cehck if the last digit of data is equal to arg (in this case)
 */
int IsMatch(void *data, void *arg);

/*************************** Utility Functions *******************************/

/*
 * Function to use inside qsort later
 */
static int rand_comparison(const void *a, const void *b);
 /*
  * Function that changes the order of elements in an array
  */
static void Shuffle(void *base, size_t nmemb, size_t size);

/*
 * Function that initialize an array to hold numbers from 1 - size
 */
static void ArrInit(int arr[], size_t size);

/*
 * Function that prints out an array
 */
static void TypeArr(int arr[], size_t size);
void PrintTree(avl_t *tree);
/*****************************************************************************/
/*****************************************************************************/

int main()
{
	int arr[NUMBERS] = {0};
	int big[BIG_SIZE] = {0};
	int i = 0;
	int counter = 0;
	int find = 0;
	int arg = 10;
	
	dll_t *main_list = DLLCreate();
	dll_iter_t iter = 0;

	avl_t *main_tree = NULL;
	avl_t *huge_tree = NULL;
	
	main_tree = AVLCreate(CmpFunc);
	huge_tree = AVLCreate(CmpFunc);
	
	/* Initializing random numbers to insert in the tree, printing the	*/
	/* the oreder they will be inserted									*/
	ArrInit(arr, NUMBERS);
	srand(time(0));
	Shuffle(arr, NUMBERS, sizeof(int));
	
	#ifdef PRINT
	TypeArr(arr, NUMBERS);
	#endif /* PRINT */
	
	/**************************************************************************/
	printf("After creation the tree is empty (1): ");
	printf("%d\n", AVLIsEmpty(main_tree));
	
	printf("After creation the amount of nodes is (0): ");
	printf("%ld\n\n", AVLCount(main_tree));
	
	/* Inserting the elements into the tree */
	for (i = 0; i < NUMBERS; ++i)
	{
		AVLInsert(main_tree, &arr[i]);
	}

	#ifdef PRINT
	PrintTree(main_tree);
	#endif /* PRINT */
	
	printf("After %d insertions the tree is NOT empty (0): ", NUMBERS);
	printf("%d\n", AVLIsEmpty(main_tree));
	
	printf("After %d insertions the amount of nodes is (%d): ", NUMBERS, NUMBERS);
	printf("%ld\n", AVLCount(main_tree));
	
	printf("After %d insertions the height of the tree is: ", NUMBERS);
	printf("%ld\n\n", AVLHeight(main_tree));
	
	find = arr[1];
	printf("Trying to find the data %d, found: ", find);
	printf("%d\n\n", *((int *)AVLFind(main_tree, &find)));
	
	
	/* Removing elements from the tree */
	for (i = 2; i <= NUMBERS - 2; ++i)
	{
		AVLRemove(main_tree, &arr[i]);
		++counter;
		++i;
	}
	
	#ifdef PRINT
	PrintTree(main_tree);
	#endif /* PRINT */
	
	printf("After %d removal the amount of nodes is (%d): ",
			counter, NUMBERS - counter);
	printf("%ld\n", AVLCount(main_tree));
	
	printf("After %d removal the height of the tree is (2): ", counter);
	printf("%ld\n", AVLHeight(main_tree));
	
	/* Checking For Each function - Will add 10 to each element */
	AVLForEach(main_tree, OprFunc, &arg);
	
	#ifdef PRINT
	PrintTree(main_tree);
	#endif /* PRINT */
	
	/* Checking Remove Multiple - Will remove every even number */
	arg = 2;
	AVLTreeRemoveMultiple(main_tree, ShouldRemove, &arg);
	printf("Removing all even numbers: \n");
	
	
	#ifdef PRINT
	PrintTree(main_tree);
	#endif /* PRINT */
	
	
	/* Checking Multi Find - Will find each number that has 5 as last digit */
	printf("\n\nChecking the AVLTreeMultiFind function:\n");
	printf("It will print all the numbers that the last digit is 5\n");
	printf("It will print it from a the doubly linked list\n\n");
	arg = 5;
	AVLTreeMultiFind(main_tree, IsMatch, &arg, main_list);
	
	for (iter = DLLPrev(DLLEnd(main_list));
		 !DLLIsSameIter(iter, DLLPrev(DLLBegin(main_list)));
		 iter = DLLPrev(iter))
	{
		printf("element: %d\n", *(int *)DLLGetData(iter));
	}
	
	DLLDestroy(main_list);
	AVLDestroy(main_tree);
	
	
	/**************************** The BIG - TEST!! ****************************/
	
	#ifdef BIG_TEST
	/* Initializing random numbers to insert in the huge tree */
	ArrInit(big, BIG_SIZE);
	srand(time(0));
	Shuffle(big, BIG_SIZE, sizeof(int));
	
	
	/* Inserting the elements into the huge tree */
	for (i = 0; i < BIG_SIZE; ++i)
	{
		AVLInsert(huge_tree, &big[i]);
		printf("%d\n", i);
	}
	
	/*#ifdef PRINT
	PrintTree(huge_tree);
	#endif*/ /* PRINT */
	
	printf("After %d insertions the tree is NOT empty (0): ", BIG_SIZE);
	printf("%d\n", AVLIsEmpty(huge_tree));
	
	printf("After %d insertions the amount of nodes in huge tree are (%d): ", BIG_SIZE, BIG_SIZE);
	printf("%d\n", AVLCount(huge_tree));
	
	printf("After %d insertions the height of the tree is: ", BIG_SIZE);
	printf("%ld\n\n", AVLHeight(huge_tree));
	#endif /* BIG_TEST */
	
	AVLDestroy(huge_tree);
	
	
	return (0);
}

/*****************************************************************************/
/*****************************************************************************

								USER FUNCTIONS
							**********************/
							
int CmpFunc(const void *first, const void *second)	
{
	return (*(int *)first - *(int *)second);
}

	
int OprFunc(void *data, const void *param)
{
	*(int *)data += *(int *)param;

	return (0);
}	


int ShouldRemove(void *data, void *arg)
{
	if (0 == (*(int *) data ) % (*(int *)arg))
	{
		return (0);	/* Should remove */
	}
	else
	{
		return (1);	/* Should NOT remove */
	}
}

int IsMatch(void *data, void *arg)
{
	int digit = (*((int *)data)) % 10;

	if (digit == *((int *)arg))
	{
		return (0);
	}
	else
	{
		return (1);
	}
}


/******************************************************************************

							   UTILITY FUNCTIONS
							**********************/

static int rand_comparison(const void *a, const void *b)
{
    (void)a; (void)b;

    return rand() % 2 ? +1 : -1;
}

/*****************************************************************************/

static void Shuffle(void *base, size_t nmemb, size_t size)
{
    qsort(base, nmemb, size, rand_comparison);
}

/*****************************************************************************/

static void ArrInit(int arr[], size_t size)
{
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		arr[i] = i + 1;
	};
}

/*****************************************************************************/

static void TypeArr(int arr[], size_t size)
{
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		printf("%d, ", arr[i]);
	}
	printf("\n\n");
}	









