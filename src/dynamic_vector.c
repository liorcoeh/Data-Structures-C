/*
 * Dynamic Vector - Functions Definitions
 */

#include <stdlib.h> /* malloc, realloc */
#include <assert.h> /* assert */

#include "dynamic_vector.h"

#define SUCCESS (0)
#define FAILURE (1)

/******************************************************************************/

struct dynamic_vector
{
	void **array;	 /* vector array pointer 	*/
	size_t capacity; /* vector current capacity */
	size_t size;	 /* vector current size	    */
};

/******************************************************************************/
/******************************************************************************
								 MAIN FUNCTIONS
						   *************************/

vector_t *VectorCreate(size_t capacity)
{
	/* allocate memory for the struct */
	vector_t *new_vector = (vector_t *)malloc(sizeof(vector_t));

	assert(capacity > 0);

	if (NULL == new_vector)
	{
		return (NULL);
	}

	/* allocate memory for the array itself */
	new_vector->array = (void **)malloc(sizeof(void *) * capacity);

	if (NULL == new_vector->array)
	{
		return (NULL);
	}

	/* save the capacity in the struct for later use */
	new_vector->capacity = capacity;

	new_vector->size = 0; /* initialaize array size */

	return (new_vector);
}

/******************************************************************************/

int VectorPushBack(vector_t *vector, void *element)
{
	int status = SUCCESS;

	assert(NULL != vector);
	assert(NULL != element);

	/* if the vector is full */
	if (vector->size == vector->capacity)
	{
		/* reserve new double space for the vector */
		status = VectorReserve(vector, (vector->capacity) * 2);
	}

	if (status == SUCCESS)
	{
		/* add one to size: */
		++vector->size;

		/* assign the element to the back of the vector: */
		vector->array[vector->size - 1] = element;
	}
	else
	{
		return (FAILURE);
	}

	return (SUCCESS);
}

/******************************************************************************/

void *VectorGetElement(vector_t *vector, unsigned int index)
{
	assert(vector != NULL);
	assert(index < vector->size);

	return (vector->array[index]);
}

/******************************************************************************/

int VectorReserve(vector_t *vector, size_t new_capacity)
{
	void **array = NULL;

	assert(NULL != vector);
	assert(new_capacity > 0);

	/* reallocate memory for the array */
	array = (void **)realloc(vector->array, (new_capacity * sizeof(void *)));

	if (NULL == array)
	{
		return (FAILURE);
	}

	/* assign the new allocated memory to the array member of the struct */
	vector->array = array;
	vector->capacity = new_capacity;

	return (SUCCESS);
}

/******************************************************************************/

void VectorDestroy(vector_t *vector)
{
	assert(NULL != vector);

	free(vector->array);
	vector->array = NULL;
	free(vector);
	vector = NULL;
}

/******************************************************************************/

void VectorPopBack(vector_t *vector)
{
	assert(NULL != vector);

	/* subtract the size to ignore the last index's value */
	--vector->size;
}

/******************************************************************************/

size_t VectorCapacity(vector_t *vector)
{
	assert(NULL != vector);

	return (vector->capacity);
}

/******************************************************************************/

size_t VectorSize(vector_t *vector)
{
	assert(NULL != vector);

	return (vector->size);
}

/******************************************************************************/

int VectorShrinkToFit(vector_t *vector)
{
	/* reserve new capcaity by the size of the vector */
	int status = VectorReserve(vector, vector->size);

	assert(NULL != vector);

	return (status);
}

/******************************************************************************/

void VectorSetElement(vector_t *vector, unsigned int index, void *element)
{
	assert(NULL != vector);
	assert(NULL != element);
	assert(index < vector->size);

	vector->array[index] = element;
}














