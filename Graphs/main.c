// Compile this assignment with: gcc -Wall main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_graph.h"


// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.

//Testing Allocation
int unitTest1(){
	int result;
	graph_t* testGraph = create_graph();
	if (testGraph != NULL){
		result = 1;
	}
	else {
		result = 0;
	}
	free_graph(testGraph);
	return result;
}

//Add several nodes and check number of nodes
int unitTest2(){
	int result = 0;
	graph_t* testGraph = create_graph();
	graph_add_node(testGraph, 1);
	graph_add_node(testGraph, 2);
	graph_add_node(testGraph, 3);
	graph_add_node(testGraph, 4);
	graph_add_node(testGraph, 5);


	if (graph_num_nodes(testGraph) == 5){
		result = 1;
	}

	free_graph(testGraph);
	return result;
}

//Add several nodes with edges and check number of edges
int unitTest3(){
	int result = 0;
	graph_t* testGraph = create_graph();
        graph_add_node(testGraph, 1);
        graph_add_node(testGraph, 2);
        graph_add_node(testGraph, 3);
        graph_add_node(testGraph, 4);
	graph_add_edge(testGraph, 1, 2);
	graph_add_edge(testGraph, 1, 3);
	graph_add_edge(testGraph, 1, 4);
	graph_add_edge(testGraph, 2, 1);
	graph_add_edge(testGraph, 2, 3);
	graph_add_edge(testGraph, 3, 1);
	graph_add_edge(testGraph, 4, 3);

	if (graph_num_edges(testGraph) == 7){
		result = 1;
	}

	free_graph(testGraph);
	return result;
}

//Add nodes, add edges, remove an edge, and check
//if the edge still exists
int unitTest4(){
	int result = 0;
	graph_t* testGraph = create_graph();
        graph_add_node(testGraph, 1);
        graph_add_node(testGraph, 2);
        graph_add_node(testGraph, 3);
	graph_add_edge(testGraph, 1, 2);
        graph_add_edge(testGraph, 1, 3);
	graph_add_edge(testGraph, 2, 3);
	graph_remove_edge(testGraph, 2, 3);

	if (contains_edge(testGraph, 2, 3) == 0){
		result = 1;
	}

	free_graph(testGraph);
	return result;
}

//Add several nodes, several edges, then remove
//2 nodes and check if the number of edges
//has been decremented correctly
int unitTest5(){
	int result;
	graph_t* testGraph = create_graph();
        graph_add_node(testGraph, 1);
        graph_add_node(testGraph, 2);
        graph_add_node(testGraph, 3);
	graph_add_node(testGraph, 4);
	graph_add_node(testGraph, 5);
	graph_add_node(testGraph, 6);
	graph_add_node(testGraph, 7);
	graph_add_edge(testGraph, 1, 2);
        graph_add_edge(testGraph, 1, 3);
	graph_add_edge(testGraph, 1, 4);
        graph_add_edge(testGraph, 2, 1);
	graph_add_edge(testGraph, 2, 4);
	graph_add_edge(testGraph, 3, 6);
	graph_add_edge(testGraph, 4, 5);
	graph_add_edge(testGraph, 6, 4);
	graph_add_edge(testGraph, 6, 7);
	graph_add_edge(testGraph, 7, 6);
	graph_remove_node(testGraph, 3);
	graph_remove_node(testGraph, 7);

	if (graph_num_edges(testGraph) == 6){
		result = 1;
	}

	free_graph(testGraph);
	return result;
}

//Add several nodes and edges, and then check
//the number of inNeighbors of a particular node
int unitTest6(){
	int result = 0;
	graph_t* testGraph = create_graph();
	graph_add_node(testGraph, 1);
        graph_add_node(testGraph, 2);
        graph_add_node(testGraph, 3);
        graph_add_node(testGraph, 4);
        graph_add_node(testGraph, 5);
        graph_add_node(testGraph, 6);
	graph_add_node(testGraph, 7);
	graph_add_edge(testGraph, 1, 2);
        graph_add_edge(testGraph, 1, 3);
        graph_add_edge(testGraph, 1, 4);
        graph_add_edge(testGraph, 2, 1);
        graph_add_edge(testGraph, 2, 4);
        graph_add_edge(testGraph, 3, 6);
        graph_add_edge(testGraph, 4, 5);
        graph_add_edge(testGraph, 6, 4);
        graph_add_edge(testGraph, 6, 7);
        graph_add_edge(testGraph, 7, 6);

	if (getNumInNeighbors(testGraph, 4) == 3){
		result = 1;
	}

	free_graph(testGraph);
	return result;
}	

//Add several nodes and edges, and then check
//the number of outNeighbors of a particular node
int unitTest7(){
        int result = 0;
        graph_t* testGraph = create_graph();
        graph_add_node(testGraph, 1);
        graph_add_node(testGraph, 2);
        graph_add_node(testGraph, 3);
        graph_add_node(testGraph, 4);
        graph_add_node(testGraph, 5);
        graph_add_node(testGraph, 6);
        graph_add_node(testGraph, 7);
        graph_add_edge(testGraph, 1, 2);
        graph_add_edge(testGraph, 1, 3);
        graph_add_edge(testGraph, 1, 4);
        graph_add_edge(testGraph, 2, 1);
        graph_add_edge(testGraph, 2, 4);
        graph_add_edge(testGraph, 3, 6);
        graph_add_edge(testGraph, 4, 5);
        graph_add_edge(testGraph, 6, 4);
        graph_add_edge(testGraph, 6, 7);
        graph_add_edge(testGraph, 7, 6);

	if (getNumOutNeighbors(testGraph, 1) == 3){
		result = 1;
	}

	free_graph(testGraph);
	return result;
}

//Add several nodes and edges, remove a node,
//and then check the number of outNeighbors of 
//a node that was previously connected to the 
//removed node
int unitTest8(){
	int result = 0;
        graph_t* testGraph = create_graph();
        graph_add_node(testGraph, 1);
        graph_add_node(testGraph, 2);
        graph_add_node(testGraph, 3);
        graph_add_node(testGraph, 4);
        graph_add_node(testGraph, 5);
        graph_add_node(testGraph, 6);
        graph_add_node(testGraph, 7);
        graph_add_edge(testGraph, 1, 2);
        graph_add_edge(testGraph, 1, 3);
        graph_add_edge(testGraph, 1, 4);
        graph_add_edge(testGraph, 2, 1);
        graph_add_edge(testGraph, 2, 4);
        graph_add_edge(testGraph, 3, 6);
        graph_add_edge(testGraph, 4, 5);
        graph_add_edge(testGraph, 6, 4);
        graph_add_edge(testGraph, 6, 7);
        graph_add_edge(testGraph, 7, 6);
	graph_remove_node(testGraph, 3);

	if (getNumOutNeighbors(testGraph, 4) == 1){
                result = 1;
        }

        free_graph(testGraph);
        return result;
}

//Add duplicate nodes and check how many nodes
//there are in the graph
int unitTest9(){
	int result = 0;
	graph_t* testGraph = create_graph();
        graph_add_node(testGraph, 1);
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

//Add nodes, add edges, and then add an edge
//that has already been added. 
int unitTest10(){
	int result = 0;
        graph_t* testGraph = create_graph();
        graph_add_node(testGraph, 1);
        graph_add_node(testGraph, 2);
        graph_add_node(testGraph, 3);
        graph_add_edge(testGraph, 1, 2);
	graph_add_edge(testGraph, 1, 3);
	graph_add_edge(testGraph, 2, 3);

	if (graph_add_edge(testGraph, 1, 2) == 0){
		result = 1;
	}

	free_graph(testGraph);
	return result;
}

//Add nodes, add edges, remove all the nodes
//and check the number of nodes
int unitTest11(){
	int result = 0;
	graph_t* testGraph = create_graph();
        graph_add_node(testGraph, 1);
        graph_add_node(testGraph, 2);
        graph_add_node(testGraph, 3);
	graph_add_edge(testGraph, 1, 2);
	graph_add_edge(testGraph, 1, 3);
	graph_add_edge(testGraph, 2, 3);
	graph_remove_node(testGraph, 1);
	graph_remove_node(testGraph, 2);
	graph_remove_node(testGraph, 3);

	if (graph_num_nodes(testGraph) == 0){
		result = 1;
	}

	free_graph(testGraph);
	return result;
} 

//Add nodes, add edges, remove all nodes
//and check the number of edges
int unitTest12(){
        int result = 0;
        graph_t* testGraph = create_graph();
        graph_add_node(testGraph, 1);
        graph_add_node(testGraph, 2);
        graph_add_node(testGraph, 3);
        graph_add_edge(testGraph, 1, 2);
        graph_add_edge(testGraph, 1, 3);
        graph_add_edge(testGraph, 2, 3);
        graph_remove_node(testGraph, 1);
        graph_remove_node(testGraph, 2);
        graph_remove_node(testGraph, 3);

        if (graph_num_edges(testGraph) == 0){
                result = 1;
        }

        free_graph(testGraph);
        return result;
}
 
//Add a node, remove a node, then try to
//find the node in the graph
int unitTest13(){
        int result = 0;
        graph_t* testGraph = create_graph();
        graph_add_node(testGraph, 1);
	graph_remove_node(testGraph, 1);

	if (find_node(testGraph, 1) == NULL){
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
	unitTest9,
	unitTest10,
	unitTest11,
	unitTest12,
	unitTest13,
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
