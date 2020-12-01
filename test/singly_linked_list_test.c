/*
 * Singly Linked List - Test File
 */

#include <stdio.h> /* printf */

#include "singly_linked_list.h"

/* function that compares to ints and return 1 if they equal, 0 if not */
int IntCompare(void *var1, void *var2);

/* function that add 1 to an int */
int IntAdd(void *data, void *param);

int main()
{
	sll_t *my_list = SLLCreate();

	iterator_t my_iter = SLLBegin(my_list);
	iterator_t i = 0;

	int var1 = 5;
	int var2 = 565;
	int var3 = 13;
	int var4 = 67;
	int var5 = 734;
	int var6 = 345;
	int var7 = 1234;
	
	int add = 1;

	printf("************** Singly Linked List DS Tests: **************\n\n");

	printf("** when the list is empty: **\n");
	printf("Elements: %lu\n", SLLCount(my_list));
	printf("Is Empty: %s\n\n", (SLLIsEmpty(my_list) ? "yes" : "no"));

	SLLInsert(my_iter, &var1);
	SLLInsert(my_iter, &var2);
	SLLInsert(my_iter, &var3);
	SLLInsert(my_iter, &var4);
	SLLInsert(my_iter, &var5);
	SLLInsert(my_iter, &var6);

	printf("** after inserting 6 elements: **\n");
	printf("Elements: %lu\n", SLLCount(my_list));
	printf("Is Empty: %s\n\n", (SLLIsEmpty(my_list) ? "yes" : "no"));
	for (i = SLLBegin(my_list); !SLLIsSameIter(i, SLLEnd(my_list)); i = SLLNext(i))
	{
		printf("element: %d\n", *(int *)SLLGetData(i));
	}

	SLLInsert(SLLEnd(my_list), &var7);
	printf("\n** after insert 1 element at end: **\n");
	printf("Elements: %lu\n", SLLCount(my_list));
	printf("Is Empty: %s\n\n", (SLLIsEmpty(my_list) ? "yes" : "no"));
	for (i = SLLBegin(my_list); !SLLIsSameIter(i, SLLEnd(my_list)); i = SLLNext(i))
	{
		printf("element: %d\n", *(int *)SLLGetData(i));
	}

	my_iter = SLLRemove(SLLNext(my_iter));

	printf("\n** remove the second element: **\n");
	printf("Elements: %lu\n", SLLCount(my_list));
	printf("Is Empty: %s\n\n", (SLLIsEmpty(my_list) ? "yes" : "no"));
	for (i = SLLBegin(my_list); !SLLIsSameIter(i, SLLEnd(my_list)); i = SLLNext(i))
	{
		printf("element: %d\n", *(int *)SLLGetData(i));
	}

	SetData(SLLNext(my_iter), &var5);

	printf("\n** set the 3rd element to 734: **\n");
	printf("Elements: %lu\n", SLLCount(my_list));
	printf("Is Empty: %s\n\n", (SLLIsEmpty(my_list) ? "yes" : "no"));
	for (i = SLLBegin(my_list); !SLLIsSameIter(i, SLLEnd(my_list)); i = SLLNext(i))
	{
		printf("element: %d\n", *(int *)SLLGetData(i));
	}

	my_iter = SLLFind(SLLBegin(my_list), SLLEnd(my_list), &var4, IntCompare);

	printf("\n** using find function to search 67 **\n");
	printf("The element found! %d\n", *(int *)SLLGetData(my_iter));

	SLLForEach(SLLBegin(my_list), SLLEnd(my_list), &add, IntAdd);

	printf("\n** using foreach function to add 1 to each element **\n");
	for (i = SLLBegin(my_list); !SLLIsSameIter(i, SLLEnd(my_list)); i = SLLNext(i))
	{
		printf("element: %d\n", *(int *)SLLGetData(i));
	}

	printf("\n** flipping the list: **\n");
	SLLFlip(my_list);
	for (i = SLLBegin(my_list); !SLLIsSameIter(i, SLLEnd(my_list)); i = SLLNext(i))
	{
		printf("element: %d\n", *(int *)SLLGetData(i));
	}
	
	if(1 == SLLHasLoop(my_list))
	{
		printf("there is a loop\n");
	}
	else
	{
		printf("there is NO loop\n");
	}
	
	SLLFindIntersection(my_list, my_list);
	
	SLLDestroy(my_list);

	return (0);
}

int IntCompare(void *var1, void *var2)
{
	return (*(int *)var1 == *(int *)var2);
}

int IntAdd(void *data, void *param)
{
	*(int *)data = *(int *)data + *(int *)param;

	return (0);
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}
