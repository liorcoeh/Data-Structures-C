/*
 * Heap - Test File
 */


#include <stdio.h>	/* printf */
#include <assert.h> /* assert */

#include "heap.h"

/******************************************************************************/

/* variables for check */
int var1 = 10;
int var2 = 7;
int var3 = 1;
int var4 = 12;
int var5 = 14;
int var6 = 13;
int var7 = 5;
int var8 = 8;
int var9 = 9;
int var10 = 15;
int var11 = 4;
int var12 = 3;

int IntCompare(const void *var1, const void *var2);
int FindDivByFive(const void *data, const void *param);
int FindTwelve(const void *data, const void *param);

int BasicTests();

/******************************************************************************/

int main()
{
	assert(BasicTests() == 0);
	return (0);
}

/******************************************************************************/

int BasicTests()
{
	heap_t *new_heap = HeapCreate(IntCompare);

	assert(HeapIsEmpty(new_heap));
	assert(HeapSize(new_heap) == 0);

	HeapPush(new_heap, &var1);
	assert(!HeapIsEmpty(new_heap));
	assert(HeapSize(new_heap) == 1);
	assert(HeapPeek(new_heap) == &var1);

	HeapPush(new_heap, &var2);
	assert(!HeapIsEmpty(new_heap));
	assert(HeapSize(new_heap) == 2);
	assert(HeapPeek(new_heap) == &var1);

	HeapPush(new_heap, &var3);
	assert(!HeapIsEmpty(new_heap));
	assert(HeapSize(new_heap) == 3);
	assert(HeapPeek(new_heap) == &var1);

	HeapPush(new_heap, &var4);
	assert(!HeapIsEmpty(new_heap));
	assert(HeapSize(new_heap) == 4);
	assert(HeapPeek(new_heap) == &var4);

	HeapPush(new_heap, &var5);
	assert(!HeapIsEmpty(new_heap));
	assert(HeapSize(new_heap) == 5);
	assert(HeapPeek(new_heap) == &var5);

	HeapPush(new_heap, &var6);
	assert(!HeapIsEmpty(new_heap));
	assert(HeapSize(new_heap) == 6);
	assert(HeapPeek(new_heap) == &var5);

	HeapPush(new_heap, &var7);
	assert(!HeapIsEmpty(new_heap));
	assert(HeapSize(new_heap) == 7);
	assert(HeapPeek(new_heap) == &var5);

	HeapPush(new_heap, &var8);
	assert(!HeapIsEmpty(new_heap));
	assert(HeapSize(new_heap) == 8);
	assert(HeapPeek(new_heap) == &var5);

	HeapPush(new_heap, &var9);
	assert(!HeapIsEmpty(new_heap));
	assert(HeapSize(new_heap) == 9);
	assert(HeapPeek(new_heap) == &var5);

	HeapPush(new_heap, &var10);
	assert(!HeapIsEmpty(new_heap));
	assert(HeapSize(new_heap) == 10);
	assert(HeapPeek(new_heap) == &var10);

	HeapPush(new_heap, &var11);
	assert(!HeapIsEmpty(new_heap));
	assert(HeapSize(new_heap) == 11);
	assert(HeapPeek(new_heap) == &var10);

	HeapPush(new_heap, &var12);
	assert(!HeapIsEmpty(new_heap));
	assert(HeapSize(new_heap) == 12);
	assert(HeapPeek(new_heap) == &var10);

	HeapPop(new_heap);

	assert(HeapRemove(new_heap, FindDivByFive, NULL) == &var1);
	assert(HeapRemove(new_heap, FindDivByFive, NULL) == &var7);
	assert(HeapRemove(new_heap, FindDivByFive, NULL) == NULL);
	
	assert(HeapRemove(new_heap, FindTwelve, NULL) == &var4);
	
	HeapDestroy(new_heap);
	return (0);
}

/******************************************************************************/

int IntCompare(const void *var1, const void *var2)
{
	return (*(int *)var1 - *(int *)var2);
}

int FindDivByFive(const void *data, const void *param)
{
	(void)param;
	return (*(int *)data % 5 == 0);
}

int FindTwelve(const void *data, const void *param)
{
	(void)param;
	return (*(int *)data == 12);
}
