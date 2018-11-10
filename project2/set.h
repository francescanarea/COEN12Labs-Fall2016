#include <stdio.h>
#include <stdbool.h>
#ifndef SET_H
#define SET_H

typedef struct sp SET;
SET* createSet(int maxElts);
void destroySet(SET *sp);
int numElements(SET *sp);
bool hasElement(SET *sp, char *elt);
bool addElement(SET *sp, char *elt);
bool removeElement(SET *sp, char *elt);
#endif /* SET_H */
