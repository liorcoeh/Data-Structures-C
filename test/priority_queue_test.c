/*
 * Priority Queue - Test File
 */

#include <stdio.h> /* printf() */

#include "priority_queue.h"

/*************************** Utility Functions *******************************/

/*
 * Priority Check: Function to decide the priority of the data
 * Return:
 * - (1) if data1 is higher priority
 * - (0) if both have the same priority
 * - (-1) if data1 is lower priority
 * - Recieve: Pointers to two datas
 */
int PriorityCheck(const void *data1, const void *data2);

/*
 * Conditon Check: Function to decide a condition to erase according to it
 * Return: 1 if the condition checks out, 0 if it's not
 * Recieve: Pointers to two datas
 */
int ConditionCheck(const void *data, const void *param);

/*
 * Print List: Prints the elements in the queue
 * Recieve: Pointer to the queue
 * Time Complexity: O(n)
 * The function is being defined in the priority_queue.c file
 */
void PrintList(pqueue_t *pqueue);

/*****************************************************************************/

int main()
{
	int a = 1;
	int b = 2;
	int c = 3;
	int param = 2;
	
	pqueue_t *main_pqueue = PQueueCreate(PriorityCheck);
	printf("After first creation -\n");
	printf("The queue is empty (1): %d\n", PQueueIsEmpty(main_pqueue));
	printf("The size is (0): %ld\n\n", PQueueSize(main_pqueue));
	
	PQueueEnqueue(main_pqueue, &c);
	PQueueEnqueue(main_pqueue, &a);
	PQueueEnqueue(main_pqueue, &b);
	printf("Enqueu three different datas -\n");
	printf("The queue is not empty (0): %d\n", PQueueIsEmpty(main_pqueue));
	printf("The size is (3): %ld\n", PQueueSize(main_pqueue));
	printf("The prioritized one is (3): %d\n\n", *(int *)PQueuePeek(main_pqueue));
	printf("And the list looks like: \n\n");
	PrintList(main_pqueue);
	
	printf("Dequeu all three elements, one at a time -\n");
	PQueueDequeue(main_pqueue);
	printf("The size is (2): %ld\n", PQueueSize(main_pqueue));
	printf("The prioritized one is (2): %d\n", *(int *)PQueuePeek(main_pqueue));
	
	PQueueDequeue(main_pqueue);
	printf("The size is (1): %ld\n", PQueueSize(main_pqueue));
	printf("The prioritized one is (1): %d\n", *(int *)PQueuePeek(main_pqueue));
	
	PQueueDequeue(main_pqueue);
	printf("The size is (0): %ld\n", PQueueSize(main_pqueue));
	printf("The queue is empty (1): %d\n\n", PQueueIsEmpty(main_pqueue));
	
	printf("Enque 4 new datas - to check the PQueueClear function\n");
	PQueueEnqueue(main_pqueue, &c);
	PQueueEnqueue(main_pqueue, &c);
	PQueueEnqueue(main_pqueue, &c);
	PQueueEnqueue(main_pqueue, &c);
	printf("The size before clear is (4): %ld ", PQueueSize(main_pqueue));
	printf("and the list looks like:\n\n");
	PrintList(main_pqueue);
	PQueueClear(main_pqueue);
	
	printf("The size after clear is (0): %ld ", PQueueSize(main_pqueue));
	printf("and the list looks like:\n\n");	
	PrintList(main_pqueue);
	
	printf("Enqueue 9 more in random order - to check the Erase function\n");
	PQueueEnqueue(main_pqueue, &c);
	PQueueEnqueue(main_pqueue, &a);
	PQueueEnqueue(main_pqueue, &b);
	PQueueEnqueue(main_pqueue, &c);
	PQueueEnqueue(main_pqueue, &a);
	PQueueEnqueue(main_pqueue, &b);
	PQueueEnqueue(main_pqueue, &c);
	PQueueEnqueue(main_pqueue, &a);
	PQueueEnqueue(main_pqueue, &b);
	printf("The size before earse is (9): %ld\n", PQueueSize(main_pqueue));
	printf("Before the list looks like:\n\n");
	PrintList(main_pqueue);
	
	PQueueErase(main_pqueue, ConditionCheck, &param);
	printf("The size after is (8): %ld\n", PQueueSize(main_pqueue));
	printf("After the list looks like:\n\n");	
	PrintList(main_pqueue);
	
	PQueueDestroy(main_pqueue);

	return (0);
}

/******************************************************************************/
/******************************************************************************/

int PriorityCheck(const void *data1, const void *data2)
{
	if (*(int *)data1 > *(int *)data2)
	{
		return (1);
	}
	else if (*(int *)data1 == *(int *)data2)
	{
		return (0);
	}
	else
	{
		return (-1);
	}
}

/******************************************************************************/

int ConditionCheck(const void *data, const void *param)
{
	if (*(int *)data == *(int *)param)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/******************************************************************************/












