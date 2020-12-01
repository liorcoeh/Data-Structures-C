/*
 * Hash Table
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef struct hash_table hash_t;

/*
 * Hash Create: Creates a new hash table
 * Return: Pointer to the new hash table
 * Receive:
 * - int(*cmp_func) - Pointer to a comparing function. This function
 *					  Return:  0 if both datas are the same
 *						       1 if they are not the same
 *					  Receive: const void * - pointer to the first data
 *							   const void * - pointer to the second data
 *
 * - size_t(*hash_func) - Pointer to the hash function. This function
 *					  Return:  The key to use for storing the data
 *					  Receive: const void * - Pointer to the data to be stored
 *
 * - size_t - The size of the hash table to create
 * Time Complexity: O(1)
 */
hash_t *HashCreate(int(*cmp_func)(const void *data1, const void *data2),
				   size_t(*hash_func)(const void *data),
				   size_t table_size);

/*
 * Hash Destroy: Frees all the memory being used by the hash table
 * Receive: hash_t * - Pointer to the hash table
 * Time Complexity: O(n+k) - k is the number of nodes in a list
 */
void HashDestroy(hash_t *hash);

/*
 * Hash Insert: Insert new data into the hash table
 * Return: 0 for success, 1 for failure
 * Receive:
 * - hash_t * - Pointer to the hash table
 * - void * - Pointer to the data to be sotred
 * Time Complexity: O(1)
 */
int HashInsert(hash_t *hash, void *data);

/*
 * Hash Remove: Removes a certain data from the hash table
 * Receive:
 * - hash_t * - Pointer to the hash table
 * - const void * - Pointer to the data to be removed
 * Time Complexity: O(1)
 */
void HashRemove(hash_t *hash, const void *data);

/*
 * Hash Size: Gets the amount of elements in the hash table
 * Return: The the amount of elements in the hash table
 * Receive: const hash_t * - Pointer to the hash table
 * Time Complexity: O(n+k) - k the number of nodes in a list
 */
size_t HashSize(const hash_t *hash);

/*
 * Hash Is Empty: Checks if the hash table is empty
 * Return: 1 if it is empty, 0 if it's not
 * Receive: const hash_t * - Pointer to the hash table
 * Time Complexity: O(n+k) - k the number of nodes in a list
 */
int HashIsEmpty(const hash_t *hash); 

/*
 * Hash For Each: Does an operation on each data in the hash table
 * Return: 0 if success, 1 if a failure
 * Receive:
 * - hast_t * - Pointer to the hash table
 * - int(*op_func) - The operation function. This function
 *				Receive: void * - Pointer to the data to operate on
 *						 void * - Pointer to a parameter to be used
 * - void * - Pointer to the parameter to be used in the op_func
 * Time Complexity: O(n+k) - k the number of nodes in a list
 */
int HashForEach(hash_t *hash,
				int(*op_func)(void *data, const void *param),
				const void *param);

/*
 * Hash Find: Finds if a certain data exists in the hash table, if it it will
 *			  move the data to the begining of the list - cashing
 * Return: Pointer to the data if found. Will return NULL if isn't found
 * Receive:
 * - hash_t * - Pointer to the hash table
 * - const void * - Pointer to the data to be found
 * Time Complexity: O(1)
 */
void *HashFind(const hash_t *hash, const void *data);

/*
 * Hash Load: A function to get the hash table load factor
 * Return: The hash table's load factor
 * Receive: const hash_t * - Pointer to the hash table
 * Time Complexity: O(1)
 */
double HashLoad(hash_t *hash);

/*
 * Hash SD: Standard Deviation. Gives the standard deviation of the hash table
 * Return: The standard deviation of the hash table
 * Receive: const hast_t * - Pointer to the hash table
 * Time Complexity: O(1)
 */
double HashSD(hash_t *hash);

#endif /* HASH_TABLE_H */










