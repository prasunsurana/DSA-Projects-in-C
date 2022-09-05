// =================== Support Code =================
// Priority Queue
//
// - Implementation of the functions to create a working circular queue.
// - This similar to the queue that we built in HW 2 except that elements
//   are dequeue in order of "priority". We will be implementing it so that
//   elements with the lowest cost are the ones that are dequeued first.
// - Do not change any of the function declarations
//   - (i.e. queue_t* create_queue(unsigned int _capacity) should not have additional arguments)
// - You should not have any 'printf' statements in your queue functions. 
//   - (You may consider using these printf statements to debug, 
//     but they should be removed from your final version)
// ==================================================
#ifndef MYPQ_H
#define MYPQ_H

#include "my_graph.h"

// The main data structure for the queue
struct queue {
	unsigned int back;	    // The next free position in the queue
				    		// (i.e. the end or tail of the line)
	unsigned int front;	    // Current 'head' of the queue
				    		// (i.e. the front or head of the line)
	unsigned int size;	    // How many total elements we currently have enqueued.
	unsigned int capacity;  // Maximum number of items the queue can hold
	graph_node_t** data; 	// The data our queue holds	
};
// Creates a global definition of 'queue_t' so we 
// do not have to retype 'struct queue' everywhere.
typedef struct queue queue_t;

// Create a queue
// Returns a pointer to a newly created queue.
// The queue should be initialized with data on
// the heap.
queue_t* create_queue(unsigned int _capacity){

	// TODO: Implement me!

	//Allocate memory for a new queue
	queue_t* myQueue = (queue_t*)malloc(sizeof(queue_t));

	//Check whether malloc was unable to allocate memory
	if (myQueue == NULL){
		return NULL;
	}

	//Initialize the queue's fields
	myQueue->back = 0;
	myQueue->front = 0;
	myQueue->size = 0;
	myQueue->capacity = _capacity;

	//Allocate memory for the data held by the queue
	myQueue->data = (graph_node_t**)malloc(sizeof(graph_node_t*)*myQueue->capacity);

	//Check if malloc was unable to allocate memory
	if (myQueue->data == NULL){
		return NULL;
	}

	return myQueue;
}

// Queue Empty
// Check if the queue is empty
// Returns 1 if true (The queue is completely empty)
// Returns 0 if false (the queue has at least one element enqueued)
int queue_empty(queue_t* q){
	// TODO: Implement me!

	//Null check on function parameter
	if (q == NULL){
		return -1;
	}

	if (q->size > 0){
		return 0;
	}

	return 1;

}

// Queue Full
// Check if the queue is Full
// Returns 1 if true (The queue is completely full)
// Returns 0 if false (the queue has more space available to enqueue items)
int queue_full(queue_t* q){
	// TODO: Implement me!

	//Null check on function parameter
	if (q == NULL){
		return -1;
	}

	if (q->size == q->capacity){
		return 1;
	}

	return 0;
}

// Enqueue a new node
// i.e. push a new item into our data structure
// Returns a -1 if the operation fails (otherwise returns 0 on success).
// (i.e. if the queue is full that is an error).
int queue_enqueue(queue_t* q, graph_node_t* item){
	// TODO: Implement me!

	//Null check on function parameters
	if (q == NULL || item == NULL){
		return -9999;
	}

	//If the queue is full, exit the function
	else if (queue_full(q) == 1){
		return -1;
	}

	//Enqueue the item
	else {
		q->data[q->back] = item;
		q->back = (q->back + 1) % q->capacity;
		q->size++;
		return 0;
	}

	return -1;

}

// Dequeue the node that has the minimum cost
// Returns the item at the front of the queue and
// removes an item from the queue.
// Removing from an empty queue should crash the program, call exit(1)
graph_node_t* queue_dequeue(queue_t *q){
	// TODO: Implement me!

	//Null check on function parameter
	if (q == NULL){
		return NULL;
	}

	//Crash the program if attempting to dequeue from an empty queue
	if (queue_empty(q) == 1){
		exit(1);
	}

	int toRemove = q->front;

	//Find the item with the lowest cost
	for (int i = toRemove; i < q->back; i++){ 
		if (q->data[i]->cost < q->data[toRemove]->cost){
			toRemove = i;
		}
	}

	//Dequeue the item with the lowest cost and adjust the array
	graph_node_t* minVertex = q->data[toRemove];
	q->data[toRemove] = NULL;

	int i;
	for (i = toRemove + 1; i < q->back; i++){
		q->data[i - 1] = q->data[i];
	}

	q->data[i] = NULL;
	q->back = (q->back - 1 + q->capacity) % q->capacity;  
	q->size--;

	return minVertex;

}


// Queue Size
// Queries the current size of a queue
// A queue that has not been previously created will crash the program.
// (i.e. A NULL queue cannot return the size, call exit(1))
unsigned int queue_size(queue_t* q){
	// TODO: Implement me!

	//Null check on function parameter
	if (q == NULL){
		exit(1);
	}

	return q->size;
}


// Free queue
// Removes a queue and all of its elements from memory.
// This should be called before the program terminates.
void free_queue(queue_t* q){
	// TODO: Implement me!

	//Null check on function parameter
	if (q == NULL){
		return;
	}

	free(q->data);

	free(q);
	return;

}


#endif
