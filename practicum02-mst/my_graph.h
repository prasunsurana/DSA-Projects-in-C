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
typedef struct graph {
    int numNodes;
    int numEdges;
    dll_t* nodes;   // a list of nodes storing all of our nodes
} graph_t;

typedef struct graph_node {
    int data;
    // per-node neighbor information which now stores edges instead of nodes
    dll_t* inNeighbors;
    dll_t* outNeighbors;
} graph_node_t;


typedef struct graph_edge {
    int from;
    int to;
    int cost;
} graph_edge_t;

//FUNCTION DECLARATIONS
graph_t* create_graph();
graph_node_t* find_node(graph_t* g, int value);
graph_node_t* create_graph_node(int value);
int graph_add_node(graph_t* g, int value);
int graph_remove_node(graph_t* g, int value);
int graph_add_edge(graph_t * g, int source, int destination, int cost);
int graph_remove_edge(graph_t* g, int source, int destination);
int contains_edge(graph_t* g, int source, int destination);
graph_edge_t* graph_get_edge(graph_t* g, int source, int destination);
dll_t* getInNeighbors(graph_t* g, int value );
int getNumInNeighbors(graph_t* g, int value);
dll_t* getOutNeighbors(graph_t* g, int value);
int getNumOutNeighbors(graph_t* g, int value);
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

	//Allocate memory to a new graph
	graph_t* myGraph= (graph_t*)malloc(sizeof(graph_t));

        //Check whether malloc was unable to allocate memory
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

	//Allocate memory to a new graph node
	graph_node_t * graph_node = (graph_node_t*)malloc(sizeof(graph_node_t));

        //Check if malloc was unable to allocate memory
        if (graph_node == NULL){
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
                return -1;
        }

        //Allocate memory for a new graph node
        graph_node_t * newNode = create_graph_node(value);

        //Check if malloc was unable to allocate memory
        if (newNode == NULL){
                return -1;
        }

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

	//Check if the node exists
	if (find_node(g, value) == NULL){
		return 0;
	}

	//REMOVE THE NODE FROM ITS OUTNEIGHBORS' INNEIGHBOR DLLS
	
		//Store the value node's outNeighbors DLL 
		dll_t* nodeOutNeighbors = getOutNeighbors(g, value);

                int nodeOutsize = dll_size(nodeOutNeighbors);

                for (int i = 0; i < nodeOutsize; i++){
                        graph_edge_t* edgeOut = (graph_edge_t*)dll_get(nodeOutNeighbors, i);
                        graph_node_t* nodeOut = find_node(g, edgeOut->to);
                        for (int j = 0; j < nodeOut->inNeighbors->count; j++){
                                graph_edge_t* edgeOutIn = (graph_edge_t*)dll_get(nodeOut->inNeighbors, j);
                                if (edgeOutIn->from == value){
                                        if (dll_remove(nodeOut->inNeighbors, j) != NULL){
                                                free(edgeOut);
                                                g->numEdges--;
                                                break;
                                        }
                                }
                        }
                }

        //REMOVE THE NODE FROM ITS INNEIGHBORS' OUTNEIGHBOR DLLS
        
		//Store the value node's inNeighbors DLL
		dll_t* nodeInNeighbors = getInNeighbors(g, value);

                int nodeInsize = dll_size(nodeInNeighbors);

                for (int i = 0; i < nodeInsize; i++){
                        graph_edge_t* edgeIn = (graph_edge_t*)dll_get(nodeInNeighbors, i);
                        graph_node_t* nodeIn = find_node(g, edgeIn->from);
                        for (int j = 0; j < nodeIn->outNeighbors->count; j++){
                                graph_edge_t* edgeInOut = (graph_edge_t*)dll_get(nodeIn->outNeighbors, j);
                                if (edgeInOut->to == value){
                                        if (dll_remove(nodeIn->outNeighbors, j) != NULL){
                                                free(edgeIn);
                                                g->numEdges--;
                                                break;
                                        }
                                }
                        }
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

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge already exists )
// Returns -1 if the graph is NULL.
int graph_add_edge(graph_t * g, int source, int destination, int cost){
    // TODO: Implement me!
    // The function adds an edge from source to destination but not the other way.
    // Make sure you are not adding the same edge multiple times.
    // Make sure you modify the in and out neighbors appropriatelly. destination will be an out neighbor of source.
    // Source will be an in neighbor of destination.

	//Null check on function parameter
	if (g == NULL){
		return -1;
	}

	//Save the source and destination as nodes
	graph_node_t* sourceNode = find_node(g, source);
	graph_node_t* destNode = find_node(g, destination);

	//Check if source and destination exist, or if the edge already exists
	if (sourceNode == NULL || destNode == NULL || contains_edge(g, source, destination) == 1){
		return 0;
	}

	//Allocate memory for a new edge
	graph_edge_t* newEdge = (graph_edge_t*)malloc(sizeof(graph_node_t));

	//Check if malloc was unable to allocate memory
	if (newEdge == NULL){
		return -1;
	}

	//Initialize fields for the new edge
	newEdge->from = source;
	newEdge->to = destination;
	newEdge->cost = cost;

	//Add the edge to the sourceNode's outNeighbors DLL and the destNode's inNeighbors DLL
	if (dll_push_back(sourceNode->outNeighbors, newEdge) != 1){
		return 0;
	}
	if (dll_push_back(destNode->inNeighbors, newEdge) != 1){
		return 0;
	}

	//Create a second edge to go from the destination to the source
	graph_edge_t* newEdge2 = (graph_edge_t*)malloc(sizeof(graph_node_t));

	//Check if malloc was unable to allocate memory
	if (newEdge2 == NULL){
                return -1;
        }       

	newEdge2->from = destination;
	newEdge2->to = source;
	newEdge2->cost = cost;

	//Add the edge to the destNode's outNeighbors and sourceNode's inNeighbors
	if (dll_push_back(destNode->outNeighbors, newEdge2) != 1){
		return 0;
	}

	if (dll_push_back(sourceNode->inNeighbors, newEdge2) != 1){
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

	//Save source and destination as nodes
	graph_node_t* sourceNode = find_node(g, source);
	graph_node_t* destNode = find_node(g, destination);

	//Check if the node and destination exist, or if the edge does not exist
	if (sourceNode == NULL || destNode == NULL || contains_edge(g, source, destination) != 1){
		return 0;
	}

	//REMOVE THE EDGE FROM THE DESTINATION'S INNEIGHBORS LIST
	int destInSize = dll_size(destNode->inNeighbors);

        for (int i = 0; i < destInSize; i++){
                graph_edge_t* inEdge = (graph_edge_t*)dll_get(destNode->inNeighbors, i);
                if (inEdge->from == source){
                        if (dll_remove(destNode->inNeighbors, i) ==  NULL){
                                return 0;
                        }
                        else {  
                                break;
                        }
                }
        }


        //REMOVE THE EDGE FROM THE SOURCE'S OUTNEIGHBORS LIST
        int sourceOutSize = dll_size(sourceNode->outNeighbors);

        for (int j = 0; j < sourceOutSize; j++){
                graph_edge_t* outEdge = (graph_edge_t*)dll_get(sourceNode->outNeighbors, j);
                if (outEdge->to == destination){
                        if (dll_remove(sourceNode->outNeighbors, j) == NULL){
                                return 0;
                        }
                        else {
                                free(outEdge);
                                break;
                        }
                }
        }

	//REMOVE THE EDGE FROM THE DESTINATION'S OUTNEIGHBORS LIST
	int destOutSize = dll_size(destNode->outNeighbors);

	for (int i = 0; i < destOutSize; i++){
		graph_edge_t* outEdge2 = (graph_edge_t*)dll_get(destNode->outNeighbors, i);
		if (outEdge2->to == source){
			if (dll_remove(destNode->outNeighbors, i) == NULL){
				return 0;
			}
			else {
				break;
			}
		}
	}

	//REMOVE THE EDGE FROM THE SOURCE'S INNEIGHBORS LIST
	int sourceInSize = dll_size(sourceNode->inNeighbors);

	for (int j = 0; j < sourceInSize; j++){
		graph_edge_t* inEdge2 = (graph_edge_t*)dll_get(sourceNode->inNeighbors, j);
			if (inEdge2->from == destination){
				if (dll_remove(sourceNode->inNeighbors, j) == NULL){
					return 0;
				}
				else {
					free(inEdge2);
					break;
				}
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

        //Check if source and destination nodes exist
        if (find_node(g, source) == NULL || find_node(g, destination) == NULL){
                return 0;
        }

        //Save the source as a node
        graph_node_t* sourceNode = find_node(g, source);

        int sizeoutNeighbors = dll_size(sourceNode->outNeighbors);

        //It is sufficient to check just the source's outNeighbors list. We do not have to also check destination's inNeighbors list
        //because by construction, when an edge is created, both point to each other. Hence, to ascertain whether an edge between two nodes
        //exists, it is sufficient to just check one of them. 
        for (int i = 0; i < sizeoutNeighbors; i++){
                graph_edge_t* tempOutNeighbors = (graph_edge_t*)dll_get(sourceNode->outNeighbors, i);
                if (tempOutNeighbors->to == destination){
                        return 1;
                }
        }

        return 0;

}

// Returns a pointer to the edge
// Returns NULL on failure (or if the source or destination nodes don't exist)
// Exits if the graph is NULL (only use this function if the graph `contains_edge` is true)
graph_edge_t* graph_get_edge(graph_t * g, int source, int destination) {
    // TODO: Implement me!

	//Null check on function parameter
	if (g == NULL){
                return NULL;
        }

        //The check to see if the source and destination nodes exist already ocurs in the contains_edge function. Hence, we can
        //just check directly to see if the edge exists between the two nodes.
        if (contains_edge(g, source, destination) != 1){
                return NULL;
        }

        //Save source as a node
        graph_node_t* sourceNode = find_node(g, source);

        int sizeoutNeighbors = dll_size(sourceNode->outNeighbors);

        //Iterate through sourceNode's outNeighbors and find the edge
        for (int i = 0; i < sizeoutNeighbors; i++){
                graph_edge_t* graphEdge = (graph_edge_t*)dll_get(sourceNode->outNeighbors, i);
                if (graphEdge->to == destination){
                        return graphEdge;
                }
        }

        return NULL;

}

// Returns dll_t* of all the in neighbors of this node.
// Returns NULL if thte node doesn't exist or if the graph is NULL.
dll_t* getInNeighbors( graph_t * g, int value ){
    // TODO: Implement me!
    
	//Null check on function parameter
	if (g == NULL){
		return NULL;
	}

	//Save the value as a node
	graph_node_t* node = find_node(g, value);

	//Check if the node exists
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

	//Save the value as a node
	graph_node_t* node = find_node(g, value);

	//Check if the node exists
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

	//Save the value as a node
	graph_node_t* node = find_node(g, value);

	//Check if the node exists
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

	//Save the value as a node
	graph_node_t* node = find_node(g, value);

	//Check if the node exists
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

	for (int i = g->numNodes - 1; i >= 0; i--){
                graph_node_t* graphNode = (graph_node_t*)dll_get(g->nodes, i);
                graph_remove_node(g, graphNode->data);
        }

        free_dll(g->nodes);
        free(g);
        return;


}

#endif
