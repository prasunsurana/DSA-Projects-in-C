// Modify this file
// compile with: gcc linkedlist.c -o linkedlist

#include <stdio.h>
#include <stdlib.h> // contains the functions free/malloc

// TODO: Create your node_t type here
typedef struct node{
	int year;
	int data;
	struct node* next;
}node_t;

// TODO: Write your functions here
// There should be 1.) create_list 2.) print_list 3.) free_list
// You may create as many helper functions as you like.
node_t* create_node(int year, int data, node_t* next){

	//Allocate memory for a new node
	node_t* node = (node_t*)malloc(sizeof(node_t));

	//Check if malloc was unable to allocate memory
	if (node == NULL){
		return NULL;
	}

	//Populate the node's fields
	node->year = year;
	node->data = data;
	node->next = next;

	return node;

}

node_t* create_list(){

	//Populate each node's fields with data
	node_t* year2014 = create_node(2014, 71, NULL);
	node_t* year2015 = create_node(2015, 78, year2014);
	node_t* year2016 = create_node(2016, 93, year2015);
	node_t* year2017 = create_node(2017, 93, year2016);
	node_t* year2018 = create_node(2018, 108, year2017);

	return year2018;

}

void print_list(node_t* head){

	//Null check on function parameter
	if (head == NULL){
		return;
	}

	node_t* iterator = head;

	while (iterator != NULL){
		printf("%d: %d wins.\n", iterator->year, iterator->data);
		iterator = iterator->next;
	}

	return;
}

void free_list(node_t* head){

	//Null check on function parameter
	if (head == NULL){
		return;
	}

	node_t* temp = head;
	node_t* store;

	while (temp != NULL){
		store = temp->next;
		free(temp);
		temp = store;
	}

	return;
}

int main(){
	// TODO: Implement me!  

	node_t* redsox = create_list();
	print_list(redsox);
	free_list(redsox);

    return 0;
}
