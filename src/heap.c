/*
 * Heap - Functions Definitions
 */

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <stdio.h>	/* printf */

#include "heap.h"
#include "dynamic_vector.h"


/* heap managing struct */
struct heap_s
{
	vector_t *heap_arr;
	int (*cmp_func)(const void *data1, const void *data2);
};

/******************************************************************************/
/******************************************************************************
								UTILITY FUNCTIONS
							*************************/

/* Reorder the heap after changes */
static void Heapify(heap_t *heap, size_t root_index);

/******************************************************************************/
/******************************************************************************
								 MAIN FUNCTIONS
						   *************************/

heap_t *HeapCreate(int (*cmp_func)(const void *data1,
								   const void *data2))
{
	heap_t *new_heap = (heap_t *)malloc(sizeof(heap_t));

	if (!new_heap)
	{
		return (NULL);
	}

	assert(cmp_func);

	new_heap->cmp_func = cmp_func;
	new_heap->heap_arr = VectorCreate(5);

	if (!new_heap->heap_arr)
	{
		free(new_heap);
		new_heap = NULL;

		return (NULL);
	}

	return (new_heap);
}

/******************************************************************************/

void HeapDestroy(heap_t *heap)
{
	assert(heap);

	VectorDestroy(heap->heap_arr);

	free(heap);
	heap = NULL;
}

/******************************************************************************/

int HeapPush(heap_t *heap, const void *data)
{
	size_t cur_index = 0;
	void *parent_data = NULL;

	assert(heap);

	cur_index = VectorSize(heap->heap_arr);

	/* push new element to the buttom of the tree */
	if (VectorPushBack(heap->heap_arr, (void *)data) != 0)
	{
		return (1);
	}

	/* if it is the first element */
	if (cur_index == 0)
	{
		return (0);
	}

	/* heapify tree upwards */
	parent_data = VectorGetElement(heap->heap_arr, (cur_index - 1) / 2);

	/* while data spoused to be upper than its parent */
	while (heap->cmp_func(data, parent_data) > 0)
	{
		/* swap elements */
		VectorSetElement(heap->heap_arr, cur_index, parent_data);
		VectorSetElement(heap->heap_arr, (cur_index - 1) / 2, (void *)data);

		cur_index = (cur_index - 1) / 2;

		/* break if achieving the heap root */
		if (cur_index == 0)
		{
			break;
		}

		parent_data = VectorGetElement(heap->heap_arr, (cur_index - 1) / 2);
	}

	return (0);
}

/******************************************************************************/

void HeapPop(heap_t *heap)
{
	size_t last_element_index = 0;

	assert(heap);

	/* replace root with last element, remove last element */
	last_element_index = VectorSize(heap->heap_arr) - 1;
	VectorSetElement(heap->heap_arr, 0,
					 VectorGetElement(heap->heap_arr, last_element_index));
	VectorPopBack(heap->heap_arr);

	if (!HeapIsEmpty(heap))
	{
		Heapify(heap, 0);
	}
}

/******************************************************************************/

void *HeapPeek(const heap_t *heap)
{
	assert(heap);

	return (VectorGetElement(heap->heap_arr, 0));
}

/******************************************************************************/

size_t HeapSize(const heap_t *heap)
{
	assert(heap);

	return (VectorSize(heap->heap_arr));
}

/******************************************************************************/

int HeapIsEmpty(const heap_t *heap)
{
	assert(heap);

	return (VectorSize(heap->heap_arr) == 0);
}

/******************************************************************************/

void *HeapRemove(heap_t *heap,
				 int (*cond_func)(const void *data,
								  const void *param),
				 const void *param)
{
	void *found_data = NULL;
	size_t i = 0;
	size_t heap_size = 0;

	assert(heap);
	assert(cond_func);

	heap_size = VectorSize(heap->heap_arr);

	/* traverse the tree by levels and check if cond_func is true  */
	for (i = 0; i < heap_size; ++i)
	{
		if (cond_func(VectorGetElement(heap->heap_arr, i), param) == 1)
		{
			found_data = VectorGetElement(heap->heap_arr, i);

			/* copy the data from the last element to the index found */
			VectorSetElement(heap->heap_arr, i,
							 VectorGetElement(heap->heap_arr, heap_size - 1));

			/* remove the older last element */
			VectorPopBack(heap->heap_arr);

			if (!(i == heap_size - 1))
			{
				Heapify(heap, i);
			}

			break;
		}
	}

	return (found_data);
}

/******************************************************************************/
/******************************************************************************
								UTILITY FUNCTIONS
							*************************/

static void Heapify(heap_t *heap, size_t root_index)
{
	/* assuming the root is the largest index */
	size_t largest_index = root_index;
	void *largest_data = NULL;
	size_t left_child_index = 2 * root_index + 1;
	size_t right_child_index = 2 * root_index + 2;
	const size_t heap_size = VectorSize(heap->heap_arr);
	void *temp = NULL;

	assert(!HeapIsEmpty(heap));

	largest_data = VectorGetElement(heap->heap_arr, root_index);

	/* If left child exists and is larger than root */
	if (left_child_index < heap_size &&
		heap->cmp_func(VectorGetElement(heap->heap_arr, left_child_index),
					   largest_data) > 0)
	{
		/* update largest variables */
		largest_index = left_child_index;
		largest_data = VectorGetElement(heap->heap_arr, largest_index);
	}

	/* If right child exists and is larger than largest so far */
	if (right_child_index < heap_size &&
		heap->cmp_func(VectorGetElement(heap->heap_arr, right_child_index),
					   largest_data) > 0)
	{
		/* update largest variables */
		largest_index = right_child_index;
		largest_data = VectorGetElement(heap->heap_arr, largest_index);
	}

	/* If largest is not root */
	if (largest_index != root_index)
	{
		/* swap */
		temp = VectorGetElement(heap->heap_arr, root_index);
		VectorSetElement(heap->heap_arr, root_index, largest_data);
		VectorSetElement(heap->heap_arr, largest_index, temp);


		Heapify(heap, largest_index);
	}
}












