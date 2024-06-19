// Compile this assignment with: gcc -Wall main.c -o main
// Use this file to create several grpahs and show that your implementation
// of Kruskal's minimum spanning tree algorithm works!
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_dll.h"
#include "my_graph.h"
#include "my_mst.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.

int main(int argc, const char * argv[]) {

	graph_t * graph = create_graph();
	graph_add_node(graph, 0);
	graph_add_node(graph, 1);
	graph_add_node(graph, 2);
	graph_add_node(graph, 3);
	graph_add_node(graph, 4);
	graph_add_node(graph, 5);
	graph_add_node(graph, 6);
	graph_add_node(graph, 7);
	graph_add_node(graph, 8);
	graph_add_edge(graph, 0, 1, 4);
	graph_add_edge(graph, 0, 7, 8);
	graph_add_edge(graph, 1, 7, 11);
	graph_add_edge(graph, 1, 2, 8);
	graph_add_edge(graph, 7, 8, 7);
	graph_add_edge(graph, 7, 6, 1);
	graph_add_edge(graph, 2, 8, 2);
	graph_add_edge(graph, 2, 3, 7);
	graph_add_edge(graph, 2, 5, 4);
	graph_add_edge(graph, 6, 8, 6);
	graph_add_edge(graph, 5, 6, 2);
	graph_add_edge(graph, 5, 4, 10);
	graph_add_edge(graph, 3, 5, 14);
	graph_add_edge(graph, 3, 4, 9);

	dll_t* mst = calculate_mst(graph);

	for (int i = 0; i < mst->count; i++){
		graph_edge_t* graphEdge = (graph_edge_t*)dll_get(mst, i);
		printf("%d -> %d	cost: %d \n", graphEdge->from, graphEdge->to, graphEdge->cost);
	}

	free_graph(graph);
	free_dll(mst);

	printf("\n \n \n \n");

	graph_t * testgraph = create_graph();
	graph_add_node(testgraph, 0);
	graph_add_node(testgraph, 1);
	graph_add_node(testgraph, 2);
	graph_add_node(testgraph, 3);
	graph_add_node(testgraph, 4);
	graph_add_node(testgraph, 5);
	graph_add_node(testgraph, 6);
	graph_add_node(testgraph, 7);
	graph_add_node(testgraph, 8);
	graph_add_edge(testgraph, 0, 1, 4);
	graph_add_edge(testgraph, 0, 2, 8);
	graph_add_edge(testgraph, 1, 2, 11);
	graph_add_edge(testgraph, 1, 4, 8);
	graph_add_edge(testgraph, 1, 3, 9);
	graph_add_edge(testgraph, 2, 3, 7);
	graph_add_edge(testgraph, 2, 5, 1);
	graph_add_edge(testgraph, 3, 4, 2);
	graph_add_edge(testgraph, 3, 5, 6);
	graph_add_edge(testgraph, 4, 5, 5);
	graph_add_edge(testgraph, 4, 6, 7);
	graph_add_edge(testgraph, 4, 7, 4);
	graph_add_edge(testgraph, 5, 7, 2);
	graph_add_edge(testgraph, 6, 7, 14);
	graph_add_edge(testgraph, 6, 8, 9);
	graph_add_edge(testgraph, 7, 8, 10);

	dll_t* mst2 = calculate_mst(testgraph);

	for (int i = 0; i < mst2->count; i++){
                graph_edge_t* graphEdge = (graph_edge_t*)dll_get(mst2, i);
                printf("%d -> %d        cost: %d \n", graphEdge->from, graphEdge->to, graphEdge->cost);
        }

	free_graph(testgraph);
	free_dll(mst2);

	printf("\n \n \n \n");

	graph_t * testgraph2 = create_graph();	
	graph_add_node(testgraph2, 0);
	graph_add_node(testgraph2, 1);
	graph_add_node(testgraph2, 2);
	graph_add_node(testgraph2, 3);
	graph_add_node(testgraph2, 4);
	graph_add_node(testgraph2, 5);
	graph_add_node(testgraph2, 6);
	graph_add_node(testgraph2, 7);
	graph_add_node(testgraph2, 8);
	graph_add_node(testgraph2, 9);
	graph_add_node(testgraph2, 10);
	graph_add_node(testgraph2, 11);
	graph_add_node(testgraph2, 12);
	graph_add_node(testgraph2, 13);
	graph_add_node(testgraph2, 14);
	graph_add_node(testgraph2, 15);
	graph_add_edge(testgraph2, 0, 1, 2);
	graph_add_edge(testgraph2, 0, 3, 7);
	graph_add_edge(testgraph2, 0, 15, 3);
	graph_add_edge(testgraph2, 1, 2, 4);
	graph_add_edge(testgraph2, 2, 5, 4);
	graph_add_edge(testgraph2, 3, 5, 3);
	graph_add_edge(testgraph2, 3, 7, 3);
	graph_add_edge(testgraph2, 3, 13, 6);
	graph_add_edge(testgraph2, 3, 14, 5);
	graph_add_edge(testgraph2, 4, 5, 9);
	graph_add_edge(testgraph2, 5, 6, 9);
	graph_add_edge(testgraph2, 5, 8, 12);
	graph_add_edge(testgraph2, 5, 9, 14);
	graph_add_edge(testgraph2, 6, 12, 13);
	graph_add_edge(testgraph2, 6, 13, 10);
	graph_add_edge(testgraph2, 7, 13, 1);
	graph_add_edge(testgraph2, 8, 10, 16);
	graph_add_edge(testgraph2, 9, 10, 4);
	graph_add_edge(testgraph2, 10, 11, 6);
	graph_add_edge(testgraph2, 11, 12, 19);
	graph_add_edge(testgraph2, 13, 14, 2);

	dll_t* mst3 = calculate_mst(testgraph2);

	for (int i = 0; i < mst3->count; i++){
                graph_edge_t* graphEdge = (graph_edge_t*)dll_get(mst3, i);
                printf("%d -> %d        cost: %d \n", graphEdge->from, graphEdge->to, graphEdge->cost);
        }

        free_graph(testgraph2);
        free_dll(mst3);









	return 0;
}
