#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "deque.h"

int main(void){

DEQUE *result = createDeque(); 
DEQUE *dq[10];

int x;
int max=0;

printf("Please input non-negative integers to sort:\n");

//scanning for integers and adding into result dq
while(scanf("%d", &x) == 1){
	if(x > 0){
		addLast(result, x);
		if(x > max){ max = x; }	
		numInts++;
	}
}

//initializing the deques for dq
for(int i = 0; i < 10; i++){
	dq[i] = createDeque();
}

//calculating number of rounds required
int round = ceil(log(max+1)/log(10));

//count variable to track which one is our current round and to calculate the digit index for radix
int count = 0;
while(count < round){

	//adding in the result array to the dq array based on radix way of sorting
	while(numItems(result) != 0){
		int index;
		index = getFirst(result) % 10;
		if(count != 0){ 
		double mult = pow(10.0, (double) count);
		index = (getFirst(result)/(int)mult) % 10; }
				
		addFirst(dq[index], removeFirst(result));
	}

	//taking everything from dq -> result
	for(int i = 0; i < 10; i++){
		while(numItems(dq[i]) != 0){	
			addLast(result, removeLast(dq[i]));
		}
	} 
count++; //count incremented at end of each round 
}


printf("Sorted integers:\n");
while(numItems(result) != 0){
	printf("%d\n", removeFirst(result));
}

}
