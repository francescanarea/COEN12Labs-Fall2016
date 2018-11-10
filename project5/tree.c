#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"

struct tree{
	int data;
	struct tree *left, *right, *parent;
};

struct tree *createTree(int data, struct tree *left, struct tree *right){
	//allocating space for tre
	struct tree *root = malloc(sizeof(struct tree));
	assert(root != NULL);

	root->right = NULL;
	root->left = NULL;
	
	//setting data
	root->data = data;

	//if left has a parent already
	setLeft(root,left);
	
	//if right has a parent already
	setRight(root,right);
	return root;
}

//recursively destroys the tree 
void destroyTree(struct tree *root){
	if(root == NULL){ return; }
	destroyTree(root->left);
	destroyTree(root->right);
	free(root);
}

int getData(struct tree *root){
	assert(root != NULL);
	return root->data;
}

struct tree *getLeft(struct tree *root){
	assert(root != NULL);
	return root->left;
}

struct tree *getRight(struct tree *root){
	assert(root != NULL);
	return root->right;
}

struct tree *getParent(struct tree *root){
	assert(root != NULL);
	return root->parent;
}

void setLeft(struct tree *root, struct tree *left){
	assert(root != NULL);
	
	//if the root has a left, break connection between root & left
	if(root->left != NULL){
		root->left->parent = NULL;
		root->left = NULL;
	}

	//if the left root given has a parent already, break these connections
	if(left != NULL && left->parent != NULL){
		if(left->parent->left == left){
			left->parent->left = NULL; }
		else{ left->parent->right = NULL; } 
	}
	if(left != NULL){ left->parent = root; }
	root->left = left;
}

void setRight(struct tree *root, struct tree *right){
	assert(root != NULL);

	if(root->right != NULL){
		root->right->parent = NULL;
		root->right = NULL;
	}

	if(right != NULL && right->parent != NULL){
		if(right->parent->right == right){
			right->parent->right = NULL;
		}
		else{ right->parent->left = NULL; } 
	}

	if(right != NULL){ right->parent = root; }
	root->right = right;
}
