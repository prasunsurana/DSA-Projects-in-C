// Compile this assignment with: gcc -Wall main.c -o main
// Use this file to create several grpahs and show that your implementation
// of Dijkstra's shortest path algorithm works!
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_graph.h"
#include "my_shortest.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.

int main(int argc, const char * argv[]) {
 
	//TEST 1
	graph_t * graph = create_graph();
    	graph_add_node(graph, 5);
   	graph_add_node(graph, 7);
	graph_add_node(graph, 3);
	graph_add_node(graph, 8);
	graph_add_node(graph, 1);
	graph_add_node(graph, 0);
	graph_add_node(graph, 2);
	graph_add_node(graph, 6);
	graph_add_node(graph, 4);
	graph_add_edge(graph, 0, 1, 4);
	graph_add_edge(graph, 0, 2, 8);
	graph_add_edge(graph, 1, 2, 11);
	graph_add_edge(graph, 1, 3, 9);
	graph_add_edge(graph, 3, 2, 7);
	graph_add_edge(graph, 3, 4, 2);
	graph_add_edge(graph, 3, 5, 6);
	graph_add_edge(graph, 4, 1, 8);
	graph_add_edge(graph, 4, 6, 7);
	graph_add_edge(graph, 4, 7, 4);
	graph_add_edge(graph, 2, 5, 1);
	graph_add_edge(graph, 5, 4, 5);
	graph_add_edge(graph, 6, 7, 14);
	graph_add_edge(graph, 6, 8, 9);
	graph_add_edge(graph, 5, 7, 2);
	graph_add_edge(graph, 7, 8, 10);
	calculate_shortest_path(graph, 1);

	print_shortest_path(graph, 1, 7); 
	

	printf("total edges: %d \n", graph_num_edges(graph));
        printf("total nodes: %d\n", graph_num_nodes(graph));

	free_graph(graph);

	//TEST 2
	graph_t * testgraph = create_graph();
	graph_add_node(testgraph, 5);
        graph_add_node(testgraph, 7);
        graph_add_node(testgraph, 3);
        graph_add_node(testgraph, 8);
        graph_add_node(testgraph, 1);
        graph_add_node(testgraph, 9);
        graph_add_node(testgraph, 2);
        graph_add_node(testgraph, 6);
        graph_add_node(testgraph, 4);
	graph_add_edge(testgraph, 1, 2, 8);
	graph_add_edge(testgraph, 1, 6, 13);
	graph_add_edge(testgraph, 1, 3, 3);
	graph_add_edge(testgraph, 2, 3, 2);
	graph_add_edge(testgraph, 2, 4, 1);
	graph_add_edge(testgraph, 3, 2, 3);
	graph_add_edge(testgraph, 3, 4, 9);
	graph_add_edge(testgraph, 3, 5, 2);
	graph_add_edge(testgraph, 4, 5, 4);
	graph_add_edge(testgraph, 4, 8, 2);
	graph_add_edge(testgraph, 4, 7, 6);
	graph_add_edge(testgraph, 5, 4, 6);
	graph_add_edge(testgraph, 5, 1, 5);
	graph_add_edge(testgraph, 5, 6, 5);
	graph_add_edge(testgraph, 5, 9, 4);
	graph_add_edge(testgraph, 6, 9, 7);
	graph_add_edge(testgraph, 6, 7, 1);
	graph_add_edge(testgraph, 7, 8, 4);
	graph_add_edge(testgraph, 8, 9, 1);
	graph_add_edge(testgraph, 9, 7, 5);

	calculate_shortest_path(testgraph, 1);
	
	print_shortest_path(testgraph, 1, 7);
		
	printf("total edges: %d \n", graph_num_edges(testgraph));
	printf("total nodes: %d\n", graph_num_nodes(testgraph));

	free_graph(testgraph);

    	return 0;
}
