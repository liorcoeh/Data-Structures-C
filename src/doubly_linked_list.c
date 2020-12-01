/*
 * Doubly Linked List - Functions Definitions
 */

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "doubly_linked_list.h"

/* basic DLL node struct */
typedef struct dll_node
{
	void *data;
	struct dll_node *next;
	struct dll_node *prev;
} dll_node_t;

/* DLL managing struct */
struct doubly_linked_list
{
	dll_node_t head; /* points to the first element as its next */
	dll_node_t tail; /* points to the last elements as its prev */
};

/* utility function for new node creation */
static dll_node_t *CreateNode(const void *data);

dll_t *DLLCreate()
{
	dll_t *new_list = (dll_t *)malloc(sizeof(dll_t));

	if (!new_list)
	{
		return (NULL);
	}

	/* initializing the members for a new DLL */
	new_list->head.next = &new_list->tail;
	new_list->head.data = NULL;
	new_list->head.prev = NULL;
	new_list->tail.prev = &new_list->head;
	new_list->tail.data = NULL;
	new_list->tail.next = NULL;

	return (new_list);
}

dll_iter_t DLLInsert(dll_iter_t iter, const void *data)
{
	dll_node_t *new_node = CreateNode(data);

	assert(iter);

	/* return tail if allocation failed */
	if (!new_node)
	{
		while (NULL != iter->next)
		{
			iter = DLLNext(iter);
		}

		return (iter);
	}

	/* initialize new node's values and its neighbours values */
	new_node->next = iter;
	new_node->prev = iter->prev;
	iter->prev = new_node;
	new_node->prev->next = new_node;

	return (new_node);
}

dll_iter_t DLLBegin(const dll_t *list)
{
	assert(list);
	return (list->head.next);
}

dll_iter_t DLLNext(const dll_iter_t iter)
{
	assert(iter);

	return (iter->next);
}

dll_iter_t DLLPrev(const dll_iter_t iter)
{
	assert(iter);
	return (iter->prev);
}

int DLLIsEmpty(const dll_t *list)
{
	assert(list);
	return (list->head.next == &list->tail);
}

size_t DLLSize(const dll_t *list)
{
	dll_node_t *current = NULL;
	size_t counter = 0;

	assert(list);

	current = DLLBegin(list);

	/* counting elements until reaching the tail */
	while (NULL != DLLNext(current))
	{
		++counter;
		current = DLLNext(current);
	}

	return (counter);
}

dll_iter_t DLLEnd(const dll_t *list)
{
	assert(list);

	return ((dll_iter_t)&list->tail);
}

int DLLIsSameIter(dll_iter_t iter1, dll_iter_t iter2)
{
	assert(iter1 && iter2);

	return (iter1 == iter2);
}

void *DLLGetData(dll_iter_t iter)
{
	assert(iter);

	return (iter->data);
}

dll_iter_t DLLRemove(dll_iter_t iter)
{
	dll_iter_t next_node = NULL;

	assert(iter);
	assert(iter->next); /* validating not deleting tail */
	assert(iter->prev); /* validating not deleting head */

	/* save the next element to return it */
	next_node = DLLNext(iter);

	/* direct the last node to the next node */
	iter->next->prev = iter->prev;
	iter->prev->next = iter->next;

	free(iter);
	iter = NULL;

	return (next_node);
}

void DLLSetData(dll_iter_t iter, const void *data)
{
	assert(iter);

	iter->data = (void *)data;
}

dll_iter_t DLLFind(const dll_iter_t from, const dll_iter_t to,
				   int (*match_func)(const void *, const void *),
				   const void *data)
{
	dll_iter_t i = NULL; /* basic iterator to loop on */

	assert(match_func);
	assert(from);
	assert(to);

	/* iterate 'from'-'to' and if there's a match return the iterator */
	for (i = from; !DLLIsSameIter(i, to); i = DLLNext(i))
	{
		if (match_func(data, i->data))
		{
			return (i);
		}
	}

	/* if there wasn't matches return iterator at the 'to' argument */
	return (to);
}

int DLLForEach(const dll_iter_t from, const dll_iter_t to,
			   int (*action_func)(void *data, const void *param),
			   const void *param)
{
	dll_iter_t i = NULL; /* basic iterator to loop on 				 */
	int status = 0;		 /* status returned from the action function */

	assert(from);
	assert(to);
	assert(NULL != action_func);

	/* iterate 'from'-'to' and invoke the action function on each element */
	for (i = from; !DLLIsSameIter(i, to); i = DLLNext(i))
	{
		status = action_func(i->data, param);

		if (0 != status)
		{
			break;
		}
	}

	return (status);
}

void DLLDestroy(dll_t *list)
{
	assert(list);

	while (!DLLIsEmpty(list))
	{
		DLLRemove(DLLBegin(list));
	}

	free(list);
	list = NULL;
}

void *DLLPopBack(dll_t *list)
{
	void *data = NULL;

	assert(list);

	data = DLLPrev(DLLEnd(list))->data;
	DLLRemove(DLLPrev(DLLEnd(list)));

	return (data);
}

dll_iter_t DLLPushBack(dll_t *list, const void *data)
{
	assert(list);

	return (DLLInsert(DLLEnd(list), data));
}

void *DLLPopFront(dll_t *list)
{
	void *data = NULL;

	assert(list);

	data = DLLBegin(list)->data;
	DLLRemove(DLLBegin(list));

	return (data);
}

dll_iter_t DLLPushFront(dll_t *list, const void *data)
{
	assert(list);

	return (DLLInsert(DLLBegin(list), data));
}

size_t DLLMultiFind(const dll_iter_t from, const dll_iter_t to,
					int (*match_func)(const void *, const void *),
					const void *data, dll_t *dest)
{
	dll_iter_t i = NULL; /* basic iterator to loop on */
	size_t count = 0;

	assert(match_func);
	assert(from);
	assert(to);
	assert(dest);

	/* iterate 'to'-'from' and if there's a match cut the node and paste it  
	 * to the dest list														 */
	for (i = from; !DLLIsSameIter(i, to); i = DLLNext(i))
	{
		if (match_func(data, i->data))
		{
			DLLInsert(DLLBegin(dest), i->data);
			++count;
		}
	}

	return (count);
}

dll_iter_t DLLSplice(dll_iter_t cut_from, dll_iter_t cut_to,
					 dll_iter_t paste_to)
{
	dll_node_t *remem_to_prev = cut_to->prev;

	paste_to->prev->next = cut_from;

	cut_from->prev->next = cut_to;

	cut_to->prev = cut_from->prev;

	cut_from->prev = paste_to->prev;

	remem_to_prev->next = paste_to;

	paste_to->prev = remem_to_prev;

	return (paste_to->prev);
}

/***** Utility Functions: *****/

static dll_node_t *CreateNode(const void *data)
{
	dll_node_t *new_node = (dll_node_t *)malloc(sizeof(dll_node_t));

	/* check if allocation failed */
	if (NULL == new_node)
	{
		return (NULL);
	}

	new_node->data = (void *)data;
	new_node->next = NULL;
	new_node->prev = NULL;

	return (new_node);
}

