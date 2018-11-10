#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deque.h"

//deque struct with count & head pointer 
struct deque{
	int count;
	struct node *head;
};

//node struct with data, next & prev (circular)
struct node{
	int data;
	struct node *next;
	struct node *prev;
};

//createDeque allocates space for head and a deque & sets the head next & prev to dummy node
struct deque *createDeque(){
	struct deque *dp;
	dp = malloc(sizeof(struct deque));
	assert(dp != NULL);
	dp->count = 0;
	dp->head = malloc(sizeof(struct node));
	assert(dp->head != NULL);
	
	dp->head->next = dp->head;
	dp->head->prev = dp->head;

	return dp;
}

//destroyDeque destroys the deque node by node and frees the data
void destroyDeque(struct deque *dp){
	assert(dp != NULL);
	if(dp->count != 0){
	struct node *pDel;
	pDel = dp->head;
	do{
		pDel = pDel->next;
		dp->count--;
		free(pDel);
	} while(pDel->next != dp->head); } //stops when we reach the end of circular list 
	free(dp->head); //once we reach the end, this is when head is freed
	free(dp);
}

//numItems returns number of items in deque currently
int numItems(struct deque *dp){
	assert(dp != NULL);
	return dp->count;
}

//addFirst adds a node with value x stored in it to the beginning of the deque
void addFirst(struct deque *dp, int x){
	assert(dp != NULL);
	struct node *np = malloc(sizeof(struct node)); //new data needs to have space allocated for it
	assert(np != NULL);
	np->data = x; //setting data of new node
	
	dp->head->next->prev = np; //putting the new node after head 
	np->next = dp->head->next; //setting new node's next value
	np->prev = dp->head; //setting new node's previous value
	dp->head->next = np; 
	dp->count++; //increment count 
}

//addLast adds a new node with value x stored in it to the end of deque
void addLast(struct deque *dp, int x){
	assert(dp != NULL);
	struct node *np = malloc(sizeof(struct node));
	assert(np != NULL);
	np->data = x;
	
	//same reasoning as addFirst, only slightly different because at end of deque
	dp->head->prev->next = np;
	
	np->prev = dp->head->prev;
	np->next = dp->head;
	
	dp->head->prev = np;
	dp->count++;
}

//removeFirst removes node at beginning of deque (after dummy node) 
int removeFirst(struct deque *dp){
	assert(dp != NULL && dp->count > 0);
	
	int del = dp->head->next->data;
	
	struct node *nextSave; 
	nextSave = dp->head->next->next;
	
	free(dp->head->next);
	
	dp->head->next = nextSave;
	dp->head->next->prev = dp->head;
	dp->count--;
	return del;
}

//removeLast removes node at end of deque 
int removeLast(struct deque *dp){
	assert(dp != NULL);
	if(dp->count == 0){ return -1;  } //won't remove if count is 0 (meaning only dummy node is present)}
	int del = dp->head->prev->data;
	
	struct node *delNextSave;
	delNextSave = dp->head->prev->prev;
	free(dp->head->prev);
	
	dp->head->prev = delNextSave;
	dp->head->prev->next = dp->head;
	dp->count--;
	return del;
}

//getFirst returns the first node with data in it (skips the dummy node)
int getFirst(struct deque *dp){
	assert(dp != NULL);
	if(dp->head->next == NULL){ return 1; }
	return dp->head->next->data; 
}

//getLast returns the last node in deque
int getLast(struct deque *dp){
	assert(dp != NULL);
	if(dp->head->next == NULL){
		return -1;
	}
	return dp->head->prev->data;
}

