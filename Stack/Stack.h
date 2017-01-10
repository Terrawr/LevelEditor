#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef enum {
	POP,
	PUSH,
	PEEK
}STACKOPERATION;

typedef struct Stack Stack;

#define TYPE_DEPENDEND_FUNCTION(name) void name(STACKOPERATION op,struct Stack* stack,void* value)
typedef TYPE_DEPENDEND_FUNCTION(typedependency);


typedef struct Stack {
	void* memory;
	int   cursor;
	int   size;
	int   elementsize;
	typedependency* functor;
} Stack;


//Initialize a Stack with the actuall size, the size of the element which should be stored
//and a functionpointer which knows how to handle the type of the element for all legal stack
//operations
void* initializeStack(size_t size, size_t esize, typedependency* func);

//Destroys the stack by freeing allocated memory of the stack
void  deconstructStack(struct Stack*);

//Pops the element of the stack where the current cursor stands.
//WARNING: the value returned by Pop is a pointer of void but with
//allocated memory of the size of the element stored in the stack
//after coping the VALUE the void* MUST BE FREEED by hand from the
//User!!!!
void* pop(struct Stack*);

//Pushs an element onto the Stack. It moves the current cursor + 1 and
//stores the new data at the oldposition plus one.
void* push(struct Stack*, void* data);

//Like Pop but no element will be removed and only the next element after
//the current element will be returned
void* peek(struct Stack*);

//I hope self explanatory 
int isEmpty(struct Stack*);
int isFull(struct Stack*);

//Deletes the stack content by simply moving the stacks cursor to position
//of -1. 
void clearStack(struct Stack*);




#ifdef __cplusplus
}
#endif