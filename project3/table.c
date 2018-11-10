#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "set.h" 

struct sp{
	int	count;
	int	length;
	char	**elts;
	char	*flags;

};

//creates a set with max elements allocated spots 
//uses the above struct 
SET *createSet(int maxElts){
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->count = 0;
	sp->length = maxElts;

	sp->elts = malloc(sizeof(char*)*maxElts);
	assert(sp->elts != NULL);

	sp->flags = malloc(sizeof(char)*maxElts);
	assert(sp->flags != NULL);

	//stuff for flags, by default every space is empty
	for(int i = 0; i < maxElts; i++){
		sp->flags[i] = 'E';
	}
	
	return sp;
}

//given hash function
static unsigned hashString(char *s){
	unsigned hash = 0;

	while(*s != '\0')
		hash = 31 * hash + *s++;
	return hash;
}

//returns index of element + a boolean variable found 
static int findElement(SET *sp, char *elt, bool *found){
	assert(sp != NULL && elt != NULL);
	int initial;
	int locn;	
	int available = -1;
	initial = hashString(elt)%(sp->length);

	for(int i = 0; i < sp->length; i++){

		//stores locn just in case need to return under certain condition
		locn = (initial + i)%(sp->length); 
	
		//if the space is empty... found is false
		if(sp->flags[locn] == 'E'){ 
			*found = false; 
			if(available != -1){
				return available;
			}
			else { return locn; }
		} 

		/*if the space is deleted & available has been changed 
		  once before, it is now set to locn*/
		else if(sp->flags[locn] == 'D'){
			if(available == -1){
				available = locn;
			}
		}

		/*if it is filled and it is the ele we are looking for,
	          returns this spot*/
		else if(sp->flags[locn] == 'F'){
			if(strcmp(sp->elts[locn], elt) == 0){ 
				*found = true;
				return locn;
			}
		}		
	}
	*found = false;
	return available;
}


//destroys sp by freeing elements and everything within struct
void destroySet(SET *sp){
	assert(sp != NULL);
	for(int i =0; i< sp->length; i++){
		//only if the space is filled with it free it
		if(sp->flags[i] == 'F'){
			free(sp->elts[i]);
		}
	}	
	free(sp->flags);
	free(sp->elts);
	free(sp);
}

//returns the number of elements in the set
int numElements(SET *sp){
	assert(sp != NULL);
	return sp->count;
}

//returns true/false if the set has an element (uses findElement's bool)
bool hasElement(SET *sp, char *elt){
	assert(sp != NULL);
	bool found;
	int i = findElement(sp, elt, &found);
	if(!found){
		return false;
	}
	return true;
}

//adds an element to the set only if it is not already there
bool addElement(SET *sp, char* elt){
        assert(sp != NULL && elt != NULL);
	bool found; 
	int index = findElement(sp, elt, &found);
	
	//if the ele is in set, will not add it
	if(found){
		return false;
	}
	
	//if the count is larger than or equal to length, will not add ele
	if(sp->count >= sp->length){
		return false;
	} 

/*	 allocates memory first,
        then takes a copy of the char*
        & points the index to the char* */ 
        sp->elts[index] = strdup(elt);
	//flag stuff
	assert(sp->flags != NULL);
	sp->flags[index] = 'F'; //filled
        //once the new element is added to the set, increments count
        sp->count++;
        return true;  
}


//removeElement removes the given element if it is found in the set	
bool removeElement(SET *sp, char *elt){
        assert(elt != NULL);
        assert(sp != NULL);
	bool found;
	int index = findElement(sp, elt, &found);
        
	//will not remove element if it is not in set
        if(!found){ return false; }

	if(sp->elts[index] != NULL){        
	free(sp -> elts[index]); }
        
        sp->count--;
        
	assert(sp->flags != NULL);
	sp->flags[index] = 'D';
	return true;
}
