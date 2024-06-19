// =================== Support Code =================
// Minimum Spanning Tree
//
// - Implement each of the functions to calculate a
//   minimum spanning tree.
// - You should not have any 'printf' statements in your graph functions.
//   - (You may consider using these printf statements to debug, but they 
//      should be removed from your final version)
// ==================================================
#ifndef MYMST_H
#define MYMST_H

#include <stdlib.h>
#include <assert.h>

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_dll.h"
#include "my_graph.h"
#include "my_pq.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.


// returns a doubly-linked list of graph edges that 
//    make up the minimimum spanning tree
// returns NULL on failure:
//   * if the graph is NULL
//   * if Kruskal's algorithm does not complete successfully

int change_to_min(graph_t* g, int nodeSet[], graph_edge_t* graphEdge);

dll_t* calculate_mst(graph_t * g) {

	//Null check on function parameter
	if (g == NULL){
		return NULL;
	}

	//Create an empty DLL to hold the edges in our Minimum Spanning Tree
	dll_t* mst = create_dll();

	//Create a node set. The node set values are initialize starting at 0, not 1, so the nodes that are added into the graph must also
	//start from 0. 
	int nodeSet[g->numNodes];

	for (int i = 0; i < g->numNodes; i++){
		nodeSet[i] = i;
	}

	//Create a priority queue
	queue_t* q = create_queue(2*g->numEdges + 1);

	//Enqueue all edges in the graph into the priority queue
	for (int i = 0; i < g->numNodes; i++){
		graph_node_t* graphNode = (graph_node_t*)dll_get(g->nodes, i);
		for (int j = 0; j < graphNode->outNeighbors->count; j++){
			graph_edge_t* graphEdge = (graph_edge_t*)dll_get(graphNode->outNeighbors, j);
			queue_enqueue(q, graphEdge);
		}
	}
/*
	for (int k = 0; k < q->size; k++){
		printf("%d -> %d	cost: %d \n", q->data[k]->from, q->data[k]->to, q->data[k]->cost);
	}
*/
	while (queue_empty(q) != 1){
		graph_edge_t* minEdge = queue_dequeue(q);
		if (nodeSet[minEdge->from] != nodeSet[minEdge->to]){
			dll_push_back(mst, minEdge);
			change_to_min(g, nodeSet, minEdge);
		}
	}

	free_queue(q);
	return mst;
}

int change_to_min(graph_t* g, int nodeSet[], graph_edge_t* graphEdge){

	//Null check on function parameter
	if (graphEdge == NULL){
		return -1;
	}

	int temp = nodeSet[graphEdge->to];

	if (nodeSet[graphEdge->from] < nodeSet[graphEdge->to]){
		for (int i = 0; i < g->numNodes; i++){
			if (nodeSet[i] == temp){
				nodeSet[i] = nodeSet[graphEdge->from];
			}
		}
	}

	int temp2 = nodeSet[graphEdge->from];

	if (nodeSet[graphEdge->from] > nodeSet[graphEdge->to]){
		for (int j = 0; j < g->numNodes; j++){
			if (nodeSet[j] == temp2){
				nodeSet[j] = nodeSet[graphEdge->to];
			}
		} 
        }

	return 0;

}


#endif
