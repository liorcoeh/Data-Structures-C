/*
 * Circular Buffer - Functions Definitions
 */

#include <stdlib.h> /* malloc(), free() */
#include <assert.h> /* assert() */

#include "circular_buffer.h"

#pragma pack(push, 1)

/* The menager struct
 * front - Index to to the place to write in
 * size - The amount of occupied space
 * cap - Short for 'capacity' - holds the total amount of space
 * arr - Flexible array that will hold the data in it
 */
struct circular_buffer
{
	size_t front;
	size_t size;
	size_t cap;
	char arr[1];
};

#pragma pack(pop)


cb_t *CBCreate(size_t capacity)
{
	cb_t *new_cb = NULL;
	new_cb = (cb_t *)malloc(sizeof(cb_t) + (sizeof(char) * (capacity - 1)));
	
	if (NULL == new_cb)
	{
		return(NULL);
	}
	
	new_cb->front = 0;
	new_cb->size = 0;
	new_cb->cap = capacity;
	
	return(new_cb);
}

/******************************************************************************/

void CBDestroy(cb_t *cb)
{
	free(cb);
	cb = NULL;
}

/******************************************************************************/

size_t CBSize(cb_t *cb)
{
	assert(cb);
	return (cb->size);
}

/******************************************************************************/

size_t CBFreeSpace(cb_t *cb)
{
	assert(cb);
	return (cb->cap - cb->size);
}

/******************************************************************************/

bool CBIsEmpty(cb_t *cb)
{
	assert(cb);
	return (cb->size == 0 ? TRUE : FALSE);	
}

/******************************************************************************/

size_t CBCapacity(cb_t *cb)
{
	assert(cb);
	return (cb->cap);
}

/******************************************************************************/

ssize_t CBWrite(cb_t *cb, const void *buf, size_t count)
{
	char *new_buf = (char *)buf;
	size_t num_of_bytes_written = 0;
	
	assert(cb);
	assert(buf);
		
	if (0 == CBFreeSpace(cb))
	{
		return (ERROR);
	}
	
	/* As long as count isn't zero or the circular buffer isn't full */
	for (;0 != count && CBFreeSpace(cb); --count) 
	{
		cb->arr[cb->front % cb->cap] = *new_buf;
		++new_buf;
		++cb->front;
		++cb->size;
		++num_of_bytes_written;
	}
	
	return (num_of_bytes_written);
}

/******************************************************************************/

ssize_t CBRead(cb_t *cb, void *buf, size_t count)
{
	char *new_buf = (char *)buf;
	size_t num_of_bytes_read = 0;
	
	assert(cb);
	assert(buf);
	
	for (;0 != count; --count)
	{
		if (0 == cb->size)
		{
			return (num_of_bytes_read);
		}
		*new_buf = cb->arr[(cb->cap + cb->front - cb->size) % cb->cap];
		--cb->size;
		++new_buf;
		++num_of_bytes_read;
	}
	
	return (num_of_bytes_read);
}









