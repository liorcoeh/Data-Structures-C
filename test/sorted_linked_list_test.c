/*
 * Sorted Linked List - Test File
 */

#include <stdio.h> /* printf() */

#include "sorted_linked_list.h"

/*
 * Function that checks if one data is before the other one, return 1 if it
 *  is, 0 if not. It's a customer function
 */
int IsBefore(const void *data1, const void *data2);

/*
 * Function that prints the list
 */
void PrintList(dsll_t *list);

/*
 * Function that compares to ints and return 1 if they equal, 0 if not
 */
int IntCompare(void *var1, void *var2);

/* 
 * function that adds paramater to an int
 */
int IntAdd(void *data, const void *param);

int main()
{
	int i = 0;
	
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	int f = 6;
	int g = 7;
	int h = 8;
	int check = 2;
	
	int fi[10] = {0};
	int se[10] = {0};
	
	iter_t my_iter= NULL;
	
	/**************************** Basic Check ********************************/
	
	dsll_t *main_list = DSLLCreate(IsBefore);
	dsll_t *first_list = DSLLCreate(IsBefore);
	dsll_t *second_list = DSLLCreate(IsBefore);

	printf("If the list is empty print (1): %d\n\n", DSLLIsEmpty(main_list));
	
	printf("Inserting 3 elements in this oreder: (1, 3, 2).");
	DSLLInsert(main_list, &a);
	DSLLInsert(main_list, &c);
	DSLLInsert(main_list, &b);
	
	printf("It should be reordered as: (3, 2, 1):\n");
	PrintList(main_list);
	
	printf("The size of the list is (3): %ld\n", DSLLSize(main_list));
	printf("Now the list is not empty (0): %d\n\n", DSLLIsEmpty(main_list));
	
	DSLLInsert(main_list, &a);
	my_iter = DSLLBegin(main_list);
	printf("Enter another element (1), and if it is equal to the first it ");
	printf("will print (1): %d\n\n", DSLLIsEqual(my_iter, DSLLNext(my_iter)));
	
	DSLLPopFront(main_list);
	DSLLPopBack(main_list);
	printf("Pop Front and Pop back should give: (2->1->NULL):\n");
	PrintList(main_list);
	
	my_iter = DSLLNext(DSLLBegin(main_list));
	printf("The address of the second element is: %p\n", (void *)my_iter);
	
	printf("and the address of the element that hold (2) in it is: ");
	my_iter = DSLLFind(main_list, DSLLBegin(main_list),
			  DSLLPrev(DSLLEnd(main_list)), &check);
	printf("%p\n\n", (void *)my_iter);
	
	printf("Removing the last element should give: (1->NULL);\n");
	DSLLRemove(my_iter);
	PrintList(main_list);
	
	printf("Inserting 7 new elements in random order (2, 5, 3, 4, 7, 6, 8)\n");
	DSLLInsert(main_list, &b);
	DSLLInsert(main_list, &e);
	DSLLInsert(main_list, &c);
	DSLLInsert(main_list, &d);
	DSLLInsert(main_list, &g);
	DSLLInsert(main_list, &f);
	DSLLInsert(main_list, &h);
	PrintList(main_list);
	
	DSLLForEach(DSLLBegin(main_list), DSLLEnd(main_list), IntAdd, &check);
	printf("After adding (2) to each element (10, 9, 8, 7, 6, 5, 4, 3)\n");
	PrintList(main_list);
	
	DSLLDestroy(main_list);
	
	/**************************** Merge Check ********************************/
	
	printf("Creating two new lists:\n");
	
	for (i = 0; i < 10; ++i)
	{
		fi[i] = 10 + (i * 3);
		se[i] = 5 + (i * 5);
	}
	
	for (i = 0; i < 10; ++i)
	{
		DSLLInsert(first_list, &fi[i]);
	}
	
	for (i = 0; i < 8; ++i)
	{
		DSLLInsert(second_list, &se[i]);
	}
	
	PrintList(first_list);
	PrintList(second_list);
	
	DSLLMerge(first_list, second_list);
	
	PrintList(first_list);
	PrintList(second_list);
	
	
	printf("The first list is not empty (0): %d\n", DSLLIsEmpty(first_list));
	printf("The second list is empty print (1): %d\n",DSLLIsEmpty(second_list));
	printf("\nThe size of the first list is: %ld\n", DSLLSize(first_list));
	
	DSLLDestroy(first_list);
	DSLLDestroy(second_list);
	
	return (0);
}

/******************************************************************************/
/******************************************************************************/

int IsBefore(const void *data1, const void *data2)
{	
	if (*(int *)data1 < *(int *)data2)
	{
		return (1);
	}
	else if (*(int *)data1 == *(int *)data2)
	{
		return (0);
	}
	else
	{
		return (-1);
	}
}

/******************************************************************************/

void PrintList(dsll_t *list)
{
	iter_t from = DSLLBegin(list);
	iter_t to = DSLLEnd(list);
	
	for (from = DSLLBegin(list); !DLLIsSameIter(from, to); from = DSLLNext(from))
	{
		printf("%d->", *(int *)DSLLGetData(from));
	}
	printf("NULL");
	printf("\n\n");
}

/******************************************************************************/

int IntCompare(void *var1, void *var2)
{
	return (*(int *)var1 == *(int *)var2);
}

/******************************************************************************/

int IntAdd(void *data, const void *param)
{
	*(int *)data = *(int *)data + *(int *)param;

	return (0);
}




