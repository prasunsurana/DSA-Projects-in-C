#include <stdio.h>
#include <stdlib.h>
#include "my_graph.h"

//Adds nodes, adds edges and tests
//number of nodes in graph
int unitTest1(){
        int result = 0;
        graph_t* testGraph = create_graph();
        graph_add_node(testGraph, 1);
        graph_add_node(testGraph, 2);
        graph_add_node(testGraph, 3);
        graph_add_node(testGraph, 4);
        graph_add_node(testGraph, 5);
        graph_add_node(testGraph, 6);
        graph_add_node(testGraph, 7);
        graph_add_node(testGraph, 8);
        graph_add_edge(testGraph, 1, 2, 4);
        graph_add_edge(testGraph, 1, 3, 8);
        graph_add_edge(testGraph, 2, 4, 3);
        graph_add_edge(testGraph, 3, 6, 5);
        graph_add_edge(testGraph, 4, 5, 6);
        graph_add_edge(testGraph, 4, 8, 2);
        graph_add_edge(testGraph, 6, 7, 11);
        graph_add_edge(testGraph, 8, 5, 3);

	if (graph_num_nodes(testGraph) == 8){
		result = 1;
	}

	free_graph(testGraph);
	return result;
}

//Adds nodes, adds edges, removes an edges
//and sees if the graph still contains edge
int unitTest2(){
	int result = 0;
	graph_t* testGraph = create_graph();
        graph_add_node(testGraph, 1);
        graph_add_node(testGraph, 2);
        graph_add_node(testGraph, 3);
        graph_add_node(testGraph, 4);
        graph_add_node(testGraph, 5);
        graph_add_node(testGraph, 6);
        graph_add_node(testGraph, 7);
        graph_add_node(testGraph, 8);
        graph_add_edge(testGraph, 1, 2, 4);
        graph_add_edge(testGraph, 1, 3, 8);
        graph_add_edge(testGraph, 2, 4, 3);
        graph_add_edge(testGraph, 3, 6, 5);
        graph_add_edge(testGraph, 4, 5, 6);
        graph_add_edge(testGraph, 4, 8, 2);
        graph_add_edge(testGraph, 6, 7, 11);
        graph_add_edge(testGraph, 8, 5, 3);
	graph_remove_edge(testGraph, 4, 5);

	if (contains_edge(testGraph, 4, 5) == 0){
		result = 1;
	}

	free_graph(testGraph);
	return result;
}

//Adds nodes, edges, tests out neighbors count
int unitTest3(){
	int result = 0;
	graph_t* testGraph = create_graph();
	graph_add_node(testGraph, 1);
        graph_add_node(testGraph, 2);
        graph_add_node(testGraph, 3);
	graph_add_node(testGraph, 4);
        graph_add_node(testGraph, 5);
        graph_add_node(testGraph, 6);
        graph_add_node(testGraph, 7);
        graph_add_node(testGraph, 8);
	graph_add_edge(testGraph, 1, 2, 4);
        graph_add_edge(testGraph, 1, 3, 8);
        graph_add_edge(testGraph, 1, 4, 3);
        graph_add_edge(testGraph, 1, 6, 5);
        graph_add_edge(testGraph, 1, 5, 6);
        graph_add_edge(testGraph, 1, 8, 2);

	if (getNumOutNeighbors(testGraph, 1) == 6){
		result = 1;
	}

	free_graph(testGraph);
	return result;
}

//Adds nodes, edges, tests number of nodes
int unitTest4(){
	int result = 0;
	graph_t* testGraph = create_graph();
	graph_add_node(testGraph, 1);
        graph_add_node(testGraph, 2);
        graph_add_node(testGraph, 3);
        graph_add_node(testGraph, 4);
        graph_add_node(testGraph, 5);
        graph_add_node(testGraph, 6);
        graph_add_node(testGraph, 7);
        graph_add_node(testGraph, 8);
        graph_add_edge(testGraph, 1, 2, 4);
        graph_add_edge(testGraph, 1, 3, 8);
        graph_add_edge(testGraph, 2, 4, 3);
        graph_add_edge(testGraph, 3, 6, 5);
        graph_add_edge(testGraph, 4, 5, 6);
        graph_add_edge(testGraph, 5, 8, 2);
	
	if (graph_num_nodes(testGraph) == 8){
		result = 1;
	}

	free_graph(testGraph);
	return result;
}

//Adds nodes, edges, removes a node and
//checks edges of destination node 
int unitTest5(){
	int result = 0;
	graph_t* testGraph = create_graph();
        graph_add_node(testGraph, 1);
        graph_add_node(testGraph, 2);
        graph_add_node(testGraph, 3);
        graph_add_node(testGraph, 4);
        graph_add_node(testGraph, 5);
        graph_add_node(testGraph, 6);
        graph_add_node(testGraph, 7);
        graph_add_node(testGraph, 8);
        graph_add_edge(testGraph, 1, 2, 4);
        graph_add_edge(testGraph, 1, 3, 8);
        graph_add_edge(testGraph, 2, 4, 3);
        graph_add_edge(testGraph, 3, 6, 5);
        graph_add_edge(testGraph, 4, 5, 6);
        graph_add_edge(testGraph, 5, 8, 2);
	graph_remove_node(testGraph, 4);

	if (getNumInNeighbors(testGraph, 5) == 0){
		result = 1;
	}

	free_graph(testGraph);
	return result;
}

//Adds duplicate nodes and checks number of nodes
int unitTest6(){
	int result;
	graph_t* testGraph = create_graph();
        graph_add_node(testGraph, 1);
        graph_add_node(testGraph, 1);
        graph_add_node(testGraph, 1);
        graph_add_node(testGraph, 1);
	
	if (graph_num_nodes(testGraph) == 1){
		result = 1;
	}

	free_graph(testGraph);
	return result;
}

//Adds duplicate edges and checks number of edges
int unitTest7(){
	int result = 0;
	graph_t* testGraph = create_graph();
        graph_add_node(testGraph, 1);
        graph_add_node(testGraph, 2);
	graph_add_edge(testGraph, 1, 2, 4);
	graph_add_edge(testGraph, 1, 2, 6);

	if (graph_num_edges(testGraph) == 1){
		result = 1;
	}

	free_graph(testGraph);
	return result;
}

int unitTest8(){
        int result = 0;
        graph_t* testGraph = create_graph();
        graph_add_node(testGraph, 1);
        graph_add_node(testGraph, 2);
        graph_add_edge(testGraph, 1, 2, 4);
	graph_edge_t* edge = graph_get_edge(testGraph, 1, 2);

	if (edge->cost == 4){
		result = 1;
	}

	free_graph(testGraph);
	return result;
}


int (*unitTests[])(int) = {
        unitTest1,
        unitTest2,
	unitTest3,
	unitTest4, 
	unitTest5,
	unitTest6,
	unitTest7,
	unitTest8,
        NULL
};

int main() {

        unsigned int testsPassed = 0;
        // List of unit tests to test data structure
        int counter = 0;
        while(unitTests[counter] != NULL){
                printf("========unitTest %d========\n",counter);
                if(1==unitTests[counter](1)){
                        printf("passed test\n");
                        testsPassed++;
                }else{
                        printf("failed test, missing functionality, or incorrect test\n");
                }
        counter++;
        }

        printf("%d of %d tests passed\n",testsPassed,counter);
	return 0;
}
