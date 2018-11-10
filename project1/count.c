#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 30

int main(int argc, char*  argv[]){
if(argc < 2){ printf("Error not enough parameters\n"); }

int count = 0;
char word[MAX_WORD_LENGTH];

//opening the file
FILE *file = fopen(argv[1], "r");
if (file == NULL){
printf("Error openign the file");
}

//looping through the textfile word by word
while (fscanf(file, "%s", word) == 1){
count++;
}

fclose(file);

//if there's one word, will say word, not words
if(count == 1){ printf("1 word\n"); }
else{ printf("%d total words\n", count); }
}

