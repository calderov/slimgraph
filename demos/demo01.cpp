/*
Example Demo 01

Creates a graph with 6 nodes and 6 edges. Then one of the nodes is removed and 
*/

#include <iostream>
#include "graph.h"

using namespace std;

int main()
{
	Graph G;
	
	G.add_node(1);
	G.add_node(2);
	G.add_node(3);
	G.add_node(4);
	G.add_node(5);
	G.add_node(6);

	G.add_edge(1, 5);
	G.add_edge(2, 5);
	G.add_edge(3, 5);
	G.add_edge(5, 4);
	G.add_edge(5, 6);
	
	// This edge will survive
	G.add_edge(4, 6);

	G.print_graph();

	cout << "\nDeleting node 5" << endl;
	G.del_node(5);

	G.print_graph();

	return 0;
}
