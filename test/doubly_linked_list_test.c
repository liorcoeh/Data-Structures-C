/*
 * Doubly Linked List - Test File
 */

#include <stdio.h> /* printf */

#include "doubly_linked_list.h"

/* function that compares to ints and return 1 if they equal, 0 if not */
int IntCompare(const void *var1, const void *var2);

/* function that add 1 to an int */
int IntAdd(void *data, const void *param);

/* fucntion to print list elements */
void PrintList(dll_t *list);

int main()
{

	int status = 0;
	size_t elements = 0;
	dll_t *my_list = DLLCreate();
	dll_t *my_list2 = DLLCreate();

	dll_iter_t my_iter = 0;
	dll_iter_t i = 0;

	int var1 = 5;
	int var2 = 565;
	int var3 = 13;
	int var4 = 67;
	int var5 = 734;
	int var6 = 345;
	int var7 = 1234;
	int var8 = 1;
	int var9 = 2;
	int var10 = 3;

	printf("************** Singly Linked List DS Tests: **************\n\n");

	printf("** when the list is empty: **\n");
	printf("Elements: %lu\n", DLLSize(my_list));
	printf("Is Empty: %s\n\n", (DLLIsEmpty(my_list) ? "yes" : "no"));

	DLLInsert(DLLBegin(my_list), &var1);
	DLLInsert(DLLBegin(my_list), &var2);
	DLLInsert(DLLBegin(my_list), &var3);
	DLLInsert(DLLBegin(my_list), &var4);
	DLLInsert(DLLBegin(my_list), &var5);
	my_iter = DLLInsert(DLLBegin(my_list), &var6);

	printf("** after inserting 6 elements: **\n");
	PrintList(my_list);

	if (my_iter == DLLEnd(my_list))
	{
		printf("cant allocate\n");
		return (1);
	}

	printf("\n** iterating the list backwards: **\n");
	for (i = DLLPrev(DLLEnd(my_list)); !DLLIsSameIter(i, DLLPrev(DLLBegin(my_list)));
		 i = DLLPrev(i))
	{
		printf("element: %d\n", *(int *)DLLGetData(i));
	}

	DLLInsert(DLLEnd(my_list), &var7);
	printf("\n** after insert 1 element at end: **\n");
	PrintList(my_list);

	my_iter = DLLRemove(DLLBegin(my_list));

	printf("\n** remove the first element: **\n");
	PrintList(my_list);

	DLLSetData(DLLNext(DLLNext(my_iter)), &var10);

	printf("\n** set the 3rd element to 3: **\n");
	PrintList(my_list);

	my_iter = DLLFind(DLLBegin(my_list), DLLEnd(my_list), IntCompare, &var4);

	printf("\n** using find function to search 67 **\n");
	printf("The element found! %d\n", *(int *)DLLGetData(my_iter));

	status = DLLForEach(DLLBegin(my_list), DLLEnd(my_list), IntAdd, &var8);

	printf("\n** using foreach function to add 1 to each element **\n");
	PrintList(my_list);

	printf("\nPopping the back and that's the data: %d\n", *(int *)DLLPopBack(my_list));
	printf("Elements: %lu\n", DLLSize(my_list));
	printf("Is Empty: %s\n\n", (DLLIsEmpty(my_list) ? "yes" : "no"));

	DLLPushBack(my_list, &var1);
	printf("\n** Pushing data to the back and now this is the list: **\n");
	PrintList(my_list);

	printf("\nPopping the front and that's the data: %d\n", *(int *)DLLPopFront(my_list));
	printf("Elements: %lu\n", DLLSize(my_list));
	printf("Is Empty: %s\n\n", (DLLIsEmpty(my_list) ? "yes" : "no"));

	DLLPushFront(my_list, &var9);
	printf("\n** Pushing data to the front and now this is the list: **\n");
	PrintList(my_list);

	elements = DLLMultiFind(DLLBegin(my_list), DLLEnd(my_list), IntCompare, &var1, my_list2);
	printf("\nmultifind 6; %lu elements written\n", elements);
	printf("** list1: **\n");
	PrintList(my_list);
	printf("\n** list2: **\n");
	PrintList(my_list2);

	my_iter = DLLSplice(DLLNext(DLLBegin(my_list)), DLLEnd(my_list), DLLNext(DLLBegin(my_list2)));

	printf("\n** SPLICE 5 elements from list 1 to the middle of 2 **\n");
	PrintList(my_list);
	printf("\n** list2: **\n");
	PrintList(my_list2);

	printf("\nlast element copied: %d\n", *(int *)DLLGetData(my_iter));

	DLLDestroy(my_list);
	DLLDestroy(my_list2);

	return (0);
}

int IntCompare(const void *var1, const void *var2)
{
	return (*(int *)var1 == *(int *)var2);
}

int IntAdd(void *data, const void *param)
{
	*(int *)data = *(int *)data + *(int *)param;

	return (0);
}

void PrintList(dll_t *list)
{
	dll_iter_t i = 0;
	printf("Elements: %lu\n", DLLSize(list));
	printf("Is Empty: %s\n\n", (DLLIsEmpty(list) ? "yes" : "no"));
	for (i = DLLBegin(list); !DLLIsSameIter(i, DLLEnd(list));
		 i = DLLNext(i))
	{
		printf("element: %d\n", *(int *)DLLGetData(i));
	}
}

