#ifndef MYGRAPH_H
#define MYGRAPH_H

#include "my_dll.h"
#include <stdlib.h>
#include <assert.h>

//Create a graph data structure
typedef struct graph{
    int numNodes;
    int numEdges;
    dll_t* nodes; //an array of nodes storing all our nodes
} graph_t;

typedef struct graph_node{
    int data;
    int visited;
    dll_t* inNeighbors;
    dll_t* outNeighbors;
} graph_node_t;

//FUNCTION DECLARATIONS
graph_t* create_graph();
graph_node_t* find_node( graph_t * g, int value);
graph_node_t * create_graph_node(int value);
int graph_add_node(graph_t* g, int value);
int graph_remove_node(graph_t* g, int value);
int graph_add_edge(graph_t * g, int source, int destination);
int graph_remove_edge(graph_t * g, int source, int destination);
int contains_edge( graph_t * g, int source, int destination);
int graph_is_reachable(graph_t * g, int source, int dest);
int graph_has_cycle(graph_t * g);
int graph_print_path(graph_t * g, int source, int dest);
int printHelper(graph_t* g, int source, int dest, dll_t* path);
dll_t* getInNeighbors( graph_t * g, int value );
int getNumInNeighbors( graph_t * g, int value);
dll_t* getOutNeighbors( graph_t * g, int value);
int getNumOutNeighbors( graph_t * g, int value);
int graph_num_nodes(graph_t* g);
int graph_num_edges(graph_t* g);
void free_graph(graph_t* g);

graph_t* create_graph(){

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

graph_node_t * create_graph_node(int value){

	//Allocate memory for a new node
	graph_node_t * graph_node = malloc(sizeof(graph_node_t));

	//Check if malloc was unable to allocate memory
	if ( graph_node == NULL ){
                return NULL;
        }

        //Initialize the new node's fields
        graph_node->data = value;
	graph_node->visited = 0;
        graph_node->inNeighbors = create_dll();
        graph_node->outNeighbors = create_dll();

        return graph_node;
}

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


int graph_remove_node(graph_t* g, int value){

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

int graph_add_edge(graph_t * g, int source, int destination){

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

int graph_remove_edge(graph_t * g, int source, int destination){

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

int contains_edge( graph_t * g, int source, int destination){

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

//Returns 1 if we can reach the destination from the source
//Returns 0 if not reachable
//Returns -1 if the graph is NULL
int graph_is_reachable(graph_t * g, int source, int dest){

	//Null check on function parameter
	if (g == NULL){
		return -1;
	}

	//Return -1 if the source and destination nodes don't exist
	if (find_node(g, source) == NULL || find_node(g, dest) == NULL){
                return -1;
        }

	//If source and destination are the same node
	if (source == dest){
		return 1;
	}

	//Before any traversal is done, reset all nodes' 'visited' fields to 0
	for (int i = 0; i < g->numNodes; i++){
		graph_node_t* resetter = (graph_node_t*)dll_get(g->nodes, i);
		resetter->visited = 0;
	}

	//Create a doubly-linked list to hold all the visited nodes. This will act like our queue.
	dll_t* queue = create_dll();

	//Save the source and destination as nodes
	graph_node_t* sourceNode = find_node(g, source);

	//Add the source node to the queue, since this is the first node we will inspect
	dll_push_back(queue, sourceNode);

	while (queue->count != 0){
		graph_node_t* iterqueue = (graph_node_t*)dll_get(queue, 0);
		iterqueue->visited = 1;
		for (int i = 0; i < iterqueue->outNeighbors->count; i++){
			graph_node_t* temp = (graph_node_t*)dll_get(iterqueue->outNeighbors, i);
			if (temp->data == dest){
				free_dll(queue);
				return 1;
			}
			if (temp->visited == 0){
				dll_push_back(queue, temp);
			}
		}
		dll_pop_front(queue);
	}			


	free_dll(queue);

	//Reset all nodes' 'visited' fields back to 0
	for (int i = 0; i < g->numNodes; i++){
                graph_node_t* resetter = (graph_node_t*)dll_get(g->nodes, i);
                resetter->visited = 0;
        }

	return 0;

}

//Returns 1 if there is a cycle in the graph
//Returns 0 if no cycles exist in the graph
//Returns -1 if the graph is NULL
int graph_has_cycle(graph_t * g){

	//Null check on function parameter
	if (g == NULL){
		return -1;
	}

	//Iterate through each node, and for each node, see if there is a path between itself and it's inNeighbors. The inNeighbor
	//points to the node, and if there is a path between FROM the node TO the inNeighbor, it indicates the presence of a cycle.
	for (int i = 0; i < g->numNodes; i++){
		graph_node_t* graphNode = (graph_node_t*)dll_get(g->nodes, i);
		int sizeinNeighbors = dll_size(graphNode->inNeighbors);
		for (int j = 0; j < sizeinNeighbors; j++){
			graph_node_t* inneighbor = (graph_node_t*)dll_get(graphNode->inNeighbors, j);
			if (graph_is_reachable(g, graphNode->data, inneighbor->data) == 1){
				return 1;
			}
		}
	}

	return 0;

}

//Returns 1 if there is a path from source to destination
//Returns 0 if there is no path from source to destination
//Returns -1 if the graph is NULL
int graph_print_path(graph_t * g, int source, int dest){

	//Null check on function parameter
	if (g == NULL){
		return -1;
	}

	//Check if source and destination exist. If not, exist the function
	if (find_node(g, source) == NULL || find_node(g, dest) == NULL){
		return -1;
	}

	//Check to see if a path exists between the source and destination nodes
	if (graph_is_reachable(g, source, dest) != 1){
		return 0;
	}

	//Reset all nodes' 'visited' field to 0
	for (int i = 0; i < g->numNodes; i++){
                graph_node_t* resetter = (graph_node_t*)dll_get(g->nodes, i);
                resetter->visited = 0;
        }
	
	//Create a DLL to store all the nodes in our path. The path DLL will act as a stack.
	dll_t* path = create_dll();

	//If a path exists, print the nodes from the path DLL
	if (printHelper(g, source, dest, path) == 1){
		node_t* iter = path->tail;
		for (int i = 0; i < path->count; i ++){
			printf("%d -> ", *(int*)iter->data);
			iter = iter->previous;
		}
		printf("\n");
		return 1;
	}

	free_dll(path);
	return 0;

}

//Returns 1 if a path exists
//Returns 0 if no path exists
int printHelper(graph_t* g, int source, int dest, dll_t* path){

	//Save the source as a node
	graph_node_t* sourceNode = find_node(g, source);

	//Push the source node into the path DLL
	dll_push_front(path, sourceNode);

	while (path->count != 0){
		graph_node_t* iterpath = (graph_node_t*)dll_get(path, 0);
		int fullyVisited = 0;
		for (int i = 0; i < iterpath->outNeighbors->count; i++){ //Tally the number of outNeighbors that have already been visited
			graph_node_t* ifVisited = (graph_node_t*)dll_get(iterpath->outNeighbors, i);
			if (ifVisited->visited == 1){
				fullyVisited++;
			}
		}
		if (fullyVisited == iterpath->outNeighbors->count){ // If all outNeighbors have been visited, mark the node as visited.
			iterpath->visited = 1;			    // Also pop the node from the path DLL since there is nothing more
			dll_pop_front(path);			    // to be explored.
			continue;
		}
		for (int j = 0; j < iterpath->outNeighbors->count; j++){
			graph_node_t* temp = (graph_node_t*)dll_get(iterpath->outNeighbors, j);
			if (temp->data == dest){ //If the destination node is found, add it to the path DLL
				dll_push_front(path, temp);
				return 1;
			}
			if (temp->outNeighbors->count == 0){ //If the node has no outNeighbors, i.e. a dead end, continue to next node
				temp->visited = 1;
				continue;
			}
			if (temp->visited == 1){ //If the node has already been visited, continue to the next node
				continue;
			}
			if (temp->visited == 0){ //If the node hasn't been visited, push it to the path stack
				dll_push_front(path, temp);
				break;
			}
		}
	}

		return 0;

}

dll_t* getInNeighbors( graph_t * g, int value ){

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

int getNumInNeighbors( graph_t * g, int value){

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

dll_t* getOutNeighbors( graph_t * g, int value ){

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

int getNumOutNeighbors( graph_t * g, int value){

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

int graph_num_nodes(graph_t* g){

	//Null check on function parameter
	if (g == NULL){
                return -1;
        }

        return g->numNodes;
}

int graph_num_edges(graph_t* g){

	//Null check on function parameter
	if (g == NULL){
                return -1;
        }

        return g->numEdges;
}

void free_graph(graph_t* g){

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
