/*
 * Stack - Test File
 */

#include "stack.h"

stack_t *stacko;

int main() 
{	
	size_t size = 10;
	int n1 = 6;
	int n2 = 5;
	int n3 = 4;
	float fl = 11.2;
	char c[10] = "hello";

    stacko = StackCreate(size);
    
    printf("The capacity of the stack is: %ld\n\n",StackCapacity(stacko));
    
    if(StackIsEmpty(stacko))
    {
    	printf("The stack is empty - Right!\n\n");
    }
    else
    {
    	printf("The stack is not-empty - WRONG!!\n");
    }
    
    StackPush(stacko, &n1);
    printf("The size of the stack is %ld\n", StackSize(stacko));
    
    StackPush(stacko, &n2);
    printf("The size of the stack is %ld\n", StackSize(stacko));
    
	StackPush(stacko, &n3);
	printf("The size of the stack is %ld\n", StackSize(stacko));

	StackPop(stacko);
    printf("The size of the stack is %ld\n", StackSize(stacko));

    StackPop(stacko);
    printf("The size of the stack is %ld\n\n", StackSize(stacko));

	if(StackIsEmpty(stacko))
    {
    	printf("The stack is empty - WRONG!!\n");
    }
    else
    {
    	printf("The stack is not-empty - Right!\n\n");
    }

	StackDestroy(stacko);

    return 0; 
} 


