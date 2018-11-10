#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "set.h"

/*
check for before inserting a new element
returns -1 if element was not found
returns index int >= 0 if element is found 
*/

//sets up the struct with a count, length and elements 
struct sp{
        int     count;
        int     length;
        char    **elts;
};

//findElement returns the index of the element and -1 if it is not in teh set
static int findElement(SET *sp, char *elt){
	assert(sp != NULL && elt != NULL);
	for(int i = 0; i < sp->count; i++){
		if(strcmp(sp->elts[i], elt) == 0){ 
			return i; }
	}
	return -1;
}

/* returns a bool value of whether or not the element is found in the set;
   uses findElement */
bool hasElement(SET *sp, char *elt){
	if(findElement(sp, elt) == -1){
		return false;
	}
	return true;
}

//creates a set given int max number of elements
//assigns the set struct count, length and space for elements
SET* createSet(int maxElts){
	SET *sp;
	sp = malloc(sizeof(sp));
	assert(sp != NULL);
	sp->count = 0;
	sp->length = maxElts;
	sp->elts = malloc(sizeof(char*)*maxElts);
	assert(sp->elts != NULL);
	return sp;
}

//adds an element to the set if and only if the char* is not found in the set already
bool addElement(SET *sp, char* elt){
	//if the element is already in the set, it will not add it or if the element 
	assert(sp != NULL && elt != NULL);
		if(!hasElement(sp, elt) || sp->count >= sp->length){ 
			return false; }
	/* allocates memory first,
	then takes a copy of the char*
	& points the index to the char* */
	sp->elts[sp->count] = strdup(elt); 	
	
	//once the new element is added to the set, increments count
	sp->count++;
	
	return true;
}

/* throws away all of the information stored inside of the set pointer
   goes through each element and frees the info
   has subsequent checks for freeing the entirety of elts 
   as well as the whole of sp (the count and length variables)
*/
void destroySet(SET *sp){
	assert(sp != NULL);
	for(int i = 0; i < sp->count; i++){
		if(sp -> elts[i] != NULL){
			free(sp -> elts[i]);
		}
	}
	free(sp -> elts);
	free(sp);
}

/* removes a specific element in the set;
   returns true if successful & false if not
   if successful, sp -> will be decremented  */
bool removeElement(SET *sp, char *elt){
	assert(elt != NULL);
	assert(sp != NULL);
	
	//will not remove element if it is not in set
	if(!hasElement(sp, elt)){ return false; }

	int index = findElement(sp, elt);	
	free(sp -> elts[index]);
	sp->elts[index] = sp->elts[sp->count-1];
	sp -> count -= 1;
	return true;
}

int numElements(SET *sp){
return sp->count;
}
