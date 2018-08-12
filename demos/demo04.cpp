/*
Example Demo 04

Creates a graph with 2 nodes and 1 edges. Properties are defined for them and then printed

*/

#include <iostream>
#include "digraph.h"

using namespace std;

int main()
{
	DiGraph G;
	
	G.add_node(1);
	G.add_node(2);

	G.add_edge(1, 2);

	G.add_node_property("NodeString", STRING);
	G.set_node_property(1, "NodeString", "Foo");
	G.set_node_property(2, "NodeString", "Bar");

	G.add_node_property("NodeDouble", DOUBLE);
	G.set_node_property(1, "NodeDouble", 111);
	G.set_node_property(2, "NodeDouble", 222);

	G.add_edge_property("EdgeString", STRING);
	G.set_edge_property(1, 2, "EdgeString", "xyz");

	G.add_edge_property("EdgeDouble", DOUBLE);
	G.set_edge_property(1, 2, "EdgeDouble", 333);

	G.print_node_properties();
	cout << endl;
	G.print_edge_properties();
	cout << endl;
	cout << endl;
	
	G.print_node_properties(1);
	cout << endl;
	G.print_edge_properties(1, 2);


	return 0;
}