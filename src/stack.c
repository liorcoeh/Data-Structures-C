/*
 * Stack - Functions Definitions
 */

#include <stdlib.h>	/* malloc() free () */
#include <assert.h> /* assert() */

#include "stack.h"

#define ONE_DEFFERNCE 1

/*A structure to represent a stack */
struct stack 
{
    void **stack_base;
 	void **stack_top;
 	size_t size;   
};

stack_t *StackCreate(size_t capacity)
{
	stack_t *stack = (stack_t *)malloc(sizeof(stack_t) + 
						sizeof(void *) * capacity);
	
	stack->stack_base = (void *)(stack + 1);
	stack->stack_top = stack->stack_base;
	stack->size = capacity;
	
	return (stack);  
}

void StackPush(stack_t *stack, void *item)
{
	/*assert(stack-> stack_top < stack->size)*/
	++stack->stack_top;
	*(stack-> stack_top) = item;	
}

void StackPop(stack_t *stack)
{
	/*assert(stack-> stack_top > stack->size)*/
	stack->stack_top--;	
}

void *StackPeek(stack_t *stack)
{
	/* assert((stack-> stack_top - stack_base) > -1)*/
	return(*(stack->stack_top));
}

int StackIsEmpty(stack_t *stack)
{
	return(stack->stack_top == stack->stack_base ? FALSE : TRUE);	
}

size_t StackCapacity(stack_t *stack)
{
	return(stack->size);
}
 
size_t StackSize(stack_t *stack)
{
	return((stack->stack_top - stack->stack_base));
}

void StackDestroy(stack_t *stack)
{
	/*free(stack->stack_base);*/
	free(stack);	
}























