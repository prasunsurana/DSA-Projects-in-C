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
#ifndef MYSHORTEST_H
#define MYSHORTEST_H

#include <stdlib.h>
#include <assert.h>

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_graph.h"
#include "my_pq.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.


// returns 1 if Dijkstra's algorithm completes successfully
// returns 0 if Dikjstra's algorithm does not complete successfully
// NOTE: Recall from our discussion, Dikjstra's algorithm does not
//       handle negative weight edges
// returns -1 if the graph is NULL
int calculate_shortest_path(graph_t * g, int source) {
	// TODO: Implement me!!

	//Null check on function parameter, or if the source node does not exist
	if (g == NULL || find_node(g, source) == NULL){
		return -1;
	}

	g->source = source;

	//Dijkstra's Algorithm fails when there are negative weights in the graph. Check all edges to verify that all weights are positive.
	for (int i = 0; i < g->numNodes; i++){
		graph_node_t* nodeCheck = (graph_node_t*)dll_get(g->nodes, i);
		for (int j = 0; j < nodeCheck->outNeighbors->count; j++){
			graph_edge_t* edgeCheck = (graph_edge_t*)dll_get(nodeCheck->outNeighbors, j);
			if (edgeCheck->cost < 0){
				return 0;
			}
		}
	}

	//Create a priority queue
	queue_t* q = create_queue(g->numNodes+1);

	for (int i = 0; i < g->numNodes; i++){
		graph_node_t* graphNode = (graph_node_t*)dll_get(g->nodes, i);
		if (graphNode->data != source){
			graphNode->cost = INFINITY;
			graphNode->from = -1;
			queue_enqueue(q, graphNode);
		}
	}

	//Save the source as a node, set its cost to 0 and enqueue it
	graph_node_t* sourceNode = find_node(g, source);
	sourceNode->cost = 0;
	queue_enqueue(q, sourceNode);

	while (queue_empty(q) != 1){
		graph_node_t* vertex = queue_dequeue(q);
		for (int i = 0; i < vertex->outNeighbors->count; i++){
			graph_edge_t* outNeighborEdge = (graph_edge_t*)dll_get(vertex->outNeighbors, i);
			graph_node_t* outNeighborNode = find_node(g, outNeighborEdge->to);
			int totalcost = vertex->cost + outNeighborEdge->cost;
			if (totalcost < outNeighborNode->cost){
				outNeighborNode->cost = totalcost;
				outNeighborNode->from = vertex->data;
			}
		}
	}	

	free_queue(q);
	return 1;

}

// prints the shortest path from source to destination if there
// exists a path from the source to the destination. Consider
// how you can solve this recursively if you want to avoid using
// another data structure.
//
// Returns 1 if there is a path from source to destination
// Returns 0 if there is not a path from source to destination
// Returns -1 if the graph is NULL
// Returns -2 if called before `calculate_shortest_path` is called
// Note: consider the bookkeeping fields in `graph_t` struct to
//       determine whether this is true or not
int print_shortest_path(graph_t * g, int source, int dest) {
	// TODO: Implement me!

	//Null check on function parameter
	if (g == NULL){
		return -1;
	}

	//Check if source and destination nodes exist
	if (find_node(g, source) == NULL || find_node(g, dest) == NULL){
		return -1;
	}

	//Check if the function has been called before the calculate_shortest_path function
	if (g->source != source){
		return -2;
	}

	//Save dest as a node
	graph_node_t* destNode = find_node(g, dest);
	
	print_shortest_path(g, source, destNode->from);

	printf("%d -> ", destNode->data);
	return 1;	

}
#endif
