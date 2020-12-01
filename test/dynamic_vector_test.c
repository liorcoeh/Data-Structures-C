/*
 * Dynamic Vector - Test File
 */


#include <stdio.h> /* printf, fprintf */

#include "dynamic_vector.h"

/******************************************************************************/

int main()
{
	vector_t *my_vector = NULL; 
	int var1 = 5;
	int var2 = 234;
	int var3 = 432;
	int var4 = 700;
	int status = 0;

	printf("************** Dynamic vector DS Tests: **************\n\n");
	my_vector = VectorCreate(3);

	if (NULL == my_vector)
	{
		fprintf(stderr, "VectorCreate failed: can't allocate memory\n");
		return (1);
	}

	printf("** Check if empty when created: **\n");
	printf("vector capacity: %lu\n", VectorCapacity(my_vector));
	printf("vector size:     %lu\n\n", VectorSize(my_vector));

	printf("** 3 elements pushed: **\n");
	status = VectorPushBack(my_vector, &var1);
	printf("var1 value: %d, status: %d\n", var1, status);
	status = VectorPushBack(my_vector, &var2);
	printf("var2 value: %d, status: %d\n", var2, status);
	status = VectorPushBack(my_vector, &var3);
	printf("var3 value: %d, status: %d\n\n", var3, status);

	printf("vector capacity: %lu\n", VectorCapacity(my_vector));
	printf("vector size:     %lu\n\n", VectorSize(my_vector));

	printf("** get the elements from the vector by index: **\n");
	printf("0. %d\n", *(int *)VectorGetElement(my_vector, 0));
	printf("1. %d\n", *(int *)VectorGetElement(my_vector, 1));
	printf("2. %d\n\n", *(int *)VectorGetElement(my_vector, 2));

	status = VectorPushBack(my_vector, &var4);
	printf("** another element pushed to check the resize: **\n");
	printf("var4 value: %d, status: %d\n\n", var4, status);

	printf("** get the element from the vector by index: **\n");
	printf("3. %d\n\n", *(int *)VectorGetElement(my_vector, 3));

	printf("vector capacity: %lu\n", VectorCapacity(my_vector));
	printf("vector size:     %lu\n\n", VectorSize(my_vector));

	VectorPopBack(my_vector);

	printf("** check the size when pop the last element: **\n");
	printf("vector capacity: %lu\n", VectorCapacity(my_vector));
	printf("vector size:     %lu\n\n", VectorSize(my_vector));

	status = VectorShrinkToFit(my_vector);

	printf("** check the size and capacity when shring to fit: **\n");
	printf("vector capacity: %lu\n", VectorCapacity(my_vector));
	printf("vector size:     %lu\n", VectorSize(my_vector));
	printf("status:          %d\n\n", status);

	VectorSetElement(my_vector, 2, &var1);

	printf("** set element at index 2 to var 1: **\n");
	printf("%d\n", *(int *)VectorGetElement(my_vector, 0));
	printf("%d\n", *(int *)VectorGetElement(my_vector, 1));
	printf("%d\n\n", *(int *)VectorGetElement(my_vector, 2));

	printf("** reserve place for new 80 elements: **\n");
	status = VectorReserve(my_vector, 80);
	printf("vector capacity: %lu\n", VectorCapacity(my_vector));
	printf("vector size:     %lu\n\n", VectorSize(my_vector));

	VectorDestroy(my_vector);

	return (0);
}













