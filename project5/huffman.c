#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tree.h"
#include "pack.h"
#define p(x)	((x)-1/2)
#define l(x)	((x)*2+1)
#define r(x)	((x)*2+2)

struct tree{
	int data;
	struct tree *left;
	struct tree *right;
	struct tree *parent;
};

int count;
static struct tree *heap[257];
static struct tree *nodes[257]; //EXTRA ONE FOR EOF

//insert nodes into heap 
static void insert(struct tree *np){
	int idx = count++;

	while(idx > 0){
		//move np to proper position
		if(heap[p(idx)] != NULL && np->data < heap[p(idx)]->data){
			heap[idx] = heap[p(idx)];
			idx = p(idx);
		}
	} 
	heap[idx] = np;
}

//one iteration of the delete, will call this function while heap has more than 1 value (count) 
static struct tree *delete(void){
	struct tree *min, *np;
	min = heap[0];
	int minIndex = 0;
	int child;
		
	struct tree *left, *right;
	np = heap[count--]; //decrementing count while grabbing value to add to top of heap 
	
	//reheap down
	while(r(count) < count){
		right = heap[r(count)];
		left = heap[l(count)];
		child = l(count); //for traversing down until bottom
		
		//ifthe left is less than right isnt end 
		if(left->data < right->data && l(count) < count){
			child = l(count) + 1;
		}
		if(heap[child]->data < np->data){ //swapping
			heap[minIndex] = heap[child];
		}
		else{ break; }
	}
	count--;
	return min;
}


void printcode(struct tree *np){
	if(np->parent != NULL){
		printcode(np->parent);
		if(np == np->parent->left){ printf("0"); }
		else{ printf("1"); }
	}
}

int main(int argc, char *argv[]){
	assert(argc == 3);

	FILE *fp = fopen(argv[1], "r");
	assert(fp != NULL);
	int counts[257];

	int c;
	//counting the character frequency in the textfile
	while((c = getc(fp)) != EOF){
		counts[c]++;
	}
	fclose(fp);

	//create and save tree nodes in nodes[]
	for(int i = 0; i < 256; i++){
		if(counts[i] != 0){ //will be 0 when reaches EOF 
			nodes[i] = createTree(counts[i], NULL, NULL);
		}
	}

	//signifying eof
	nodes[256] = createTree(0, NULL, NULL);

	//insert nodes to heap
	for(int i=0; i<257; i++){
		if(nodes[i] != NULL){
			insert(nodes[i]);	
		}
	}



	//combine trees until 2 
	while(count > 1){
		//delete nodes from heap 
		struct tree* np1 = delete();
		struct tree* np2 = delete();
		//combine, then put into tree

		int combine = np1->data + np2->data;
		struct tree* combinedTrees = createTree(combine, np1, np2);
		insert(combinedTrees);
	}
	//print bit pattern for each character
	for(int i=0; i< 256; i++){
		if(counts[i] > 0){
			printcode(nodes[i]);
			printf("\n");
		}

	}
	printcode(nodes[256]);
	printf("\n");
	//call pack function
	pack(argv[1], argv[2], nodes);

	return 0;
}


