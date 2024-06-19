// =================== Support Code =================
// Doubly Linked List ( DLL ).
//
//
//
// - Implement each of the functions to create a working DLL.
// - Do not change any of the function declarations
//   - (i.e. dll_t* create_dll() should not have additional arguments)
// - You should not have any 'printf' statements in your DLL functions. 
//   - (You may consider using these printf statements to debug,
//     but they should be removed from your final version)
//   - (You may write helper functions to help you debug your code such as print_list etc)
// ==================================================
#ifndef MYDLL_H
#define MYDLL_H
#include <stdlib.h>
#include <stdio.h>

// Create a node data structure to store data within
// our DLL. In our case, we will stores 'integers'
typedef struct node {
    void* data;
    struct node* next;
    struct node* previous;
} node_t;

// Create a DLL data structure
// Our DLL holds a pointer to the first node in our DLL called head,
// and a pointer to the last node in our DLL called tail.
typedef struct DLL {
    int count;              // count keeps track of how many items are in the DLL.
    node_t* head;           // head points to the first node in our DLL.
    node_t * tail;          //tail points to the last node in our DLL.
} dll_t;

// Creates a DLL
// Returns a pointer to a newly created DLL.
// The DLL should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The DLLs fields should also be initialized to default values.
// Returns NULL if we could not allocate memory.
dll_t* create_dll(){
    // Modify the body of this function as needed.

	//Allocate memory for the newly created doubly linked list called myDLL    
	dll_t* myDLL = (dll_t*)malloc(sizeof(dll_t));

	//Check if malloc was unable to allocate memory to myDLL
	 if (myDLL == NULL){
                return NULL;
        }

	//Initialize the fields for myDLL
	myDLL->head = NULL;
        myDLL->tail = NULL;
        myDLL->count = 0;

        return myDLL;
}

// DLL Empty
// Check if the DLL is empty
// Returns -1 if the dll is NULL.
// Returns 1 if true (The DLL is completely empty)
// Returns 0 if false (the DLL has at least one element enqueued)
int dll_empty(dll_t* l){
    // TODO: Implement me!!

	//Null check on the function parameter
	if (l == NULL){
	        return -1;
        }
        else if (l->count == 0){
                return 1;
        }
        else {
                return 0;
        }
}

// push a new item to the front of the DLL ( before the first node in the list).
// Returns -1 if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// (i.e. the memory allocation for a new node failed).
int dll_push_front(dll_t* l, void* item){
    // TODO: Implement me!!

	//Null check on the function parameter
        if (l == NULL){
                return -1;
        }

	//Allocate memory for a new node
        node_t* new_node = (node_t*)malloc(sizeof(node_t));

	//Check if malloc was unable to allocate memory to the new node
        if (new_node == NULL){
        	return 0;
        }

	//Adding a node when the DLL is empty
        if (l->head == NULL){
                l->head = new_node;
                l->tail = new_node;
                new_node->next = NULL;
                new_node->previous = NULL;
                new_node->data = item;
                l->count++;
                return 1;
        }

        else {
		//Initialize the new node's fields
                new_node->data = item;
                new_node->next = l->head;
                new_node->previous = NULL;

		//Add the new node to the start of the list
                l->head->previous = new_node;
                l->head = new_node;
                l->count++;

                return 1;
        }
}

// push a new item to the end of the DLL (after the last node in the list).
// Returns -1 if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// (i.e. the memory allocation for a new node failed).
int dll_push_back(dll_t* l, void* item){
    // TODO: Implement me!!

	//Null check on function parameter
        if (l == NULL){
                return -1;
        }

	//Allocate memory for a new node
        node_t* new_node = (node_t*)malloc(sizeof(node_t));

	//Check if malloc was unable to allocate memory to the newnode
        if (new_node == NULL){
 	       return 0;
        }

	//Adding a node when the DLL is empty
        if (l->tail == NULL){
                l->head = new_node;
                l->tail = new_node;
                new_node->next = NULL;
                new_node->previous = NULL;
                new_node->data = item;
                l->count++;

                return 1;
        }

        else {
		//Initialize the new node's fields
        	new_node->data = item;
                new_node->next = NULL;
                new_node->previous = l->tail;

		//Adding a new node to the end of the list
                l->tail->next = new_node;
                l->tail = new_node;
                l->count++;

                return 1;
        }
}

// Returns the first item in the DLL and also removes it from the list.
// Returns -1 if the DLL is NULL. 
// Returns 0 on failure, i.e. there is noting to pop from the list.
// Assume no negative numbers in the list or the number zero.
void* dll_pop_front(dll_t* t){
    // TODO: Implement me!!

	//Null check on function parameter
        if (t == NULL){
                return NULL;
        }

	//Check if DLL is empty
        if (t->count == 0){
                return NULL;
        }

	//Pop front if there is only one element in the list
        if (t->count == 1){
                int* data = t->head->data;
                node_t* temp = t->head;
                t->head = NULL;
                t->tail = NULL;
                t->count--;
                free(temp);
                return data;
        }

        else {
                int* data = t->head->data;
                node_t* temp = t->head;
                t->head = t->head->next;
                t->head->previous = NULL;
                free(temp);
                t->count--;
                return data;
        }
}

// Returns the last item in the DLL, and also removes it from the list.
// Returns a -1 if the DLL is NULL. 
// Returns 0 on failure, i.e. there is noting to pop from the list.
// Assume no negative numbers in the list or the number zero.
void* dll_pop_back(dll_t* t){
    // TODO: Implement me!!

	//Null check on function parameter	
        if (t == NULL){
                return NULL;
        }

	//Check if the DLL is empty
        if (t->count == 0){
                return NULL;
        }

	//Pop back if there is only one element in the list
        if (t->count == 1){
                int* data = t->tail->data;
                node_t* temp = t->tail;
                t->head = NULL;
                t->tail = NULL;
                t->count--;
                free(temp);
                return data;
        }

        else {
                int* data = t->tail->data;
                node_t* temp = t->tail;
                t->tail = t->tail->previous;
                t->tail->next = NULL;
                t->count--;
                free(temp);
                return data;
        }
}

// Inserts a new node before the node at the specified position.
// Returns -1 if the list is NULL
// Returns 1 on success
// Retruns 0 on failure:
//  * we couldn't allocate memory for the new node
//  * we tried to insert at a negative location.
//  * we tried to insert past the size of the list
//   (inserting at the size should be equivalent as calling push_back).
int dll_insert(dll_t* l, int pos, void* item){
    // TODO: Implement me!!

	//Null check on function parameter
        if (l == NULL){
                return -1;
        }

	//Exit function if the position parameter entered is negative or exceeds the list size
        if (pos < 0 || pos > l->count){
                return 0;
        }

	//If inserting at the front of the list, invoke the push_front function
        else if (pos == 0){
                return dll_push_front(l, item);
        }

	//If inserting at the rear of the list, invoke the push_back function
        else if (pos == l->count){
                return dll_push_back(l, item);

        }

        else {

		//Allocate memory for a new node
                node_t* new_node = (node_t*)malloc(sizeof(node_t));

		//Check whether malloc was unable to allocate memory for the new node
                if (new_node == NULL){
                        return 0;
                }

		//Create an iterator called temp to traverse the list
                node_t* temp = l->head;

		//Traverse through the list
                for (int i = 0; i < pos; i++){
                        temp = temp->next;
                }

		//Add the new node into the list by updating the fields
                new_node->previous = temp->previous;
                new_node->next = temp;
                temp->previous = new_node;
                new_node->previous->next = new_node;
                l->count++;

                return 1;
        }
}

// Returns the item at position pos starting at 0 ( 0 being the first item )
// Returns -1 if the list is NULL
//  (does not remove the item)
// Returns 0 on failure:
//  * we tried to get at a negative location.
//  * we tried to get past the size of the list
// Assume no negative numbers in the list or the number zero.
void* dll_get(dll_t* l, int pos){
    // TODO: Implement me!!

	//Null check on function parameter
        if (l == NULL){
                return NULL;
        }

	//Exit the program if the position parameter is negative or greater than
	//or equal to the size of the DLL.
        else if (pos < 0 || pos >= l->count){
                return NULL;
        }

        else {

		//Create an iterator called temp to traverse the list
                node_t* temp = l->head;

		//Traverse the list
                for (int i = 0; i < pos; i++){
                        temp = temp->next;
                }

                return temp->data;

        }
}

// Removes the item at position pos starting at 0 ( 0 being the first item )
// Returns -1 if the list is NULL
// Returns 0 on failure:
//  * we tried to remove at a negative location.
//  * we tried to remove get past the size of the list
// Assume no negative numbers in the list or the number zero.
void* dll_remove(dll_t* l, int pos){
    // TODO: Implement me!!

	//Null check on function parameter
        if (l == NULL){
                return NULL;
        }       
        
	//Exit the program if position parameter is negative or greater than 
	//or equal to the size of the DLL.
        else if (pos < 0 || pos >= l->count){
                return NULL;
        }       
        
	//If the position is at the start of the list, invoke the pop_front function
        else if (pos == 0){
                return dll_pop_front(l);
        }       
        
	//If the position is at the rear of the list, invoke the pop_back function
        else if (pos == l->count - 1){
                return dll_pop_back(l);
        }       
        
        else {
        
		//Create an iterator called temp to traverse the list
                node_t* temp = l->head;

		//Traverse through the list               
                for (int i = 0; i < pos; i++){
                        temp = temp->next;
                }       
                
		//Update the fields of the adjacent nodes
                int* data = temp->data;
                temp->previous->next = temp->next;
                temp->next->previous = temp->previous;
                free(temp);
                l->count--;
                
                return data;
        }       
}

// DLL Size
// Returns -1 if the DLL is NULL.
// Queries the current size of a DLL
int dll_size(dll_t* t){
    // TODO: Implement me!!

	//Null check on function parameter
        if (t == NULL){
                return -1;
        }
        return t->count;
        
}

// Free DLL
// Removes a DLL and all of its elements from memory.
// This should be called before the proram terminates.
void free_dll(dll_t* t){
    // TODO: Implement me!!    

	//Null check on function parameter
        if (t == NULL){
                return;
        }

	//Create an interator called current and next, and use them to traverse the list and
	//free each node until the DLL is empty.
        node_t* current = t->head;
        while (current != NULL){
                node_t* next = current;
                current = current->next;
                free(next);
        }
        free(t);
};

#endif
