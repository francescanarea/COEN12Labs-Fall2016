#include <cassert>
#include "deque.h"

//creating the node
struct Node{
	int data;
	Node *next;
	Node *prev;
};

//creating the deque, with count set to 0, as well as a head that is circularly linked
Deque::Deque(){
	count = 0;
	head = new Node();

	head->next = head;
	head->prev = head;
}

//destructor, frees the memory, including the head
Deque::~Deque(){
	if(count != 0){
		Node *pDel = head;
		Node *next;
	do{
		next = pDel->next;
		delete pDel;
		pDel = next;
	}while(pDel != head); }
	delete head;
}

//returns the current size of the deuqe
int Deque::size(){
	return count;
}

//adds to the front of the deque, after the head
void Deque::addFirst(int x){
	Node *np = new Node();
	np->data = x;
	
	//the element after head will be teh element we are adding
	head->next->prev = np;
	np->next = head->next;
	np->prev = head;
	head->next = np;
	count++; //increment count once add the element
}

//adds to the end of the deque
void Deque::addLast(int x){
	Node *np = new Node();
	np->data = x;

	//since the list is circularly linked, can add through the head's preivous element 
	head->prev->next = np;
	np->prev = head->prev;
	np->next = head;

	head->prev = np;
	count++; //increment count once add the elemtn
}

//removes the last element
int Deque::removeLast(){
	if(count == 0){ return -1; }
	int del = head->prev->data; //saving the element's data to return
	
	//saving the new last element
	Node *delNextSave = head->prev->prev;
	
	delete head->prev; //actually deleting the element
	
	head->prev = delNextSave;
	head->prev->next = head;
	count--; //decrementing count once the elemtn is deleted
	
	return del;
}

//removes the first element in the deque
int Deque::removeFirst(){
	if(count == 0){ return -1; }
	int del = head->next->data; //saving the element's data to return later

	//saving the new first element
	Node *nextSave = head->next->next;

	delete head->next; //actually deleting the first element
	
	head->next = nextSave;
	head->next->prev = head;
	count--; //decrements count once element is removed
	return del;
}

//gets the first element in teh deque, without changing or deleting it
int Deque::getFirst(){
	assert(count > 0);
	return head->next->data;
}

//gets the last element in the deque, without changing or deleing it
int Deque::getLast(){
	assert(count > 0);
	return head->prev->data;
}
