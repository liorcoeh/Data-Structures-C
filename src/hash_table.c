/*
 * Hash Table - Functions Defintions
 */

#include <stdio.h>	/* printf()	*/
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <math.h>	/* pow(), sqrt() */

#include "hash_table.h"
#include "doubly_linked_list.h"

#define GetHashedIndex(hash, data) ((hash)->hash_func(data) % \
									 (hash)->table_size)
#define KEY (hash->table[key])
#define SQAURE (2)

struct hash_table
{
    size_t(*hash_func)(const void *data);
    int(*cmp_func)(const void *data1, const void *data2);
    dll_t **table;
    size_t table_size;
};

/******************************************************************************/
/******************************************************************************
								UTILITY FUNCTIONS
							*************************/


/******************************************************************************/
/******************************************************************************
								  MAIN FUNCTIONS
							*************************/

hash_t *HashCreate(int (*cmp_func)(const void *data1, const void *data2),
				   size_t (*hash_func)(const void *data),
				   size_t table_size)
{
	hash_t *new_hash_table = NULL;
	size_t i = 0;

	assert(cmp_func);
	assert(hash_func);
	assert(table_size != 0);

	new_hash_table = (hash_t *)malloc(sizeof(hash_t));

	if (!new_hash_table)
	{
		return (NULL);
	}

	new_hash_table->table = (dll_t **)malloc(sizeof(dll_t **) * table_size);

	if (!new_hash_table->table)
	{
		free(new_hash_table);
		new_hash_table = NULL;

		return (NULL);
	}

	new_hash_table->cmp_func = cmp_func;
	new_hash_table->hash_func = hash_func;
	new_hash_table->table_size = table_size;

	/* Creating DLList for each "key" and making sure they are created */
	for (i = 0; i < table_size; ++i)
	{
		new_hash_table->table[i] = DLLCreate();

		if (!new_hash_table->table[i])
		{
			for (; i != 0; --i)
			{
				DLLDestroy(new_hash_table->table[i]);
				new_hash_table->table[i] = NULL;
			}

			free(new_hash_table->table);
			new_hash_table->table = NULL;

			free(new_hash_table);
			new_hash_table = NULL;

			return (NULL);
		}
	}

	return (new_hash_table);
}

/******************************************************************************/

void HashDestroy(hash_t *hash)
{
	size_t index = 0;

	assert(hash);

	for (index = 0; index < hash->table_size; ++index)
	{
		DLLDestroy(hash->table[index]);
		hash->table[index] = NULL;
	}

	free(hash->table);
	hash->table = NULL;

	free(hash);
	hash = NULL;
}

/******************************************************************************/

int HashInsert(hash_t *hash, void *data)
{
	size_t key = 0;
	dll_iter_t status = NULL;
	dll_t *list_of_key = NULL;

	assert(hash);
	assert(data);

	key = GetHashedIndex(hash, data);
	list_of_key = KEY;

	status = DLLPushBack(list_of_key, data);

	/* DLLPushBack returns the last element of the list if failed */
	return (status == DLLEnd(list_of_key) ? 1 : 0);
}

/******************************************************************************/

size_t HashSize(const hash_t *hash)
{
	size_t key = 0;
	size_t count = 0;

	assert(hash);

	for (key = 0; key < hash->table_size; ++key)
	{
		count += DLLSize(KEY);
	}

	return (count);
}

/******************************************************************************/

int HashIsEmpty(const hash_t *hash)
{
	assert(hash);

	return (0 == HashSize(hash));
}

/******************************************************************************/

void HashRemove(hash_t *hash, const void *data)
{
	size_t key = 0;
	dll_t *list_of_key = NULL;
	dll_iter_t iter = NULL;

	assert(hash);
	assert(data);

	key = GetHashedIndex(hash, data);
	list_of_key = KEY;

	for (iter = DLLBegin(list_of_key);
		 !DLLIsSameIter(iter, DLLEnd(list_of_key));
		 iter = DLLNext(iter))
	{
		if (hash->cmp_func(data, DLLGetData(iter)) == 0)
		{
			DLLRemove(iter);

			break;
		}
	}
}

/******************************************************************************/

void *HashFind(const hash_t *hash, const void *data)
{
	size_t key = 0;
	dll_t *list_of_key = NULL;
	dll_iter_t iter = NULL;
	void *found_data;

	assert(hash);
	assert(data);

	key = GetHashedIndex(hash, data);
	list_of_key = KEY;

	for (iter = DLLBegin(list_of_key);
		 !DLLIsSameIter(iter, DLLEnd(list_of_key));
		 iter = DLLNext(iter))
	{
		if (hash->cmp_func(data, DLLGetData(iter)) == 0)
		{
			found_data = DLLGetData(iter);

			if (iter != DLLBegin(list_of_key))
			{
				if (DLLPushFront(list_of_key, found_data) !=
					DLLEnd(list_of_key))
				{
					DLLRemove(iter);

				}
			}

			return (found_data);
		}
	}

	return (NULL);
}

/******************************************************************************/

int HashForEach(hash_t *hash,
				int (*op_func)(void *data, const void *param),
				const void *param)
{
	size_t key = 0;
	dll_t *list_of_key = NULL;
	dll_iter_t iter = NULL;
	int status = 0;

	assert(hash);
	assert(op_func);

	/* iterate the array of lists */
	for (key = 0; key < hash->table_size; ++key)
	{
		list_of_key = KEY;

		/* iterate the list of index i */
		for (iter = DLLBegin(list_of_key);
			 !DLLIsSameIter(iter, DLLEnd(list_of_key));
			 iter = DLLNext(iter))
		{
			status = op_func(DLLGetData(iter), param);

			if (status != 0)
			{
				return (status);
			}
		}
	}

	return (0);
}

/******************************************************************************/

double HashLoad(hash_t *hash)
{
	double hash_load = 0;
	
	assert(hash);

	hash_load = (double)HashSize(hash) / (double)hash->table_size;

	return (hash_load);
}

/******************************************************************************/

double HashSD(hash_t *hash)
{
	size_t key = 0;
	double average = 0;
	double total_pow_sum = 0;
	size_t list_size = 0;
	

	assert(hash);

	average = HashLoad(hash);

	for (key = 0; key < hash->table_size; ++key)
	{
		list_size = DLLSize(KEY);
		total_pow_sum += pow(list_size - average, 2);
	}

	total_pow_sum /= hash->table_size;

	return (sqrt(total_pow_sum));
}








