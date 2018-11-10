#ifndef DEQUE_H
#define DEQUE_H

class Deque{
	int count;
	class Node *head;
	
public:
	Deque();
	~Deque();
	int size();
	void addLast(int x);
	void addFirst(int x);
	int removeFirst();
	int removeLast();
	int getFirst();
	int getLast();
};
#endif
