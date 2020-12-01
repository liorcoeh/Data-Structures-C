/*
 * Dynamic Vector
 */

#ifndef DYNAMIC_VECTOR_H
#define DYNAMIC_VECTOR_H 

#include <stddef.h> /* size_t */

/* dynamic vector struct type defenition */
typedef struct dynamic_vector vector_t;

/******************************************************************************/

/* Vector Create: */
/* Recieve: the initial capacity for the vector (size_t) 					*/
/* Return: pointer to a new Dynamic vector struct		 					*/
/* Errors: return NULL if can't allocate memory for the struct or the array */
vector_t *VectorCreate(size_t capacity);

/* Vector destroy: */
/* Recieve: pointer to a vector struct 								*/
/* Action: Free the memory allocated for the struct and the array	*/
void VectorDestroy(vector_t *vector);

/* Vector Push Back: */
/* Recieve: 1. pointer to dynamic vector; 2. pointer to element)	*/
/* Action: Push the element to the back of the vector				*/
/* Return: exit status 0 for success, 1 for failure		 			*/
int VectorPushBack(vector_t *vector, void *element);

/* Vector pop back: */
/* Recieve: pointer to a vector struct 			*/
/* Action: remove the last element in the array	*/
void VectorPopBack(vector_t *vector);

/* Vector Shrink To Fit: */
/* Recieve: pointer to dynamic vector					 */
/* Action: Shrink vector's capacity to fit vector's size */
/* Return: exit status 0 for success, 1 for failure		 */
int VectorShrinkToFit(vector_t *vector);

/* Vector Set Element: */
/* Recieve: 1. pointer to a vector struct; 2. requested index (unsigned int); */
/* 			3. pointer to a new element							    		  */
/* Action: sets the index to the new element received						  */
void VectorSetElement(vector_t *vector, unsigned int index, void *element);

/* Vector Get Element: */
/* Recieve: 1. pointer to a vector struct; 2. requested index (unsigned int); */
/* return: void pointer to the element requested by index					  */
void *VectorGetElement(vector_t *vector, unsigned int index);

/* Vector Capacity: */
/* Recieve: pointer to a vector struct 	*/
/* Return: vector's capacity		 	*/
size_t VectorCapacity(vector_t *vector);

/* Vector Size: */
/* Recieve: pointer to a vector struct 	*/
/* Return: vector's size			 	*/
size_t VectorSize(vector_t *vector);

/* Vector Reserve: */
/* Recieve: 1. pointer to dynamic vector; 2. new requested capacity (size_t) */
/* Action: change vector's capacity to a new capcity requested. 			 */
/* Return: exit status 0 for success, 1 for failure							 */
int VectorReserve(vector_t *vector, size_t new_capacity);

#endif /* DYNAMIC_VECTOR_H */














