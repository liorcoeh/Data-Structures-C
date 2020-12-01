/*
 * Circular Buffer - Test File
 */

#include <stdio.h>

#include "circular_buffer.h"
#include "utility.h"

int main()
{
	size_t capacity = 15;
	size_t write_count = 10;
	size_t read_count = 5;
	ssize_t num_write = 0;
	ssize_t num_read = 0;
	
	char *str1 = "hello world";
	char str2[15] = {0};
	
	cb_t *main_cb;
	main_cb = CBCreate(capacity);
	
	printf("The capacity of the circular buffer is: ");
	printf("%ld\n\n", CBCapacity(main_cb));
	
	/**************** Checking after circular buffer creation ****************/
	printf("The amount of elements in the circular buffer is: ");
	printf("%lu\n", CBSize(main_cb));
	if (1 == CBIsEmpty(main_cb))
	{
		printf("The circular buffer is empty\n");
	}
	else
	{
		printf("The circular buffer is NOT empty\n");
	}
	printf("The amount of free space in the circular buffer is: ");
	printf("%ld\n", CBFreeSpace(main_cb));
	printf("\n");
	
	/************ Checking after writing into the circular buffer ************/
	num_write = CBWrite(main_cb, str1, write_count);
	
	printf("After writing %ld times into the buffer:\n", write_count);
	printf("The amount of elements in the circular buffer is: ");
	printf("%lu\n", CBSize(main_cb));
	if (1 == CBIsEmpty(main_cb))
	{
		printf("The circular buffer is empty\n");
	}
	else
	{
		printf("The circular buffer is NOT empty\n");
	}
	printf("The amount of free space in the circular buffer is: ");
	printf("%ld\n", CBFreeSpace(main_cb));
	printf("The number of bytes written into the circular buffer is: ");
	printf("%ld\n", num_write);
	printf("\n");
	
	/************ Checking after reading from the circular buffer ************/
	num_read = CBRead(main_cb, str2, read_count);
		
	printf("After reading %ld times from the buffer:\n", write_count);
	printf("The amount of elements in the circular buffer is: ");
	printf("%lu\n", CBSize(main_cb));
	if (1 == CBIsEmpty(main_cb))
	{
		printf("The circular buffer is empty\n");
	}
	else
	{
		printf("The circular buffer is NOT empty\n");
	}
	printf("The amount of free space in the circular buffer is: ");
	printf("%ld\n", CBFreeSpace(main_cb));
	printf("The number of bytes read from the circular buffer is: ");
	printf("%lu\n", num_read);
	printf("\n");
	
	/*** Checking after wrting to the circular buffer - more then capacity ***/
	write_count = 20;
	num_write = CBWrite(main_cb, str1, write_count);
	printf("After writing more times than the capacity:\n");
	
	printf("The amount of elements in the circular buffer is: ");
	printf("%lu\n", CBSize(main_cb));
	if (1 == CBIsEmpty(main_cb))
	{
		printf("The circular buffer is empty\n");
	}
	else
	{
		printf("The circular buffer is NOT empty\n");
	}
	printf("The amount of free space in the circular buffer is: ");
	printf("%ld\n", CBFreeSpace(main_cb));
	printf("The number of bytes written into the circular buffer is: ");
	printf("%lu\n", num_write);
	printf("\n");
	
	/** Checking after reading from the circular buffer - more then capacity **/
	read_count = 25;
	num_read = CBRead(main_cb, str2, read_count);
		
	printf("After reading more times than the capcity:\n");
	printf("The amount of elements in the circular buffer is: ");
	printf("%lu\n", CBSize(main_cb));
	if (1 == CBIsEmpty(main_cb))
	{
		printf("The circular buffer is empty\n");
	}
	else
	{
		printf("The circular buffer is NOT empty\n");
	}
	printf("The amount of free space in the circular buffer is: ");
	printf("%ld\n", CBFreeSpace(main_cb));
	printf("The number of bytes read from the circular buffer is: ");
	printf("%lu\n", num_read);
	printf("\n");
	
	CBDestroy(main_cb);

	return (0);
}
