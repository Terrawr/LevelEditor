#include "Stack.h"
#include <stdlib.h>
#include <malloc.h>



void* initializeStack(size_t size, size_t esize, typedependency* func)
{
	Stack* stack = (Stack*)malloc(sizeof(Stack) + size);
	if (stack == NULL)
		return NULL; //Error Occoured;
	stack->memory = stack + sizeof(Stack);
	stack->size = size;
	stack->cursor = -1;
	stack->functor = func;
	stack->elementsize = esize;

	return ((void*)stack);
}

void deconstructStack(struct Stack* stack)
{
	free(stack);
	return;
}

void* pop(struct Stack* stack) {

	void* value = malloc(stack->elementsize);
	if (value == NULL)
		return NULL;//error
	if (isEmpty(stack) == TRUE)
		return NULL;//Error				
					/////////////////////////////////////////

	stack->functor(POP, stack, value);
	return value;
}

void* push(struct Stack* stack, void* data) {

	if (isFull(stack) == FALSE)
		return NULL; //error
	if (data == NULL)
		return NULL; //error

	stack->functor(PUSH, stack, data);
	return (void*)stack;
}

void* peek(struct Stack* stack) {

	void* value = malloc(stack->elementsize);
	if (value == NULL)
		return NULL; //error

	stack->functor(PEEK, stack, value);
	return value;
}

int isEmpty(struct Stack* stack) {
	return stack->cursor < 0;
}

int isFull(struct Stack * stack)
{
	return stack->size >= stack->size - 1;
}

void clearStack(struct Stack * stack)
{
	stack->cursor = -1;
}