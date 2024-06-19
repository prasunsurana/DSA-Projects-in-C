// Include our header file for our my_bst.c
#include "my_bst.h"

// Include any other libraries needed
#include <stdio.h>
#include <stdlib.h>

// Creates a BST
// Returns a pointer to a newly created BST.
// The BST should be initialized with data on the heap.
// The BST fields should also be initialized to default values(i.e. size=0).
bst_t* bst_create(){
    // Modify the body of this function as needed.

	//Allocate memory for the new BST
	bst_t* myBST= (bst_t*)malloc(sizeof(bst_t));

	//Check whether malloc was unable to allocate memory
	if (myBST == NULL){
		return NULL;
	}

	//Initialize the fields of the BST
	myBST->size = 0;
	myBST->root = NULL;

    return myBST;
}

// BST Empty
// Check if the BST is empty
// Returns 1 if true (The BST is completely empty)
// Returns 0 if false (the BST has at least one element)
int bst_empty(bst_t* t){

	//Null check on function parameter
	if (t == NULL){
		return -1;
	}

	if (t->size == 0){
		return 1;
	}
	else {
		return 0;
	}
}

//Helper function for bst_add 
void bst_addhelper(bstnode_t* rootnode, bstnode_t* newnode){

	if (newnode->data <= rootnode->data){
                if (rootnode->leftChild == NULL){ //If the root node has no children, simply add newnode to the root node
                        rootnode->leftChild = newnode;
                }
        	else { //Recursively call the helper function down the left side of the tree/subtrees 
			bst_addhelper(rootnode->leftChild, newnode);
		}
	} else {
		if (rootnode->rightChild == NULL){ //If the root node has no children, simply add newnode to the root node
			rootnode->rightChild = newnode;
		}
		else { //Recursively call the helper function down the right side of the tree/subtree
			bst_addhelper(rootnode->rightChild, newnode);
		}
	}
}

// Adds a new node containng item to the BST
// The item is added in the correct position in the BST.
//  - If the data is less than or equal to the current node we traverse left
//  - otherwise we traverse right.
// The bst_function returns '1' upon success
//  - bst_add should increment the 'size' of our BST.
// Returns a -1 if the operation fails.
//      (i.e. the memory allocation for a new node failed).
// Your implementation should should run in O(log(n)) time.
//  - A recursive imlementation is suggested.
int bst_add(bst_t* t, int item){

	//Null check on function parameter
	if (t == NULL){
		return -1;
	}

	//Allocate memory for a new node
	bstnode_t* newnode = (bstnode_t*)malloc(sizeof(bstnode_t));

	//Check whether malloc was unable to allocate memory
	if (newnode == NULL){
		return -1;
	}

	//Initialize the new node's fields
	newnode->data = item;
	newnode->leftChild = NULL;
	newnode->rightChild = NULL;

	//Check if the BST is empty. If it is, then make the new node the root node. If not, the recursively
	//traverse through the BST and add the new node to the appropriate place.
	if (t->root == NULL){
		t->root = newnode;
		t->size++;
	}
	else {
		bst_addhelper(t->root, newnode);
		t->size++;
	}

	return 1;
 
}

//Helper function to print the nodes in a tree in ascending order
void printascending(bstnode_t* node){

	if (node == NULL){
		return;
	}

	printascending(node->leftChild);
	printf("%d\n", node->data);
	printascending(node->rightChild);
}

//Helper function to print the nodes in a tree in descending order
void printdescending(bstnode_t* node){

	if (node == NULL){
		return;
	}

	printdescending(node->rightChild);
	printf("%d\n", node->data);
	printdescending(node->rightChild);
}


// Prints the tree in ascending order if order = 0, otherwise prints in descending order.
// For NULL tree -- print "(NULL)".
// It should run in O(n) time.
void bst_print(bst_t *t, int order){

	//If the tree is null, print NULL
	if(NULL == t){
		printf("(NULL)");
	}
	else {
		if (order == 0){
			printascending(t->root);
		}
		else {
			printdescending(t->root);
		}
	}
}

//Helper function for bst_sum
int sumHelper(bstnode_t* node){

	if (node == NULL){
		return 0;
	}

	return sumHelper(node->leftChild) + node->data + sumHelper(node->rightChild);

}

// Returns the sum of all the nodes in the bst. 
// exits the program for a NULL tree. 
// It should run in O(n) time.
int bst_sum(bst_t *t){

	if (t == NULL){
		return -1;
	}

	return sumHelper(t->root);
}

//Helper function for bst_find
int findHelper(bstnode_t* node, int value){

	if (node == NULL){
		return 0;
	}

	//If the value we are looking for matches the value stored in the root node, the function returns 1 and ends here 
	if (node->data == value){
		return 1;
	}
	if (value > node->data){ //If the value is greater than the root node, recursively travel down the right side of the (sub)tree
		return findHelper(node->rightChild, value);
	}
	if (value < node->data){ // If the value is less than the root node, recursively travel down the left side of the (sub)tree
		return findHelper(node->leftChild, value);
	}

	return 0;

}

// Returns 1 if value is found in the tree, 0 otherwise. 
// For NULL tree it exists the program. 
// It should run in O(log(n)) time.
int bst_find(bst_t * t, int value){
 
	if (t == NULL){
		return -1;
	}

	return findHelper(t->root, value);
}

// Returns the size of the BST
// A BST that is NULL exits the program.
// (i.e. A NULL BST cannot return the size)
unsigned int bst_size(bst_t* t){

	if (t == NULL){
		return -1;
	}

	return t->size;

}

//Helper function for bst_free
void freehelper(bstnode_t* node){

	if (node == NULL){
		return;
	}

	//Free the subtrees on either side first, and lastly free the root node
	freehelper(node->leftChild);
	freehelper(node->rightChild);
	free(node);
}


// Free BST
// Removes a BST and ALL of its elements from memory.
// This should be called before the proram terminates.
void bst_free(bst_t* t){

	if (t == NULL){
		return;
	}

	t->size = 0; //reset the size of the BST to 0 when all nodes are freed.
	freehelper(t->root);
	free(t);
	
}

