#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "set.h"

//sets up the struct with count, length and elements
struct sp{
        int     count;
        int     length;
        char    **elts;
};

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

//uses binary search to find the element in a sorted array
//returns the index of the element if found 
//if not found returns index of where to insert
static int findElement(SET *sp, char *elt, bool *found){
	assert(sp != NULL && elt != NULL);
	int low; int high; int mid;
	low = 0;
	high = sp->count-1;
	while(low <= high){
		mid = (low + high)/2;
		if (strcmp(elt, sp->elts[mid]) < 0){ high = mid-1; }
		if (strcmp(elt, sp->elts[mid]) > 0){ low = mid+1; }
		if (strcmp(elt,sp->elts[mid]) == 0){
			*found = true;
			return mid;
		}
	}
	*found = false;
	return low; 
}

//uses the findElement function to add in the elt if it is not found 
//if and once the element is added, moves down the trailing elements
bool addElement(SET *sp, char* elt){
	//asserts to make sure element & struct isn't null
	assert(sp != NULL && elt != NULL);
	//asserts to make sure that the count won't go over length
	assert(sp->count < sp->length);
	bool found = false;
	int locn;
	
	locn = findElement(sp, elt, &found);
	//if the elemtn is not in the set, it will be added
	if(!found){
		assert(sp->count < sp->length);
		//for loop goes backwards to shift the elements
		for(int i = sp->count; i > locn; i--){
			sp->elts[i] = strdup(sp->elts[i-1]);
		}		
//		sp->count++; //you need to increment count once you add it to set
		sp->elts[locn] = strdup(elt); //actually setting location equal to element
		return true;
	}
	return false;
}

//uses findElement to remove an element
//moves up the elements behind it once it is deleted
bool removeElement(SET *sp, char *elt){
	assert(elt != NULL && sp != NULL);
	bool found;
	int locn;
	locn = findElement(sp, elt, &found);

	//element will be removed only if it is in the set 
	if(found){
		free(sp -> elts[locn]);
		for(int i = locn; i < sp->count; i++){
			sp->elts[i] = strdup(sp->elts[i+1]);
		}	
		sp->count--; //decrementing count once the elemtn is removed
		return true;
	}
	return false;
}

//if find element returns true, the set has the element
bool hasElement(SET *sp, char *elt){
	bool found;
	int locn;
	locn = findElement(sp, elt, &found);
	if(found){ return true; }
	return false;
}

//frees everything stored in the set
void destroySet(SET *sp){
        assert(sp != NULL);

	//loops through each element in sp and frees the space
        for(int i = 0; i < numElements(sp); i++){
                if(sp -> elts[i] != NULL){
                        free(sp -> elts[i]);
                }
        }
        free(sp -> elts);
        free(sp);
}

//returns the number of elements in the set (the count) (slightly useless)
int numElements(SET *sp){ return sp->count; }
