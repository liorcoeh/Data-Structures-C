/*
 * Stack
 */

#ifndef STACK_H
#define STACK_H

#include <stdio.h>	/* size_t */

enum results {FALSE, TRUE};

typedef struct stack stack_t;

/* Function to create a stack of given capacity 			*/
/* Gets the stack size. Will return NULL in case of failure	*/
stack_t *StackCreate(size_t size);

/* Destoryes the stack data structure */
void StackDestroy(stack_t *stacko);

/* Takes out the element from the stack */
void StackPop(stack_t *stacko);

/* Puts in the element */
void StackPush(stack_t *stacko, void *item);

/* Shows the element */
void *StackPeek(stack_t *stacko);

/* Gets the amount of elements in the stack */
size_t StackSize(stack_t *stacko);

/* Finds if the stack is empty */
int StackIsEmpty(stack_t *stacko);

/* Gives the size of the stack */
size_t StackCapacity(stack_t *stacko);

#endif /* STACK_H */










