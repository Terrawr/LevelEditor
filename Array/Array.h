#pragma once
typedef const void const* ConstIterator;
typedef void*			  Iterator;
typedef void*			  Any;
typedef void**			  Data;

//Function Pointer
typedef int unary_predicate(Any value);
typedef int binary_predicate(Any lhs, Any rhs);

typedef struct ElementMetaData {

	int				type;
	int				typesize;
	char*			type_name;
	Data			ReferenceTableToData; //You Iterator through this here!!!!
}Element;

typedef struct ManagedArray {
	Iterator BeginIter,
		EndIter,
		CursorIter;

	int    CurrentCapacity;  //private Max Offset

	int    ArraySize;		//public Max Offset. May not exceed CurrentCapacity
	int    CurrentUse;		//Offset to the latest added Element

	Element ManagedData;			//contains the actuall data stored as Pointer of Pointer of Void ( void** )
}Array;

//Initialize an Managed Array
Array* InitilaizeArray(Iterator startadress, int size, int capacity, int type, int typesize, char* type_name);
void   DestroyArray(Array* ar);

Array* resize(Array*, int size);
Array* shrink(Array*, int size);

//Adds an element to the next free position.
//If the next free position would exceed endITerator
//NULL will be returned otherwise an Iterator to the new 
//element in the Array
Iterator push(Any data);

//Pops the element of the array latest added.
//WARNING: the value returned by Pop is a pointer of void but with
//allocated memory of the size of the element stored in the stack
//after coping the VALUE the void* MUST BE FREEED by hand from the
//User!!!!
Iterator pop();

//Random Access of the Array

//Returns an Iterator of the Position within the Array.
//If you dereference it you must cast it to the appropiate 
//type you are actually storing in the array
Iterator array_at(int index);
void     array_insertIterator(Iterator insertionPoint, Data data);

//Returns the first Iterator ReadOnly
inline Iterator begin(Array* ar);
//Returns the R/W Iterator of the Cursor;
inline Iterator current(Array*ar);
//returns the previous iterator relative to the cursor
inline Iterator previous(Array*ar);
//returns the next iterator relative to the cursor
inline Iterator next(Array* ar);
//Returns the current last iterator. ReadOnly
inline Iterator end(Array* ar);

/*
* @Name: find
@brief: Looks in range [begin,end] for the first occurance of an value.
@param: Iterator begin,End - Specifys the range find should look in
@param: Any Value - Any is of type void*. Value find should look for. Can be NULL but then a Predicate must be provided!!!
@param: unary_predicate p - predicate which returns TRUE if the element found. Can be NULL but then a value of type Any must be provided!!!
@returns: Iterator to the element found in the range OR END if not found. if NULL parameter of the functions were corrupted!!!
*/
Iterator find(Iterator begin, Iterator end, Any value, unary_predicate* p);