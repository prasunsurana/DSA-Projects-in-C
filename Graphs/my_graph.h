// =================== Support Code =================
// Graph.
//
// - Implement each of the functions to create a working graph.
// - Do not change any of the function declarations
//   - (i.e. graph_t* create_graph() should not have additional arguments)
// - You should not have any 'printf' statements in your graph functions.
//   - (You may consider using these printf statements to debug, but they 
//      should be removed from your final version)
// ==================================================
#ifndef MYGRAPH_H
#define MYGRAPH_H

#include "my_dll.h"
#include <stdlib.h>
#include <assert.h>
// Create a graph data structure
typedef struct graph{
    int numNodes;
    int numEdges;
    dll_t* nodes;     //an array of nodes storing all of our nodes.
} graph_t;

typedef struct graph_node{
    int data;
    dll_t* inNeighbors;
    dll_t* outNeighbors;
} graph_node_t;

//FUNCTION DECLARATIONs:
graph_t* create_graph();
graph_node_t* find_node( graph_t * g, int value);
graph_node_t * create_graph_node(int value);
int graph_add_node(graph_t* g, int value);
int graph_remove_node(graph_t* g, int value);
int graph_add_edge(graph_t * g, int source, int destination);
int graph_remove_edge(graph_t * g, int source, int destination);
int contains_edge( graph_t * g, int source, int destination);
dll_t* getInNeighbors( graph_t * g, int value );
int getNumInNeighbors( graph_t * g, int value);
dll_t* getOutNeighbors( graph_t * g, int value);
int getNumOutNeighbors( graph_t * g, int value);
int graph_num_nodes(graph_t* g);
int graph_num_edges(graph_t* g);
void free_graph(graph_t* g);

// Creates a graph
// Returns a pointer to a newly created graph.
// The graph should be initialized with data on the heap.
// The graph fields should also be initialized to default values.
// Returns NULL if we cannot allocate memory.
graph_t* create_graph(){
    // Modify the body of this function as needed.

	//Allocate memory to a new graph called myGraph
	graph_t* myGraph= malloc(sizeof(graph_t));

	//Check whether malloc was unable to allocate memory to myGraph
	if (myGraph == NULL){
		return NULL;
	}

	//Initialize the new graph's fields
	myGraph->nodes = create_dll();
	myGraph->numEdges = 0;
	myGraph->numNodes = 0;

	return myGraph;
}

// Returns the node pointer if the node exists.
// Returns NULL if the node doesn't exist or the graph is NULL
graph_node_t* find_node( graph_t * g, int value){

	//Null check on function parameter
	if (g == NULL){
		return NULL;
	}

	//Create a graphNode and iterate through g->nodes until we find the value
	for (int i = 0; i < g->numNodes; i++){
		graph_node_t* graphNode = (graph_node_t*)dll_get(g->nodes, i);
		if (graphNode->data == value){
			return graphNode;
		}
	}

	return NULL; //If the node does not exist, return NULL	

}

// Creates a graph node
// Note: This relies on your dll implementation.
graph_node_t * create_graph_node(int value){

	//Allocate memory for a new node
	graph_node_t * graph_node = malloc(sizeof(graph_node_t));
    
	//Check if malloc was unable to allocate memory
	if ( graph_node == NULL ){ 
		return NULL;
	}

	//Initialize the new node's fields
	graph_node->data = value;
	graph_node->inNeighbors = create_dll();
	graph_node->outNeighbors = create_dll();
    
	return graph_node;
}

// Returns 1 on success
// Returns 0 on failure ( or if the node already exists )
// Returns -1 if the graph is NULL.
int graph_add_node(graph_t* g, int value){

	//Null check on function parameter
	if (g == NULL){ 
		return -1;
	}

	//If the node already exists in the graph, exit the function
	if (find_node(g, value) != NULL){
		return 0;
	}
    
	//Allocate memory for a new node
	graph_node_t * newNode = create_graph_node(value);

	//NOTE: The malloc check is already executed in the create_graph_node function

   
	assert(g->nodes);
	dll_push_back(g->nodes, newNode);
	g->numNodes++;
    
	return 1;
}

// Returns 1 on success
// Returns 0 on failure ( or if the node doesn't exist )
// Returns -1 if the graph is NULL.
int graph_remove_node(graph_t* g, int value){
    // TODO: Implement me!
    // The function removes the node from the graph along with any edges associated with it.
    // That is, this node would have to be removed from all the in and out neighbor's lists that countain it.

	//Null check on function parameter
	if (g == NULL){
		return -1;
	}

	//Return 0 if the node doesn't exist
	if (find_node(g, value) == 0){
 		return 0;
	}

	else {

	//REMOVE THE NODE FROM ITS OUTNEIGHBORS' INNEIGHBOR DLLS

		//Store the value node's outNeighbors DLL 
		dll_t* nodeOut = getOutNeighbors(g, value);

		//Create an iterator to traverse through nodeOut
		node_t* nodeOutTemp = nodeOut->head;

		while (nodeOutTemp != NULL){
			dll_t* nodeOutIn = getInNeighbors(g, *(int*)nodeOutTemp->data); //Save each outNeighbor's inNeighbor as a DLL
			node_t* nodeOutInTemp = nodeOutIn->head; //Create an iterator to traverse that DLL
			for (int i = 0; i < nodeOutIn->count; i++){
				if (*(int*)nodeOutInTemp->data == value){
					if (dll_remove(nodeOutIn, i) != NULL){
						g->numEdges--;
						break;
					}
				}
				else {
					nodeOutInTemp = nodeOutInTemp->next;
				}
			}
			nodeOutTemp = nodeOutTemp->next; //Move on to the next outNeighbor
		}

	//REMOVE THE NODE FROM ITS INNEIGHBOURS' OUTNEIGHBOR DLLS

		//Store the value node's inNeighbors DLL
		dll_t* nodeIn = getInNeighbors(g, value);

		//Create an iterator to traverse through nodeIn
		node_t* nodeInTemp = nodeIn->head;

		while (nodeInTemp != NULL){
			dll_t* nodeInOut = getOutNeighbors(g, *(int*)nodeInTemp->data); //Save each inNeighbor's outNeighbor as a DLL
			node_t* nodeInOutTemp = nodeInOut->head; //Create an iterator to traverse that DLL
			for (int i = 0; i < nodeInOut->count; i++){
				if (*(int*)nodeInOutTemp->data == value){
					if (dll_remove(nodeInOut, i) != NULL){
						g->numEdges--;
						break;
					}
				}
				else {
					nodeInOutTemp = nodeInOutTemp->next;
				}
			}
			nodeInTemp = nodeInTemp->next; //Move on to the next inNeighbour
		}

	//REMOVE NODE FROM THE GRAPH
	
		for (int i = 0; i < g->numNodes; i++){
			graph_node_t* node = (graph_node_t*)dll_get(g->nodes, i);
			if (node->data == value){
				if (dll_remove(g->nodes, i) != NULL){
					free_dll(node->inNeighbors);
					free_dll(node->outNeighbors);
					free(node);
					g->numNodes--;
					break;
				}
			}
		}

	return 1;

	}


}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge already exists )
// Returns -1 if the graph is NULL.
int graph_add_edge(graph_t * g, int source, int destination){
    // TODO: Implement me!
    // The function adds an edge from source to destination but not the other way.
    // Make sure you are not adding the same edge multiple times.
    // Make sure you modify the in and out neighbors appropriatelly. destination will be an out neighbor of source.
    // Source will be an in neighbor of destination.

	//Null check on function parameter
	if (g == NULL){
		return -1;
	}

	//Save the parameters into source and destination nodes
	graph_node_t* sourceNode = find_node(g, source);
	graph_node_t* destNode = find_node(g, destination);

	//Return 0 if source or destination nodes don't exist, or if the edge already exists
	if (sourceNode == NULL || destNode == NULL || contains_edge(g, source, destination) == 1){
		return 0;
	}

	//Add the destination to the end of source's outNeighbors list
	if (dll_push_back(sourceNode->outNeighbors, destNode) != 1){
		return 0;
	}
	
	//Add the source to the end of destination's outNeighbors list
	if (dll_push_back(destNode->inNeighbors, sourceNode) != 1){
		return 0;
	}

	g->numEdges++;
	return 1;
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge doesn't exists )
// Returns -1 if the graph is NULL.
int graph_remove_edge(graph_t * g, int source, int destination){
    // TODO: Implement me!
    //The function removes an edge from source to destination but not the other way.
    //Make sure you remove destination from the out neighbors of source.
    //Make sure you remove source from the in neighbors of destination.

	//Null check on function parameter
	if (g == NULL){
		return -1;
	}

	//Return 0 if the source or destination nodes don't exist, or if the edge doesn't exist
	if (find_node(g, source) == NULL || find_node(g, destination) == NULL || contains_edge(g, source, destination) != 1){
                return 0;
        }

	//Save the source's outNeighbors and destination's inNeighbors as DLLs		
	dll_t* sourceOut = getOutNeighbors(g, source);
	dll_t* destIn = getInNeighbors(g, destination);
	
	//Create iterator to traverse the sourceOut and destIn DLLs
	node_t* sourceOutTemp = sourceOut->head;
	node_t* destInTemp = destIn->head;

	//Remove destination from source's outNeighbors list
	for (int i = 0; i < sourceOut->count; i++){
		if (*(int*)sourceOutTemp->data == destination){
			if (dll_remove(sourceOut, i) != NULL){
				break;
			}
		}
		else {
			sourceOutTemp = sourceOutTemp->next;
		}
	}  

	//Remove source from destination's inNeighbors list
	for (int i = 0; i < destIn->count; i++){
		if (*(int*)destInTemp->data == source){
			if (dll_remove(destIn, i) != NULL){
				break;
			}
		}
		else {
			destInTemp = destInTemp->next;
		}
	} 

	g->numEdges--;
	return 1;

}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist )
// Returns -1 if the graph is NULL.
int contains_edge( graph_t * g, int source, int destination){
    // TODO: Implement me!

	//Null check on function parameter
	if (g == NULL){
		return -1;
	}

	//Store the source and destination nodes
	graph_node_t* sourceNode = find_node(g, source);
	graph_node_t* destNode = find_node(g, destination);

	//Check to see if the source and destination nodes are null
	if (sourceNode == NULL || destNode == NULL){
		return 0;
	}

	int sizeoutNeighbors = dll_size(sourceNode->outNeighbors);

	//It is sufficient to check just the source's outNeighbors list. We do not have to also check destination's inNeighbors list
	//because by construction, when an edge is created, both are executed. Hence, to ascertain whether an edge between two nodes
	//exists, it is sufficient to just check one of them. 
	for (int i = 0; i < sizeoutNeighbors; i++){
		graph_node_t* tempOutNeighbors = (graph_node_t*)dll_get(sourceNode->outNeighbors, i);
		if (tempOutNeighbors->data == destination){
			return 1;
		}
	}

	return 0;

}

// Returns dll_t* of all the in neighbors of this node.
// Returns NULL if thte node doesn't exist or if the graph is NULL.
dll_t* getInNeighbors( graph_t * g, int value ){
    // TODO: Implement me!

	//Null check on function parameter
	if (g == NULL){
		return NULL;
	}

	//Store the value in a graph node
	graph_node_t* node = find_node(g, value);

	//Return NULL if the node doesn't exist
	if (node == NULL){
		return NULL;
	}

	return node->inNeighbors;

}

// Returns the number of in neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumInNeighbors( graph_t * g, int value){
    // TODO: Implement me!

	//Null check on function parameter
	if (g == NULL){
		return -1;
	}

	//Store the value in a graph node
	graph_node_t* node = find_node(g, value);

	//Return -1 if the node does not exist
	if (node == NULL){
		return -1;
	}

	return node->inNeighbors->count;

}

// Returns dll_t* of all the out neighbors of this node.
// Returns NULL if thte node doesn't exist or if the graph is NULL.
dll_t* getOutNeighbors( graph_t * g, int value ){
    // TODO: Implement me!

	//Null check on function parameter
	if (g == NULL){
		return NULL;
	}

	//Store the value in a graph node
	graph_node_t* node = find_node(g, value);

	//Return NULL if the node does not exist
	if (node == NULL){
		return NULL;
	}

	return node->outNeighbors;

}

// Returns the number of out neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumOutNeighbors( graph_t * g, int value){
    // TODO: Implement me!

	//Null check on function parameter
	if (g == NULL){
		return -1;
	}

	//Store the value as a graph node
	graph_node_t* node = find_node(g, value);

	//Exit the function if the node does not exist 
	if (node == NULL){
		return -1;
	}

	return node->outNeighbors->count;
	
}

// Returns the number of nodes in the graph
// Returns -1 if the graph is NULL.
int graph_num_nodes(graph_t* g){
    // TODO: Implement me!

	//Null check on function parameter
	if (g == NULL){
		return -1;
	}

	return g->numNodes;
}

// Returns the number of edges in the graph,
// Returns -1 on if the graph is NULL
int graph_num_edges(graph_t* g){
    // TODO: Implement me!

	//Null check on function parameter
	if (g == NULL){
		return -1;
	}

	return g->numEdges;
}

// Free graph
// Removes a graph and ALL of its elements from memory.
// This should be called before the program terminates.
// Make sure you free all the dll's too.
void free_graph(graph_t* g){
    // TODO: Implement me!

	//Null check on function parameter
	if (g == NULL){
		return;
	}

	for (int i = 0; i < g->numNodes; i++){
		graph_node_t* graphNode = (graph_node_t*)dll_get(g->nodes, i);
		free_dll(graphNode->inNeighbors);
		free_dll(graphNode->outNeighbors);
		free(graphNode);
	}

	free_dll(g->nodes);
	free(g);

}

#endif
