/****************************************************************************
* File Name: DynamicVector_test.c											*
* Writer: Lior Cohen														*
* Date: 27/02/2020														    *
* Purpose: Tests the functions for the dynamic vector assignement			*
* Code reviewer: Lucy Volkov												*
*****************************************************************************/

#include "DynamicVector.h"

vector_t *main_vector;

int main() 
{	
	size_t size = 3;
	int n1 = 1;
	int n2 = 5;
	float fl = 11.2;
	char c[21] = "Hello, how do you do?";
	
	size_t new_capacity = 20;
		
	main_vector = VectorCreate(size);
	
	printf("\nThe starting vector capacity should be 3 ");
	printf("and it is: %ld\n\n", VectorCapacity(main_vector));
	
	printf("After 2 pushes the size should be 2 ");
	VectorPushBack(main_vector, &n1);
	VectorPushBack(main_vector, &fl);
	printf("and it is: %ld\n\n", VectorSize(main_vector));
	
	printf("The elements should be 1 in the (0) index and (11.20) ");
	printf("in the (1) index\n");
	printf("They are: %d and %0.2f\n\n", *((int *)VectorGetElement
			(main_vector, 0)), *((float *)VectorGetElement(main_vector, 1)));
	
	printf("After 2 more pushes, the capcity should be 6 and the size 4\n");
	VectorPushBack(main_vector, c);
	VectorPushBack(main_vector, &n2);
	printf("The capcity is %ld ", VectorCapacity(main_vector));
	printf("and the size is: %ld\n\n", VectorSize(main_vector));
	
	printf("Resereve capacity should change the capacity to 20\n");
	VectorReserve(main_vector, new_capacity);
	printf("And it is: %ld\n\n", VectorCapacity(main_vector));
	
	printf("After 1 push and 2 pops, the size should be 3 and the element \n");
	printf("in the (2) index should be: Hello, how do you do?\n\n");
	VectorPushBack(main_vector, &n1);
	VectorPopBack(main_vector);
	VectorPopBack(main_vector);
	printf("The size is: %ld ", VectorSize(main_vector));
	printf("and the item is: %s\n\n", ((char *)VectorGetElement
			(main_vector, 2)));
	
	printf("Before shrink, the capacity is 20, after it will be 3\n");
	VectorShrinkToFit(main_vector);
	printf("and it is: %ld\n\n", VectorCapacity(main_vector));
	
	VectorDestroy(main_vector);
	
	return (0);	
}
