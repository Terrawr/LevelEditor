#include "Array.h"

//Initialize an Managed Array
Array* InitializeAndCreateArray(Iterator startadress, int size, int capacity, int type, int typesize, char* type_name) {
	if (startadress == NULL) {
		Array * ar = (Array*)malloc(sizeof(Array) + capacity);

		ar->CurrentCapacity = capacity;
		if (size <= capacity)
			ar->ArraySize = size;

		//Starts after the Array struct in Memory. So the adress offset is ar+sizeof(Array).
		//It Never Moves and will always point the beginning of the array
		ar->BeginIter = ar + sizeof(Array);

		//This iterator will be moved and changes always position
		ar->CursorIter = ar->BeginIter;

		//Starts after Begin Iterator in Memory. So the adress offset for the End Iterator is BeginITer+ArraySize.
		//It will always point to the End of the Array. Because the End of the Array can vary, it is never guranteed
		//that an older Copy of the EndIter is still valid!!!
		ar->EndIter = ar + ar->ArraySize;

		//Points to the Actuall start  of the Array. Always equals the BeginIterator.
		//This array only stores pointers of type void (void*) which then points to the
		//actuall data. User is responsible for proper type casting!!!
		ar->Meta.ReferenceToData = ar->BeginIter;
		ar->Meta.type = type;
		ar->Meta.typesize = typesize;
		ar->Meta.type_name = type_name;

		return ar;
	}
	else {
		return NULL; //not yet supported
	}
}
void   DestroyArray(Array* ar) {
	free(ar->ManagedData.ReferenceTableToData);
	free(ar);
}


Array* resize(Array*, int size) {
	return NULL;
}
Array* shrink(Array*, int size) {
	return NULL;
}

//Adds an element to the next free position.
//If the next free position would exceed endITerator
//NULL will be returned otherwise an Iterator to the new 
//element in the Array
Iterator push(Any data) {
	return NULL;
}

//Pops the element of the array latest added.
//WARNING: the value returned by Pop is a pointer of void but with
//allocated memory of the size of the element stored in the stack
//after coping the VALUE the void* MUST BE FREEED by hand from the
//User!!!!
Iterator pop() {
	return NULL;
}

//Random Access of the Array

//Returns an Iterator of the Position within the Array.
//If you dereference it you must cast it to the appropiate 
//type you are actually storing in the array
Iterator array_at(int index) {
	return NULL;
}
void     array_insertIterator(Iterator insertionPoint, Data data) {
	return NULL;
}

//Returns the first Iterator ReadOnly
 Iterator begin(Array* ar) { return ar->BeginIter; };
//Returns the R/W Iterator of the Cursor;
 Iterator current(Array*ar) { return ar->CursorIter; }
//returns the previous iterator relative to the cursor
 Iterator previous(Array*ar) { return --ar->CursorIter; }
//returns the next iterator relative to the cursor
 Iterator next(Array* ar) { return ++ar->CursorIter; }
//Returns the current last iterator. ReadOnly
 Iterator end(Array* ar) { return ar->EndIter; }

/*
* @Name: find
@brief: Looks in range [begin,end] for the first occurance of an value.
@param: Iterator begin,End - Specifys the range find should look in
@param: Any Value - Any is of type void*. Value find should look for. Can be NULL but then a Predicate must be provided!!!
@param: unary_predicate p - predicate which returns TRUE if the element found. Can be NULL but then a value of type Any must be provided!!!
@returns: Iterator to the element found in the range OR END if not found. if NULL parameter of the functions were corrupted!!!
*/
Iterator find(Iterator begin, Iterator end, Any value, unary_predicate* p)
{
	if (p != NULL && value == NULL) {
		for (; begin != end; begin++)
			if (p(begin))
				return begin;
		return end;
	}
	else if (p == NULL && value != NULL) {
		for (; begin != end; begin++)
			if (*begin == value)
				return begin;
		return end;
	}

	return NULL;
}