/*
 * Queue - Test File
 */

#include <stdio.h> /* printf */

#include "queue.h"

int main()
{	
	int first1 = 1;
	int first2 = 2;
	int first3 = 3;
	int second1 = 10;
	int second2 = 20;
	
	queue_t *first_queue;
	queue_t *second_queue;
	first_queue = QueueCreate();
	second_queue = QueueCreate();
	
	printf("Both lists are empty:\n");
	printf("First is Empty: %s\n", QueueIsEmpty(first_queue) ? "yes" : "no");
	printf("Second is Empty: %s\n", QueueIsEmpty(second_queue) ? "yes" : "no");
	printf("\n");
	
	printf("Add three elements to first one\n");
	QueueEnqueue(first_queue, &first1);
	QueueEnqueue(first_queue, &first2);
	QueueEnqueue(first_queue, &first3);
	
	printf("First is Empty: %s\n", QueueIsEmpty(first_queue) ? "yes" : "no");
	printf("Second is Empty: %s\n", QueueIsEmpty(second_queue) ? "yes" : "no");
	printf("\n");
	
	printf("Add two elements to second one\n");
	QueueEnqueue(second_queue, &second1);
	QueueEnqueue(second_queue, &second2);
	printf("Amount of elements in first: %lu\n", QueueSize(first_queue));
	printf("Amount of elements in second: %lu\n", QueueSize(second_queue));
	printf("\n");
	
	printf("Element in second one is: %d\n", *(int *)QueuePeek(second_queue));
	printf("\n");
	
	printf("Before append the amount of elements ");
	printf("in first is: %lu\n", QueueSize(first_queue));
	QueueAppend(first_queue, second_queue);
	printf("After the append the amount is: %lu\n", QueueSize(first_queue));
	printf("and the element before dequeue is: ");
	printf("%d\n", *(int *)QueuePeek(first_queue));
	printf("\n");
	
	QueueDequeue(first_queue);
	QueueDequeue(first_queue);
	
	printf("After two dequeues the ");
	printf("amount of elements in first: %lu\n", QueueSize(first_queue));
	printf("The element found in first: %d\n", *(int *)QueuePeek(first_queue));
	
	QueueDequeue(first_queue);
	printf("Amount of elements in first: %lu\n", QueueSize(first_queue));

	
	QueueDestroy(first_queue);
	
	return (0);
}












