/*
 * Sorted Linked List - Functions Definitions
 */

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "sorted_linked_list.h"

struct sorted_linked_list
{
	dll_t *list;
	int (*priority_check)(const void *data1, const void *data2);
};

/*****************************************************************************/
/*****************************************************************************/

dsll_t *DSLLCreate(int (*priority_check)(const void *data1, const void *data2))
{
	dll_t *new_list = DLLCreate();
	dsll_t *new_slist = NULL;
	
	assert(priority_check);
	
	if (!new_list)
	{
		return (NULL);
	}
	
	new_slist = (dsll_t *)malloc(sizeof(dsll_t));
	if (!new_slist)
	{
		DLLDestroy(new_list);
	
		return (NULL);
	}
	
	new_slist->list = new_list;
	new_slist->priority_check = priority_check;

	return (new_slist);
}

/*****************************************************************************/

void DSLLDestroy(dsll_t *list)
{
	DLLDestroy(list->list);
	free(list);
	list = NULL;
}

/*****************************************************************************/

dsll_iter_t DSLLBegin(const dsll_t *list)
{
	return (DLLBegin(list->list));
}

/*****************************************************************************/

dsll_iter_t DSLLNext(const dsll_iter_t iter)
{
	return (DLLNext(iter));
}

/*****************************************************************************/

dsll_iter_t DSLLPrev(const dsll_iter_t iter)
{
	return (DLLPrev(iter));
}

/*****************************************************************************/

dsll_iter_t DSLLEnd(const dsll_t *list)
{
	return (DLLEnd(list->list));
}

/*****************************************************************************/

size_t DSLLSize(const dsll_t *list)
{
	return (DLLSize(list->list));
}

/*****************************************************************************/

int DSLLIsEmpty(const dsll_t *list)
{
	return (DLLIsEmpty(list->list));
}

/*****************************************************************************/

void *DSLLGetData(const dsll_iter_t iter)
{
	return (DLLGetData(iter));
}

/*****************************************************************************/

int DSLLIsEqual(const dsll_iter_t iter1, const dsll_iter_t iter2)
{
	return (DSLLGetData(iter1) == DSLLGetData(iter2));
}

/*****************************************************************************/

dsll_iter_t DSLLInsert(dsll_t *list, const void *data)
{
	dsll_iter_t i = NULL;
	dsll_iter_t check = NULL;
	
	assert(list);
	assert(data);

	for (i = DSLLBegin(list); !DLLIsSameIter(i, DSLLEnd(list)); i = DSLLNext(i))
	{
		if (0 < (list->priority_check)(data, DSLLGetData(i)))
		{
			check = DLLInsert(i, data);

			return (check);
		}
	}

	check = DLLInsert(DSLLEnd(list), data);
	
	return (check);
}

/*****************************************************************************/

dsll_iter_t DSLLRemove(dsll_iter_t iter)
{
	return (DLLRemove(iter));
}

/*****************************************************************************/

void *DSLLPopFront(dsll_t *list)
{
	return (DLLPopFront(list->list));
}

/*****************************************************************************/

void *DSLLPopBack(dsll_t *list)
{
	return (DLLPopBack(list->list));
}

/*****************************************************************************/

dsll_iter_t DSLLFind(const dsll_t *list, const dsll_iter_t from,
					 const dsll_iter_t to, const void *data)
{
	dsll_iter_t i = NULL;
	
	assert(list);
	assert(data);
	
	for (i = from; !DLLIsSameIter(i, to); i = DSLLNext(i))
	{
		if (0 == (list->priority_check)(DSLLGetData(i), data))
		{
			return (i);
		}
	}
	
	return (to);
}

/*****************************************************************************/

dsll_iter_t DSLLFindIf(const dsll_t *list,
					   int (*cond_func)(const void *data1, const void *data2),
					   const void *param)
{
	return (DLLFind(DSLLBegin(list), DSLLEnd(list), cond_func, param));
}

/*****************************************************************************/

int DSLLForEach(const dsll_iter_t from, const dsll_iter_t to,
				int (*action_func)(void *data, const void *param),
				const void *param)
{
	return (DLLForEach(from, to, action_func, param));
}


/*****************************************************************************/

void DSLLMerge(dsll_t *list1, dsll_t *list2)
{
	dsll_iter_t where_1 = DSLLBegin(list1);
	dsll_iter_t from_2 = DSLLBegin(list2);
	dsll_iter_t to_2 = from_2;

	assert(list1);
	assert(list2);

	/* iterate the lists and splice list2 to list1 in the appropriate places */
	while (!DSLLIsEmpty(list2) && where_1 != DSLLEnd(list1))
	{
		if (1 == (list1->priority_check)(DSLLGetData(from_2),
				  DSLLGetData(where_1)))
		{
			/* get to_2 to the last number that is smaller than where_1 */
			while (to_2 != DSLLEnd(list2) && (1 == (list1->priority_check)
				  (DSLLGetData(to_2), DSLLGetData(where_1))))
			{
				to_2 = DSLLNext(to_2);
			}
			DLLSplice(from_2, to_2, where_1);
			from_2 = to_2;
		}
		where_1 = DSLLNext(where_1);
	}

	/* check if where_1 is at the end and there are elements in list2 */
	if (!DSLLIsEmpty(list2))
	{
		DLLSplice(from_2, DSLLEnd(list2), where_1);
	}

	/*iter_t point_to = DSLLBegin(list2);
	iter_t to_delete = point_to;

	while (!DLLIsSameIter(point_to, DSLLEnd(list2)))
	{
		to_delete = point_to;
		DSLLInsert(list1, DSLLGetData(point_to));
		point_to = DSLLNext(point_to);
		DLLRemove(to_delete);
	}
	
	DLLSplice(iter_t where_1, iter_t from_2, iter_t to_2)*/
}















